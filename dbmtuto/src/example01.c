#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ndbm.h>

#define TEST_DB_FILE    "dbmTestExample"
#define ITEMS_USED       3

typedef struct TestData{
    char misc[15];
    int value;
    char more[21];
} TestData_t;


// ---------------
//   MAIN DRIVER
// ---------------
int main(){
    TestData_t items_to_store[ITEMS_USED];
    TestData_t item_retrieved;

    char key_to_use[20];
    int i, result;

    datum key_datum;
    datum data_datum;
    DBM *dbmPtr;

    dbmPtr = dbm_open(TEST_DB_FILE, O_RDWR|O_CREAT, 0666);
    if(!dbmPtr){
        fprintf(stderr, "Failed to open database\n");
        exit(EXIT_FAILURE);
    }
    memset(items_to_store, '\0', sizeof(items_to_store));
    
    strcpy(items_to_store[0].misc, "First!");
    items_to_store[0].value = 47;
    strcpy(items_to_store[0].more, "foo");

    strcpy(items_to_store[1].misc, "bar!");
    items_to_store[1].value = 13;
    strcpy(items_to_store[1].more, "unlucky?");

    strcpy(items_to_store[2].misc, "Third!");
    items_to_store[2].value = 3;
    strcpy(items_to_store[2].more, "baz?");

    return EXIT_SUCCESS;
}
