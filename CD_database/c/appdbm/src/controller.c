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


int db_initialize(const int newdb){
    //! @todo
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
