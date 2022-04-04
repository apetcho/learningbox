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
static int enter_new_catalog_entries(CatalogEntry *entry);
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

    return EXIT_SUCCESS;
}

// ------------------------ LOCAL ROUTINES -----------------------------
static int command_mode(int argc, char **argv){}
static void announce(void){}
static MenuOption show_menu(const CatalogEntry *current){}
static int get_confirm(const char *question){}
static int enter_new_catalog_entries(CatalogEntry *entry){}
static void enter_new_track_entries(const CatalogEntry *entry){}
static void delete_catalog_entries(const CatalogEntry *entry){}
static void delete_track_entries(const CatalogEntry *entry){}
static CatalogEntry find_catalog(void){}
static void list_tracks(const CatalogEntry *entry){}
static void count_all_entries(void){}
static void display_catalog(const CatalogEntry *entry){}
static void display_track(const TrackEntry *entry){}
static void strip_return(char *text){}
