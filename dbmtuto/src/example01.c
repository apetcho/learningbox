#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ndbm.h>

#define TEST_DB_FILE    "dbmTestExample"
#define ITEM_USED       3

typedef struct TestData{
    char misc[15];
    int value;
    char more[21];
} TestData_t;


// ---------------
//   MAIN DRIVER
// ---------------
int main(){

    return EXIT_SUCCESS;
}
