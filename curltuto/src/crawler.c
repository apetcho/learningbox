#include<libxml/HTMLparser.h>
#include<libxml/xpath.h>
#include<libxml/uri.h>
#include<curl/curl.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>
#include<math.h>

// -*-
typedef struct {
    int maxCon;
    int maxTotal;
    int maxRequests;
    int maxLinkPerPage;
    int followRelativeLinks;
    const char* urlbase;
}Parameters;

// -*-
typedef struct {
    char *data;
    size_t len;
} Buffer;

// -*-
int pendingInterrupt = 0;
void sighandler(int dummy){
    pendingInterrupt = 1;
}

// -*-
size_t resize_buffer(void *buffer, size_t sz, size_t nmemb, void *ctx){
    size_t memsize = sz * nmemb;
    Buffer* self = (Buffer*)ctx;
    char *ptr = realloc(self->data, self->len + memsize);
    if(!ptr){
        fprintf(stderr, "not enought memory (realloc returned NULL)\n");
        return 0;
    }
    self->data = ptr;
    memcpy(&(self->data[self->len]), buffer, memsize);
    self->len += memsize;
    return memsize;
}

// -*-
CURL* make_handle(const char *url){
    CURL* handle = curl_easy_init();
    // Immportand: use HTTP2 over HTTPS
    curl_easy_setopt(handle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
    curl_easy_setopt(handle, CURLOPT_URL, url);

    // buffer body
    Buffer* buffer = calloc(1, sizeof(*buffer));
    buffer->len = 0;
    buffer->data = calloc(1, sizeof(char));
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, resize_buffer);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, buffer);
    curl_easy_setopt(handle, CURLOPT_PRIVATE, buffer);

    // For completeness
    curl_easy_setopt(handle, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(handle, CURLOPT_TIMEOUT, 5L);
    curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
    // only allow redirects to HTTP and HTTPS URLs
    curl_easy_setopt(handle, CURLOPT_REDIR_PROTOCOLS_STR, "http,https");
    curl_easy_setopt(handle, CURLOPT_AUTOREFERER, 1L);
    curl_easy_setopt(handle, CURLOPT_MAXREDIRS, 10L);
    // each transfer needs to be done within 20 seconds!
    curl_easy_setopt(handle, CURLOPT_TIMEOUT_MS, 20000L);
    // connect fast of fail
    curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT_MS, 2000L);
    // skip files larger thand a gigabyte
    curl_easy_setopt(handle, CURLOPT_MAXFILESIZE_LARGE, (curl_off_t)1024*1024*1024);
    curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "");
    curl_easy_setopt(handle, CURLOPT_FILETIME, 1L);
    curl_easy_setopt(handle, CURLOPT_USERAGENT, "mini crawler");
    curl_easy_setopt(handle, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
    curl_easy_setopt(handle, CURLOPT_UNRESTRICTED_AUTH, 1L);
    curl_easy_setopt(handle, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
    curl_easy_setopt(handle, CURLOPT_EXPECT_100_TIMEOUT_MS, 0L);

    return handle;
}

// -*-
size_t follow_links(CURLM *multiHandle, Buffer *buffer, const char *url, Parameters params){
    int opts = (
        HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR |
        HTML_PARSE_NOWARNING | HTML_PARSE_NONET
    );
    htmlDocPtr doc = htmlReadMemory(buffer->data, buffer->len, url, NULL, opts);
    if(!doc){
        return 0;
    }
    xmlChar *xpath = (xmlChar*)"//a/@href";
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);
    if(!result){
        return 0;
    }
    xmlNodeSetPtr nodeset = result->nodesetval;
    if(xmlXPathNodeSetIsEmpty(nodeset)){
        xmlXPathFreeObject(result);
        return 0;
    }
    size_t count = 0;
    int i;
    for(i=0; i < nodeset->nodeNr; i++){
        double r = rand();
        int x = r * nodeset->nodeNr / RAND_MAX;
        const xmlNode *node = nodeset->nodeTab[x]->xmlChildrenNode;
        xmlChar *href = xmlNodeListGetString(doc, node, 1);
        if(params.followRelativeLinks){
            xmlChar *orig = href;
            href = xmlBuildURI(href, (xmlChar*)url);
            xmlFree(orig);
        }
        char* link = (char*)href;
        if(!link || strlen(link) < 20){
            continue;
        }
        if(!strncmp(link, "http://", 7)||!strncmp(link, "https://", 8)){
            curl_multi_add_handle(multiHandle, make_handle(link));
            if(count++ == params.maxLinkPerPage){
                break;
            }
        }
        xmlFree(link);
    }
    xmlXPathFreeObject(result);
    return count;
}

// -*-
int is_html(char *cstr){
    return cstr != NULL && strlen(cstr) > 10 && strstr(cstr, "text/html");
}

// -*-------------------------*-
// -*- M A I N   D R I V E R -*-
// -*-------------------------*-
int main(int argc, char **argv){
    signal(SIGINT, sighandler);

    Parameters params = {};
    params.maxCon = 200;
    params.maxTotal = 20000;
    params.maxRequests = 500;
    params.maxLinkPerPage = 5;
    params.followRelativeLinks = 0;
    params.urlbase = "https://www.reuters.com";

    LIBXML_TEST_VERSION;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURLM *multi_handle = curl_multi_init();
    curl_multi_setopt(multi_handle, CURLMOPT_MAX_TOTAL_CONNECTIONS, params.maxCon);
    curl_multi_setopt(multi_handle, CURLMOPT_MAX_HOST_CONNECTIONS, 6);

    // enables http/2 if available
#ifdef CURLPIPE_MULTIPLEX
    curl_multi_setopt(multi_handle, CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX);
#endif

    // sets html start page
    curl_multi_add_handle(multi_handle, make_handle(params.urlbase));

    int msgs_left;
    int pending = 0;
    int complete = 0;
    int still_running = 1;
    while(still_running && !pendingInterrupt){
        int numfds;
        curl_multi_wait(multi_handle, NULL, 0, 1000, &numfds);
        curl_multi_perform(multi_handle, &still_running);

        // see how the transfers went
        CURLMsg *m = NULL;
        while((m=curl_multi_info_read(multi_handle, &msgs_left))){
            if(m->msg == CURLMSG_DONE){
                CURL *handle = m->easy_handle;
                char *url = NULL;
                Buffer *buffer = {0};
                curl_easy_getinfo(handle, CURLINFO_PRIVATE, &buffer);
                curl_easy_getinfo(handle, CURLINFO_EFFECTIVE_URL, &url);
                if(m->data.result == CURLE_OK){
                    long res_status;
                    curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &res_status);
                    if(res_status==200){
                        char *cstr;
                        curl_easy_getinfo(handle, CURLINFO_CONTENT_TYPE, &cstr);
                        printf("[%d] HTTP 200 (%s): %s\n", complete, cstr, url);
                        if(is_html(cstr) && buffer->len > 100){
                            if(pending < params.maxRequests && (complete + pending) < params.maxTotal){
                                pending += follow_links(multi_handle, buffer, url, params);
                                still_running = 1;
                            }
                        }
                    }else{
                        printf("[%d] HTTP %d: %s\n", complete, (int)res_status, url);
                    }
                }else{
                    printf("[%d] Connection failure: %s\n", complete, url);
                }
                curl_multi_remove_handle(multi_handle, handle);
                curl_easy_cleanup(handle);
                free(buffer->data);
                free(buffer);
                complete++;
                pending--;
            }
        }
    }

    curl_multi_cleanup(multi_handle);
    curl_global_cleanup();

    return 0;
}