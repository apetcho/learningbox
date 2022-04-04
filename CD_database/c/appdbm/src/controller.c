#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<ndbm.h>

#include "appcommon.h"

#define CATALOG_FILE_BASE   "catalog_data"
#define TRACK_FILE_BASE     "track_data"
#define CATALOG_FILE_DIR    "catalog_data.dir"
#define CATALOG_FILE_PAG    "catalog_data.pag"
#define TRACK_FILE_DIR      "track_data.dir"
#define TRACK_FILE_PAG      "track_data.pag"

/* File scope variables */
static DBM *catalog_dbm_ptr = NULL;
static DBM *track_dbm_ptr = NULL;

/**
 * @brief Initialize access to the database
 * 
 * @param newdb If true (!0) a new database is started
 * @return int 1 if successful otherwise return 0
 */
int db_initialize(const int newdb){
    int mode = O_CREAT | O_RDWR;
    // If any existing database is open then close it
    if(catalog_dbm_ptr){ dbm_close(catalog_dbm_ptr); }
    if(track_dbm_ptr){ dbm_close(track_dbm_ptr); }

    if(newdb){
        // delete the old files
        (void)unlink(CATALOG_FILE_PAG);
        (void)unlink(CATALOG_FILE_DIR);
        (void)unlink(TRACK_FILE_PAG);
        (void)unlink(TRACK_FILE_DIR);
    }
    /* Open some new files, creating the if needed */
    catalog_dbm_ptr = dbm_open(CATALOG_FILE_BASE, mode, 0644);
    track_dbm_ptr = dbm_open(TRACK_FILE_BASE, mode, 0644);
    if(!catalog_dbm_ptr || !track_dbm_ptr){
        fprintf(stderr, "Unable to create database\n");
        perror("dbm_open");
        catalog_dbm_ptr = NULL;
        track_dbm_ptr = NULL;
        return 0;
    }
    return 1;
}

/**
 * @brief Close opened database
 */
void db_close(void){
    if(catalog_dbm_ptr){ dbm_close(catalog_dbm_ptr); }
    if(track_dbm_ptr){ dbm_close(track_dbm_ptr);}
    catalog_dbm_ptr = NULL;
    track_dbm_ptr = NULL;
}

/**
 * @brief Get the catalog entry object
 * 
 * @param catalog_ptr 
 * @return CatalogEntry 
 */
CatalogEntry get_catalog_entry(const char *catalog_ptr){
    CatalogEntry entry;
    char entry_to_find[CAT_CAT_LEN+1];
    datum data_datum;
    datum key_datum;

    memset(&entry, '\0', sizeof(entry));

    // check whether database are initialized and paramters are valid
    if(!catalog_dbm_ptr|| !track_dbm_ptr){ return entry; }
    if(!catalog_ptr){ return entry; }
    if(strlen(catalog_ptr) >= CAT_CAT_LEN){ return entry; }

    // ensure the search key contains only the valid string and nulls
    memset(&entry_to_find, '\0', sizeof(entry_to_find));
    strcpy(entry_to_find, catalog_ptr);

    key_datum.dptr = (void*)entry_to_find;
    key_datum.dsize = sizeof(entry_to_find);

    memset(&data_datum, '\0', sizeof(data_datum));
    data_datum = dbm_fetch(catalog_dbm_ptr, key_datum);
    if(data_datum.dptr){
        memcpy(&entry, (char*)data_datum.dptr, data_datum.dsize);
    }

    return entry;
}


TrackEntry get_track_entry(const char *catalog_ptr, const int trackno){
    //! @todo
}

// add entry
int add_catalog_entry(const CatalogEntry entry){
    //! @todo
}

int add_track_entry(const TrackEntry entry){
    //! @todo
}

// delete entry
int delete_catalog_entry(const char *catalog_ptr){
    //! @todo
}

int delete_track_entry(const char *catalog_ptr, const int trackno){
    //! @todo
}

// search function
CatalogEntry search_catalog_entry(const char *catalog_ptr, int *firstptr){
    //! @todo
}
