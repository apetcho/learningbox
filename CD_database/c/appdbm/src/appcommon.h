#ifndef _APP_COMMON_H
#define _APP_COMMON_H

//
#define CAT_CAT_LEN     30
#define CAT_TITLE_LEN   70
#define CAT_TYPE_LEN    30
#define CAT_ARTIST_LEN  70

typedef struct{
    char catalog[CAT_CAT_LEN+1];
    char title[CAT_TITLE_LEN+1];
    char type[CAT_TYPE_LEN+1];
    char artist[CAT_ARTIST_LEN+1];
}CatalogEntry;

#define TRACK_CAT_LEN       CAT_CAT_LEN
#define TRACT_TTEXT_LEN     70

typedef struct{
    char catalog[TRACK_CAT_LEN+1];
    int trackno;
    char tracktxt[TRACT_TTEXT_LEN+1];
}TrackEntry;

// Initialization and termination functions
int db_initialize(const int newdb);
void db_close(void);

// data retrieval
CatalogEntry get_catalog_entry(const char *catalog_ptr);
TrackEntry get_track_entry(const char *catalog_ptr, const int trackno);

// add entry
int add_catalog_entry(const CatalogEntry entry);
int add_track_entry(const TrackEntry entry);

// delete entry
int delete_catalog_entry(const char *catalog_ptr);
int delete_track_entry(const char *catalog_ptr, const int trackno);

// search function
CatalogEntry search_catalog_entry(const char *catalog_ptr, int *firstptr);

#endif
