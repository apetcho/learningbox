#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include "xvector.h"
#include "bank.h"

#define BANKLEN         16
#define BANK_NAMELEN    32


static const int SECRET_LEN = 128;
static const int PASSWORD_MAXLEN = 32;
static const int DEFAULT_CAPACITY = 10;
static const double GROWTH_RATE = 1.5;
static const char* WITHDRAW_STRING = "Withdraw";
static const char* DEPOSIT_STRING = "Deposit";
static const char* CONSULT_STRING = "Consult";

// fname-lname-phone-id.txt
#define TRANS_FORMAT    "%s-%s-%s-%d.txt"
static const char* CFILE_SUFFIX = "Customers.dat";
static const char* SFILE_SUFFIX = "Secret.bin";

// ------
//! @todo
void bank_event_handler(int banksignum){}
void bank_exception(BankEvent event){}

// ---------------
//  Transaction
// ---------------
typedef struct Transaction_ Transaction;
struct Transaction_{
    BankEvent type;
    time_t when;
    size_t (*to_string)(const Transaction *self, char *outstr);
};

// -----------------------------------------------------------------
enum BankEvent_{
    OP_UNKNOWN = -1,
    OP_SUCCESS = 0,
    OP_CREATE_ACCOUNT,
    OP_CLOSE_ACCOUNT,
    OP_VALIDATE_ACCOUNT,
    OP_WITHDRAW,
    OP_CONSULT,
    OP_DEPOSIT,
    OP_TRANSFER,
    OP_FAIL = 100,
    OP_MEMORY = 101
};

// -----------------------------------------------------------------
static Transaction *malloc_transaction(BankEvent type){
    signal(OP_MEMORY, bank_event_handler);
    Transaction *trans;
    trans = (Transaction *)malloc(sizeof(*trans));
    if(trans == NULL){ raise(OP_MEMORY);}
    trans->type = type;
    trans->when = time(0);
    trans->to_string = transaction_string;
    return trans;
}

// ----
static void free_transaction(Transaction *self){
    signal(OP_UNKNOWN, bank_event_handler);
    if(self){
        free(self);
        self->type = OP_UNKNOWN;
        self->when = (time_t)0;
        self->to_string = 0;
    }else{
        perror("delete_transaction(): cannot delete non-exist transtaction");
        raise(OP_UNKNOWN);
    }
    return;
}

// ---
static void print_transaction(const Transaction *self){
    signal(OP_UNKNOWN, bank_event_handler);
    if(self){
        char *buf;
        transaction_string(self, buf);
        printf("%s\n", buf);
    }else{
        perror("print_transaction(): cannot print non-exist transtaction");
        raise(OP_UNKNOWN);
    }
    return;
}

// ---
static size_t transaction_string(const Transaction *self, char *outstr){
    signal(OP_MEMORY, bank_event_handler);
    char buf[80];
    size_t len;
    BankEvent type = self->type;
    switch(type){
    case OP_WITHDRAW:
        sprintf(buf, "%s @ %s",
            WITHDRAW_STRING, asctime(localtime(&self->when)));
        len = strlen(buf);
        buf[len-1] = '\0';
        break;
    case OP_DEPOSIT:
        sprintf(buf, "%s @ %s",
            DEPOSIT_STRING, asctime(localtime(&self->when)));
        len = strlen(buf);
        buf[len-1] = '\0';
        break;
    case OP_CONSULT:
        sprintf(buf, "%s @ %s",
            CONSULT_STRING, asctime(localtime(&self->when)));
        len = strlen(buf);
        buf[len-1] = '\0';
        break;
    default:
        sprintf(buf, "");
        len = 0;
        buf[0] = '\0';
    }
    outstr = malloc(len+1);
    if(outstr == NULL){
        perror("transaction_string()");
        raise(OP_MEMORY);
        return 0;
    }
    strncpy(outstr, buf, len);
    return len;
}

// ---
static void copy_transaction(Transaction *to, const Transaction *from){
    if(to){
        delete_transaction(to);
    }
    to = create_transaction(from->type);
    to->when = from->when;
    return;
}

// -----------
// User Info
// -----------
struct UserInfo_{
    char fname[BANKLEN+1];
    char lname[BANKLEN+1];
    char email[BANKLEN+1];
    char phone[BANKLEN+1];
    size_t (*to_string)(const UserInfo *user, char* outstr);
};

