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
    //! @todo
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

void db_close(void){
    //! @todo
}

// data retrieval
CatalogEntry get_catalog_entry(const char *catalog_ptr){
    //! @todo
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
