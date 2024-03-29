#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#include "appcommon.h"

#define TMP_STRING_LEN  128

/* MENU OPTIONS */
typedef enum {
    MO_INVALID,
    MO_ADD_CAT,
    MO_ADD_TRACKS,
    MO_DEL_CAT,
    MO_FIND_CAT,
    MO_LIST_CAT_TRACKS,
    MO_DEL_TRACKS,
    MO_COUNT_ENTRIES,
    MO_EXIT
} MenuOption;

/* LOCAL PROTOTYPES */
static int command_mode(int argc, char **argv);
static void announce(void);
static MenuOption show_menu(const CatalogEntry *current);
static int get_confirm(const char *question);
static int enter_new_catalog_entry(CatalogEntry *entry);
static void enter_new_track_entries(const CatalogEntry *entry);
static void _delete_catalog_entry(const CatalogEntry *entry);
static void _delete_track_entries(const CatalogEntry *entry);
static CatalogEntry find_catalog(void);
static void list_tracks(const CatalogEntry *entry);
static void count_all_entries(void);
static void display_catalog(const CatalogEntry *entry);
static void display_track(const TrackEntry *entry);
static void strip_return(char *text);

// ----------------------------
//     M A I N   D R I V E R
// ----------------------------
int main(int argc, char **argv){
    MenuOption option;
    CatalogEntry c_entry;
    int cmdResult;

    memset(&c_entry, '\0', sizeof(c_entry));

    if(argc > 1){
        cmdResult = command_mode(argc, argv);
        exit(cmdResult);
    }
    announce();

    if(!db_initialize(0)){
        fprintf(stderr, "Sorry, unable to initialize database\n");
        fprintf(stderr, "To create a new database use\n\t%s -i", argv[0]);
        exit(EXIT_FAILURE);
    }

    while(option != MO_EXIT){
        option = show_menu(&c_entry);
        switch(option){
        case MO_ADD_CAT:
            if(enter_new_catalog_entry(&c_entry)){
                if(!add_catalog_entry(c_entry)){
                    fprintf(stderr, "Failed to add new entry\n");
                    memset(&c_entry, '\0', sizeof(c_entry));
                }
            }
            break;
        case MO_ADD_TRACKS:
            enter_new_track_entries(&c_entry);
            break;
        case MO_DEL_CAT:
            _delete_catalog_entry(&c_entry);
            break;
        case MO_FIND_CAT:
            c_entry = find_catalog();
            break;
        case MO_LIST_CAT_TRACKS:
            list_tracks(&c_entry);
            break;
        case MO_DEL_TRACKS:
            _delete_track_entries(&c_entry);
            break;
        case MO_COUNT_ENTRIES:
            count_all_entries();
            break;
        case MO_EXIT:
            break;
        case MO_INVALID:
            break;
        default:
            break;
        }
    }

    db_close();
    return EXIT_SUCCESS;
}

// ------------------------ LOCAL ROUTINES -----------------------------
static void announce(void){
    const char text[] =
        "\n\n"
        "---------------------------------------------------------------"
        "    WELCOME TO THE DEMONSTRATION CD CATALOG DATABASE PROGRAM   "
        "---------------------------------------------------------------"
        "\n";
    printf("%s", text);
}

// ---
static MenuOption show_menu(const CatalogEntry *selected){
    char tmpstr[TMP_STRING_LEN+1];
    MenuOption chosen = MO_INVALID;

    while(chosen == MO_INVALID){
        if(selected->catalog[0]){
            printf("\n\nCurrent entry: ");
            printf("%s, %s, %s, %s\n",
                selected->catalog, selected->title,
                selected->type, selected->artist
            );
            printf("\n");
            puts("1 - Add new CD");
            puts("2 - Search for a CD");
            puts("3 - Count the CDs and tracks in the database");
            puts("4 - Re-enter tracks for current CD");
            puts("5 - Delete this CD, and all it's tracks");
            puts("6 - List tracks for this CD");
            puts("q - Quit\n");
            printf("option>> ");
            fgets(tmpstr, TMP_STRING_LEN, stdin);
            switch(tmpstr[0]){
            case '1':
                chosen = MO_ADD_CAT;
                break;
            case '2':
                chosen = MO_FIND_CAT;
                break;
            case '3':
                chosen = MO_COUNT_ENTRIES;
                break;
            case '4':
                chosen = MO_ADD_TRACKS;
                break;
            case '5':
                chosen = MO_DEL_CAT;
                break;
            case '6':
                chosen = MO_LIST_CAT_TRACKS;
                break;
            case 'q':
                chosen = MO_EXIT;
                break;
            }
        }else{
            puts("\n");
            puts("1 - Add new CD");
            puts("2 - Search for a CD");
            puts("3 - Count the CDs and tracks in the database");
            puts("q - Quit\n");
            printf("option>> ");
            fgets(tmpstr, TMP_STRING_LEN, stdin);
            switch(tmpstr[0]){
            case '1':
                chosen = MO_ADD_CAT;
                break;
            case '2':
                chosen = MO_FIND_CAT;
                break;
            case '3':
                chosen = MO_COUNT_ENTRIES;
                break;
            case 'q':
                chosen = MO_EXIT;
                break;
            }
        }
    }

    return chosen;
}

