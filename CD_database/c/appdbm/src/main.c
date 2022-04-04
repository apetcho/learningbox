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
static void delete_catalog_entries(const CatalogEntry *entry);
static void delete_track_entries(const CatalogEntry *entry);
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
            delete_catalog_entries(&c_entry);
            break;
        case MO_FIND_CAT:
            c_entry = find_catalog();
            break;
        case MO_LIST_CAT_TRACKS:
            list_tracks(&c_entry);
            break;
        case MO_DEL_TRACKS:
            delete_track_entries(&c_entry);
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
static int command_mode(int argc, char **argv){}
static void announce(void){}
static MenuOption show_menu(const CatalogEntry *current){}
static int get_confirm(const char *question){}
static int enter_new_catalog_entry(CatalogEntry *entry){}
static void enter_new_track_entries(const CatalogEntry *entry){}
static void delete_catalog_entries(const CatalogEntry *entry){}
static void delete_track_entries(const CatalogEntry *entry){}
static CatalogEntry find_catalog(void){}
static void list_tracks(const CatalogEntry *entry){}
static void count_all_entries(void){}
static void display_catalog(const CatalogEntry *entry){}
static void display_track(const TrackEntry *entry){}
static void strip_return(char *text){}