static size_t user_string(const UserInfo *user, char *outstr){
    signal(OP_MEMORY, bank_event_handler);
    const size_t maxlen = 4*(BANKLEN+1);
    size_t len;
    char buf[maxlen+1];
    //!@todo register appropiate signals
    if(user){
        sprintf(buf, "%s %s %s %s",
            user->fname, user->lname, user->email, user->phone);
        len = strlen(buf);
        buf[len-1] = '\0';
        outstr = malloc(len+1);
        if(outstr == NULL){
            perror("user_string()");
            raise(OP_MEMORY);
        }
        strncpy(outstr, buf, len);
    }else{
        outstr = malloc(1);
        if(outstr == NULL){
            perror("user_string()");
            raise(OP_MEMORY);
        }
        strcpy(outstr, "");
    }
    return len;
}

// ---
static UserInfo* malloc_user(
    const char *fnm, const char *lnm, const char *eml, const char *fon){
    signal(OP_MEMORY, bank_event_handler);
    UserInfo *user;
    user = (UserInfo*)malloc(sizeof(*user));
    if(user == NULL){
        perror("create_user()");
        raise(OP_MEMORY);
    }
    strncpy(user->fname, fnm, BANKLEN);
    strncpy(user->lname, lnm, BANKLEN);
    strncpy(user->email, eml, BANKLEN);
    strncpy(user->phone, fon, BANKLEN);
    user->to_string = user_string;
    return user;
}

// ---
void free_user(UserInfo* info){
    signal(OP_UNKNOWN, bank_event_handler);
    if(info){
        free(info);
        info->email[0] = '\0';
        info->fname[0] = '\0';
        info->lname[0] = '\0';
        info->phone[0] = '\0';
        info->to_string = 0;
    }else{
        perror("delete_user(): cannot delete non-existing user");
        raise(OP_UNKNOWN);
    }
}

// ---
static void copy_user(UserInfo *to, const UserInfo *from){
    if(to){ delete_user(to); }
    to = create_user(from->fname, from->lname, from->email, from->email);
}

// --------------
//  Account Info
// --------------
CUSTOM_XVECTOR(Transaction)

struct Account_{
    UserInfo *user;
    char password[BANKLEN+1];
    double balance;
    int id;
    char *filename;
    char *sline;
    XVector_t *transactions;
    char* (*to_string)(const Account *self);
};

//! @todo
static char* read_password(Account *self){}
static int load_account_transactions(Account *account){}
static void save_account_transactions(const Account *account){}
static void add_account_transaction(
    Account *account, const Transaction *trans){}
static char* account_string(const Account *self){}
static Account *create_account();
static void delete_account(Account *);
static void copy_account(Account *to, const Account *from){}


// -------------
//  Bank Object
// -------------
// customerfile
// for each customer: transactionfile
CUSTOM_XVECTOR(Account)

struct Bank_{
    char name[BANK_NAMELEN+1];
    char cfile[BANK_NAMELEN+1+BANKLEN+1];
    char sfile[BANK_NAMELEN+1+BANKLEN+1];
    XVector_t *accounts;
    char **secrets;
};

Bank* load_bank_data(){}
void save_bank_data(const Bank *bank){}
const Account* get_all_accounts(const Bank *bank){}
void print_all_accounts(const Bank *bank){}

static void parse_secret(Account *account, char *data){}
static void load_secrets(Bank *bank){}
static void save_secrets(const Bank *bank){}

static void load_accounts(Bank *bank){}
static int save_accounts(const Bank *bank){}

void add_bank_account(Bank *bank, const Account *account){}
void close_bank_account(Bank *bank, Account *account){}

void user_login(Bank *bank, const Account *account, const char *password){}

void make_withdraw(Bank *bank, Account *account, double amnt){}
void make_deposit(Bank *bank, Account *account, double amnt){}
void make_transfer(
    Bank *bank, const Account *sendAcc, double amnt, Account *recvAcc){}
void check_account_detail(Bank *bank, const Account *account){}

//! @todo ----
double check_account_balance(const Account *account){}
Transaction* get_account_transactions(const Account *account){}
UserInfo* get_account_user_info(const Account *account){}
// -------------------
// internal structure
// -------------------
typedef struct{
    int ncustomers;
    int ntransactions;
    double asset;
    double avg_transactions;
}BankReport;
static BankReport *create_bank_report(){}
static BankReport *delete_bank_report(BankReport *bkreport){}
void print_bank_report(const Bank *bank){}