// ---
static int get_confirm(const char *question){
    char tmpstr[TMP_STRING_LEN+1];
    printf("%s (yes/no)\n>> ", question);
    fgets(tmpstr, TMP_STRING_LEN, stdin);
    if(tmpstr[0] == 'Y' || tmpstr[0] == 'y'){ return 1; }
    return 0;
}

// ----
static int enter_new_catalog_entry(CatalogEntry *entry){
    CatalogEntry n_entry;
    char tmpstr[TMP_STRING_LEN+1];

    memset(&n_entry, '\0', sizeof(n_entry));
    puts("Enter catalog entry:");
    printf(">> ");
    (void)fgets(tmpstr, TMP_STRING_LEN, stdin);
    strip_return(tmpstr);
    strncpy(n_entry.catalog, tmpstr, CAT_CAT_LEN-1);

    puts("Enter Title:");
    printf(">> ");
    (void)fgets(tmpstr, TMP_STRING_LEN, stdin);
    strip_return(tmpstr);
    strncpy(n_entry.title, tmpstr, CAT_TITLE_LEN-1);

    puts("Enter Type:");
    printf(">> ");
    (void)fgets(tmpstr, TMP_STRING_LEN, stdin);
    strip_return(tmpstr);
    strncpy(n_entry.type, tmpstr, CAT_TYPE_LEN-1);

    puts("Enter Artist:");
    printf(">> ");
    (void)fgets(tmpstr, TMP_STRING_LEN, stdin);
    strip_return(tmpstr);
    strncpy(n_entry.artist, tmpstr, CAT_ARTIST_LEN-1);

    puts("\nNew catalog entry is:-");
    display_catalog(&n_entry);
    if(get_confirm("Add this entry ?")){
        memcpy(entry, &n_entry, sizeof(n_entry));
        return 1;
    }

    return 0;
}


//
static void enter_new_track_entries(const CatalogEntry *entry){
    TrackEntry ntrack, xtrack;
    char tmpstr[TMP_STRING_LEN+1];
    int trackno = 1;

    if(entry->catalog[0] == '\0'){ return; }
    printf("\nUpdating tracks for %s\n", entry->catalog);
    puts("Press return to leave existing description unchanged,");
    puts("a single \x1b[32md\x1b[m to delete this and remaining tracks,");
    puts("or new track descriptions");

    while(1){
        memset(&ntrack, '\0', sizeof(ntrack));
        xtrack = get_track_entry(entry->catalog, trackno);
        if(xtrack.catalog[0]){
            printf("\tTrack %d: %s\n", trackno, xtrack.tracktxt);
            printf("\tNew text:");
        }else{
            printf("\tTrack %d description: ", trackno);
        }
        fgets(tmpstr, TMP_STRING_LEN, stdin);
        strip_return(tmpstr);
        if(strlen(tmpstr) == 0){
            if(xtrack.catalog[0] == '\0'){ break; }
            else{
                trackno++;
                continue;
            }
        }
        if((strlen(tmpstr) == 1) && tmpstr[0] == 'd'){
            while(delete_track_entry(entry->catalog, trackno)){
                trackno++;
            }
            break;
        }

        // --
        strncpy(ntrack.tracktxt, tmpstr, TRACT_TTEXT_LEN-1);
        strcpy(ntrack.catalog, entry->catalog);
        ntrack.trackno = trackno;
        if(!add_track_entry(ntrack)){
            fprintf(stderr, "Failed to add new track\n");
            break;
        }
        trackno++;
    }
}

