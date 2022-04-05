
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<assert.h>

#include "mybank.h"
typedef int (*fn)();

int testOpenBank();
int testCreateAccount();

void tester(fn callback, const char *funname){
    char line[80];
    char top[80];
    char bot[80];
    memset(line, '.', 78);
    line[79] = '\0';
    memset(top, '\0', 80);
    memset(bot, '\0', 80);
    sprintf(top, "%s ", funname);
    sprintf(bot, "Test ");
    size_t xn = strlen(top);
    size_t dx = 79 - xn - 8 - 14;
    size_t dy = 79 - 5 - 8 - 14; 
    if(dx > 0){
        (void)strncat(top, line, dx);
    }
    if(dy > 0){
        (void)strncat(bot, line, dy);
    }

    strcat(top, " \x1b[34mSTARTED\x1b[m");

    printf("%s\n", top);
    int ret = callback();
    if(ret == 0){
        strcat(bot, " \x1b[32mOK\x1b[m");
        printf("%s\n", bot);
    }else{
        strcat(bot, " \x1b[31mFAILED\x1b[m");
        printf("%s\n", bot);
    }
    putchar('\n');
}

// ----------------------------
//    M A I N   D R I V E R
// ----------------------------
int main(int argc, char **argv){
    //puts("Testing open_bank() ...");
    //testOpenBank();
    //puts("Test ............... OK");
    tester(testOpenBank, "open_bank()");
    tester(testCreateAccount, "create_account()");

    return EXIT_SUCCESS;
}

// ----
int testOpenBank(){
    Bank_t *bk = open_bank();
    int ret = 1;
    if(bk->db == NULL){ ret = 0; }
    if(bk->accounts == NULL){ret = 0;}
    if(strcmp(bk->dbfile, "bkdatafile") == 0){ ret = 0; }
    return ret;
}

// ----
int testCreateAccount(){
    int ret = 1;
    Account *acnt = create_account(
        "John", "Doe", "jdoe@exple.com", "+130 011 123 421", "#&Jdabc"
    );
    if(acnt){ ret = 0; }
    if(acnt->transactions == NULL){ ret = 0; }

    printf("fname: %s\n", acnt->fname);
    printf("lname: %s\n", acnt->lname);
    printf("email: %s\n", acnt->email);
    printf("phone: %s\n", acnt->phone);
    printf("pword: %s\n", acnt->pword);
    printf("accno: %s\n", acnt->accno);
    printf("balance: %lf\n", acnt->balance);
    printf("created: %s\n", asctime(localtime(&acnt->created)));

    free(acnt->fname);
    free(acnt->lname);
    free(acnt->email);
    free(acnt->phone);
    free(acnt->pword);
    free(acnt->accno);
    free(acnt);

    return ret;
}
