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
    DBM *dbm_ptr;
    

    return EXIT_SUCCESS;
}