//
static void _delete_catalog_entry(const CatalogEntry *entry){
    int trackno = 1;
    int deleteok;

    display_catalog(entry);
    if(get_confirm("Delete this entry and all it's tracks? ")){
        do{
            deleteok = delete_track_entry(entry->catalog, trackno);
            trackno++;
        }while(deleteok);

        if(!delete_catalog_entry(entry->catalog)){
            fprintf(stderr, "Failed to delete entry\n");
        }
    }
}

// ----
static void _delete_track_entries(const CatalogEntry *entry){
    int trackno = 1;
    int deleteok;
    display_catalog(entry);
    if(get_confirm("Delete tracks for this entry? ")){
        do{
            deleteok = delete_track_entry(entry->catalog, trackno);
            trackno++;
        }while(deleteok);
    }
}

//
static CatalogEntry find_catalog(void){
    CatalogEntry found;
    char tmpstr[TMP_STRING_LEN+1];
    int fcall = 1;
    int anyfound = 0;
    int stringok = 0;
    int selected = 0;

    do{
        stringok = 1;
        printf("Enter string to search for in catalog entry:\n>> ");
        fgets(tmpstr, TMP_STRING_LEN, stdin);
        strip_return(tmpstr);
        if(strlen(tmpstr) > CAT_CAT_LEN){
            fprintf(
                stderr, "Sorry, string too long, maximum %d characters\n",
                CAT_CAT_LEN
            );
            stringok = 0;
        }
    }while(!stringok);

    while(!selected){
        found = search_catalog_entry(tmpstr, &fcall);
        if(found.catalog[0] != '\0'){
            anyfound = 1;
            puts("");
            display_catalog(&found);
            if(get_confirm("This entry? ")){
                selected = 1;
            }
        }else{
            if(anyfound){puts("Sorry, no more matches found");}
            else{ puts("Sorry, nothing found");}
            break;
        }
    }

    return found;
}

// ----
static void list_tracks(const CatalogEntry *entry){
    int trackno = 1;
    TrackEntry entfound;

    display_catalog(entry);
    printf("\nTracks\n");
    do{
        entfound = get_track_entry(entry->catalog, trackno);
        if(entfound.catalog[0]){
            display_track(&entfound);
            trackno++;
        }
    }while(entfound.catalog[0]);
    (void)get_confirm("Press return");
}

// ---
static void count_all_entries(void){
    int cfound = 0;
    int tfound = 0;
    CatalogEntry catalog;
    TrackEntry track;
    int trackno = 1;
    int ftime = 1;
    char *searchstr = "";

    do{
        catalog = search_catalog_entry(searchstr, &ftime);
        if(catalog.catalog[0]){
            cfound++;
            trackno = 1;
            do{
                track = get_track_entry(catalog.catalog, trackno);
                if(track.catalog[0]){
                    tfound++;
                    trackno++;
                }
            }while(track.catalog[0]);
        }
    }while(catalog.catalog[0]);

    printf("Found %d CDs, with a total of %d tracks\n", cfound, tfound);
    (void)get_confirm("Press return");
}

//
static void display_catalog(const CatalogEntry *entry){
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[m"
    printf("Catalogue:" YELLOW " %s" RESET "\n", entry->catalog);
    printf("\ttitle  :" GREEN " %s" RESET "\n", entry->title);
    printf("\ttype   :" GREEN " %s" RESET "\n", entry->title);
    printf("\tartist :" GREEN " %s" RESET "\n", entry->artist);

#undef GREEN
#undef YELLOW
#undef RESET
}

// ---
static void display_track(const TrackEntry *entry){
#define BLUE    "\x1b[34m"
#define GREEN   "\x1b[32m"
#define RESET   "\x1b[m"
    printf(
        GREEN "%d:" RESET BLUE "%s" BLUE "\n", entry->trackno, entry->tracktxt
    );

#undef BLUE
#undef GREEN
#undef RESET
}

//
static void strip_return(char *text){
    int len;
    len = strlen(text);
    if(text[len-1] == '\n'){
        text[len-1] = '\0';
    }
}

static int command_mode(int argc, char **argv){
    int c;
    int result = EXIT_SUCCESS;
    char *progname = argv[0];

    while((c = getopt(argc, argv, ":i")) != -1){
        switch(c){
        case 'i':
            if(!db_initialize(1)){
                result = EXIT_FAILURE;
                fprintf(stderr, "Failed to initialize database\n");
            }
            break;
        case ':':
        case '?':
        default:
            fprintf(stderr, "Usage:\n\t%s [-i]\n", progname);
            result = EXIT_FAILURE;
            break;
        }
    }

    return result;
}
