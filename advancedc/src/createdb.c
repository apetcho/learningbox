/** This program demonstrates typedef */
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>


#define CUSTOMER_RECORD     1
#define SUPPLIER_RECORD     2

/* Data structure */
typedef struct {
    int rectype;        // 1 == Customer record
    char name[61];      // 60 chars for name, 1 for null at end
    char addr1[61];     // address 1
    char addr2[61];     // address 2
    char city[26];      // City
    char state[3];      // 2-character state abbreviation, plus null
    int zip;            // 
    int nrecnum;        // record number
    double total;
}Customer_t;

typedef Customer_t* PCustomer_t;
typedef Customer_t** NPCustomer_t;

static void readline(char *data, size_t len);


int main(){
    FILE *fp;
    Customer_t customer;
    char filename[25];
    char buffer[129];
    int i;
    int nresult;
    double sales = 0.0;

    printf("Please enter customer databse name: ");
    readline(filename, sizeof(filename)-1);
    fp = fopen(filename, "wb");
    if(fp == NULL){
        fprintf(stderr, "ERROR: File '%s' couldn't be opened.\n", filename);
        exit(4);
    }
    customer.name[0] = 'A'; // to get past while() the first time
    i = 0;
    customer.nrecnum = 0;
    while(strlen(customer.name) > 0){
        memset(&customer, 0, sizeof(customer));
        printf("Enter the customer's name: ");
        readline(customer.name, sizeof(customer.name));
        if(strlen(customer.name) > 0){
            customer.nrecnum = i;
            do{
                printf("Enter 1 for customer, 2 for supplier: ");
                readline(buffer, sizeof(buffer));
                sscanf(buffer, "%d", &customer.rectype);
            }while(
                customer.rectype != CUSTOMER_RECORD &&
                customer.rectype != SUPPLIER_RECORD
            );
            printf("Enter address line 1: ");
            readline(customer.addr1, sizeof(customer.addr1));
            printf("Enter address line 2: ");
            readline(customer.addr2, sizeof(customer.addr2));
            printf("Enter city: ");
            readline(customer.city, sizeof(customer.city));
            printf("Enter state postal abbreviation: ");
            readline(customer.state, sizeof(customer.state));
            printf("Enter ZIP code: ");
            readline(buffer, sizeof(buffer));
            sscanf(buffer, "%d", &customer.zip);
            printf("Enter total sales: ");
            readline(buffer, sizeof(buffer));
            sscanf(buffer, "%lf", &customer.total);

            nresult = fwrite((char*)&customer, sizeof(Customer_t), 1, fp);
            if(nresult != 1){
                fprintf(stderr, "ERROR: File '%s', write error.\n", filename);
                fclose(fp);
                exit(4);
            }
            ++i;
        }
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

// ---
static void readline(char *data, size_t len){
    const size_t N = len;
    memset(data, 0, len);
    char buffer[N];
    fgets(buffer, N, stdin);
    size_t xlen = strlen(buffer);
    buffer[xlen-1] = '\0';
    int i=0;
    while((*(data+i) = buffer[i])){
        if(buffer[i] == '\0'){break;}
        ++i;
    }
    *(data+i) = '\0';
    fflush(stdout);
    fflush(stdin);
    printf("readline():: data = %s\n", data);
    printf("readline():: buffer = %s\n", buffer);
}
