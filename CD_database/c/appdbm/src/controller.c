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

/**
 * @brief Get the track entry object
 * 
 * Retrieve a single track entry, when passed a pointer pointing to a catalog
 * string and a track number. If the entry is not found then the returned
 * data has an empty catalog field.
 * 
 * @param catalog_ptr 
 * @param trackno 
 * @return TrackEntry 
 */
TrackEntry get_track_entry(const char *catalog_ptr, const int trackno){
    TrackEntry entry;
    char entry_to_find[CAT_CAT_LEN + 10];
    datum data;
    datum key;

    memset(&entry, '\0', sizeof(entry));

    // check if the database initialized and parameters are valid
    if(!catalog_dbm_ptr || !track_dbm_ptr){ return entry; }
    if(!catalog_ptr){ return entry; }
    if(strlen(catalog_ptr) >= CAT_CAT_LEN){ return entry; }

    // --
    // setup the search key, which is a composite key of catalog entry
    // and track number
    // --
    memset(&entry_to_find, '\0', sizeof(entry_to_find));
    sprintf(entry_to_find, "%s %d", catalog_ptr, trackno);

    key.dptr = (void*)entry_to_find;
    key.dsize = sizeof(entry_to_find);

    memset(&data, '\0', sizeof(data));
    data = dbm_fetch(track_dbm_ptr, key);
    if(data.dptr){
        memcpy(&entry, (char*)data.dptr, data.dsize);
    }

    return entry;
}

/**
 * @brief Add a new catalog entry.
 * 
 * @param entry 
 * @return int 
 */
int add_catalog_entry(const CatalogEntry entry){
    char key_to_add[CAT_CAT_LEN+1];
    datum key;
    datum data;
    int result;

    // ---
    if(!catalog_dbm_ptr || !track_dbm_ptr){ return 0; }
    if(strlen(entry.catalog) >= CAT_CAT_LEN){ return 0; }

    // ---
    memset(&key_to_add, '\0', sizeof(key_to_add));
    strcpy(key_to_add, entry.catalog);

    key.dptr = (void*)key_to_add;
    key.dsize = sizeof(key_to_add);
    data.dptr = (void*)&entry;
    data.dsize = sizeof(entry);

    result = dbm_store(catalog_dbm_ptr, key, data, DBM_REPLACE);
    if(result == 0){ return 1; }
    else{ return 0; }
}

/**
 * @brief Add a new track entry.
 * 
 * @param entry 
 * @return int 
 */
int add_track_entry(const TrackEntry entry){
    //! @todo
    char key_to_add[CAT_CAT_LEN+10];
    datum data;
    datum key;
    int result;

    // ---
    if(!catalog_dbm_ptr || !track_dbm_ptr){ return 0; }
    if(strlen(entry.catalog) >= CAT_CAT_LEN){ return 0; }

    // ---
    memset(&key_to_add, '\0', sizeof(key_to_add));
    sprintf(key_to_add, "%s %d", entry.catalog, entry.trackno);

    key.dptr = (void*)key_to_add;
    key.dsize = sizeof(key_to_add);
    data.dptr = (void*)&entry;
    data.dsize = sizeof(entry);

    result = dbm_store(track_dbm_ptr, key, data, DBM_REPLACE);
    if(result == 0){ return 1; } // success
    else{ return 0; } // failure
}

/**
 * @brief Delete an entry from cd catalog
 * 
 * @param catalog_ptr 
 * @return int 
 */
int delete_catalog_entry(const char *catalog_ptr){
    char key_to_del[CAT_CAT_LEN+1];
    datum key;
    int result;

    // ---
    if(!catalog_dbm_ptr || !track_dbm_ptr){ return 0; }
    if(strlen(catalog_ptr) >= CAT_CAT_LEN){ return 0; }

    // ---
    memset(&key_to_del, '\0', sizeof(key_to_del));
    strcpy(key_to_del, catalog_ptr);

    key.dptr = (void*)key_to_del;
    key.dsize = sizeof(key_to_del);

    result = dbm_delete(catalog_dbm_ptr, key);
    if(result == 0){ return 1; }
    else{ return 0; }
}

int delete_track_entry(const char *catalog_ptr, const int trackno){
    //! @todo
}

// search function
CatalogEntry search_catalog_entry(const char *catalog_ptr, int *firstptr){
    //! @todo
}
