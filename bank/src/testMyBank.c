
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<assert.h>

#include "mybank.h"

void testOpenBank();
// ----------------------------
//    M A I N   D R I V E R
// ----------------------------
int main(int argc, char **argv){
    puts("Testing open_bank() ...");
    testOpenBank();
    puts("Test ............... OK");
    
    return EXIT_SUCCESS;
}

// ----
void testOpenBank(){
    Bank_t *bk = open_bank();
    assert(bk->db == NULL);
    assert(bk->accounts == NULL);
    assert(strcmp(bk->dbfile, "bkdatafile") == 0);
}
