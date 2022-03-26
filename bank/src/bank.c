#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#include "bank.h"

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
void bank_exception(BankEvent_t event){}

// ---------------
//  Transaction
// ---------------
typedef struct Transaction_ Transaction_t;
struct Transaction_{
    BankEvent_t type;
    time_t when;
    size_t (*to_string)(const Transaction_t *self, char *outstr);
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

static Transaction_t *malloc_transaction(BankEvent_t type){
    signal(OP_MEMORY, bank_event_handler);
    Transaction_t *trans;
    trans = (Transaction_t *)malloc(sizeof(*trans));
    if(trans == NULL){ raise(OP_MEMORY);}
    trans->type = type;
    trans->when = time(0);
    trans->to_string = transaction_string;
    return trans;
}

// ----
static void free_transaction(Transaction_t *self){
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
static void print_transaction(const Transaction_t *self){
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
static size_t transaction_string(const Transaction_t *self, char *outstr){
    signal(OP_MEMORY, bank_event_handler);
    char buf[80];
    size_t len;
    BankEvent_t type = self->type;
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
static void copy_transaction(Transaction_t *to, const Transaction_t *from){
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
    size_t (*to_string)(const UserInfo_t *user, char* outstr);
};


static size_t user_string(const UserInfo_t *user, char *outstr){
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
            perror("usrér_string()");
            raise(OP_MEMORY);
        }
        strcpy(outstr, "");
    }
    return len;
}

// ---
static UserInfo_t* malloc_user(
    const char *fnm, const char *lnm, const char *eml, const char *fon){
    signal(OP_MEMORY, bank_event_handler);
    UserInfo_t *user;
    user = (UserInfo_t*)malloc(sizeof(*user));
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
void free_user(UserInfo_t* info){
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
static void copy_user(UserInfo_t *to, const UserInfo_t *from){
    if(to){ delete_user(to); }
    to = create_user(from->fname, from->lname, from->email, from->email);
}

// --------------
//  Account Info
// --------------
struct Account_{
    UserInfo_t *user;
    char password[BANKLEN+1];
    double balance;
    int id;
    char *filename;
    char *sline;
    Transaction_t *transactions;
    char* (*to_string)(const Account_t *self);
};

//! @todo
static char* read_password(Account_t *self){}
static int load_account_transactions(Account_t *account){}
static void save_account_transactions(const Account_t *account){}
static void add_account_transaction(
    Account_t *account, const Transaction_t *trans){}
static char* account_string(const Account_t *self){}
static Account_t *create_account();
static void delete_account(Account_t *);
static void copy_account(Account_t *to, const Account_t *from){}


// -------------
//  Bank Object
// -------------
// customerfile
// for each customer: transactionfile
typedef struct Bank_ Bank_t;

struct Bank_{
    char name[BANK_NAMELEN+1];
    char cfile[BANK_NAMELEN+1+BANKLEN+1];
    char sfile[BANK_NAMELEN+1+BANKLEN+1];
    Account_t *accounts;
    char **secrets;
};

Bank_t* load_bank_data(){}
void save_bank_data(const Bank_t *bank){}

static void parse_secret(Account_t *account, char *data){}
static void load_secrets(Bank_t *bank){}
static void save_secrets(const Bank_t *bank){}

static void load_accounts(Bank_t *bank){}
static int save_accounts(const Bank_t *bank){}

void add_bank_account(Bank_t *bank, const Account_t *account){}
void close_bank_account(Bank_t *bank, Account_t *account){}

void user_login(Bank_t *bank, const Account_t *account, const char *password){}

void make_withdraw(Bank_t *bank, Account_t *account, double amnt){}
void make_deposit(Bank_t *bank, Account_t *account, double amnt){}
void make_transfer(
    Bank_t *bank, const Account_t *sendAcc, double amnt, Account_t *recvAcc){}
void check_account_detail(Bank_t *bank, const Account_t *account){}

//! @todo ----
double check_account_balance(const Account_t *account){}
Transaction_t* get_account_transactions(const Account_t *account){}
UserInfo_t* get_account_user_info(const Account_t *account){}
// -------------------
// internal structure
// -------------------
typedef struct{
    int ncustomers;
    int ntransactions;
    double asset;
    double avg_transactions;
}BankReport_t;
static BankReport_t *create_bank_report(){}
static BankReport_t *delete_bank_report(BankReport_t *bkreport){}
void print_bank_report(const Bank_t *bank){}
