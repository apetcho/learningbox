#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<signal.h>
#include<errno.h>
#include<stdio.h>
#include<time.h>

#include "maze.h"

#define MAZE_ROUTINE(name) maze_ ## name

#define MAZE_ERROR_MESSAGE(routine, fmt, ...) \
    do{\
        char buf[80];\
        sprintf(buf, "%s(): %s" , routine, strerror(errno));\
        fprintf(stderr, "%s\n", buf);\
        fprintf(stderr, fmt, __VA_ARGS__);\
        fprintf(stderr, "\n");\
    } while(0)

#define MAZE_SET_ROUTINE_INFO(index) \
    do{\
        maze_routine_index = index;\
        sprintf(maze_routine_name, "%s", maze_routines[index]);\
    }while(0)
    

struct MazeCell_s{
    int row;
    int col;
    char value;
};

struct Maze_s{
    int nrow;
    int ncol;
    MazeCell_t* grid[MAZE_MAXROW+1][MAZE_MAXCOL+1];
};

typedef enum {
    MAZE_EVENT_NONE = 100,
    MAZE_EVENT_MEMORY_ERROR,
    MAZE_EVENT_RUNTIME_ERROR,
    MAZE_EVENT_INVALID_DATA
} MazeEvent_t;

enum MazeRoutine_e {
    ALLOCATE_CELL,
    ALLOCATE_MAZE,
    DEALLOCATE_CELL,
    DEALLOCATE_MAZE,
    ADD_CELL,
    READ_FILE,
    SAVE_FILE,
    PRINT,
    FIND_PATH,
    GRID_SHAPE,
    GENERATE_RANDOM
};
typedef enum MazeRoutine_e MazeRoutine_t;

int xstart = -1;
int ystart = -1;
int nrow = -1;
int ncol = -1;
Maze_t *maze = NULL;
static char maze_routine_name[20];
static MazeRoutine_t maze_routine_index;

static char* maze_routines[] = {
    /*[ALLOCATE_CELL] =*/ (char*)MAZE_ROUTINE(allocate_cell),
    /*[ALLOCATE_MAZE] =*/ (char*)MAZE_ROUTINE(allocate),
    /*[DEALLOCATE_CELL] =*/ (char*)MAZE_ROUTINE(deallocate_cell),
    /*[DEALLOCATE_MAZE] =*/ (char*)MAZE_ROUTINE(deallocate),
    /*[ADD_CELL] = */ (char*)MAZE_ROUTINE(add_cell),
    /*[READ_FILE] =*/ (char*)MAZE_ROUTINE(read_file),
    /*[SAVE_FILE] */ (char*)MAZE_ROUTINE(save_file),
    /*[PRINT] =*/ (char*)MAZE_ROUTINE(print),
    /*[FIND_PATH] =*/ (char*)MAZE_ROUTINE(find_path),
    /**/ (char*)MAZE_ROUTINE(grid_shape),
    /*[GENERATE_RANDOM] =*/ (char*)MAZE_ROUTINE(generate_random),
    NULL
};
//
static void maze_signal_handler(int maze_signum){
    char message[80];
    switch(maze_signum){
    case MAZE_EVENT_NONE:
        return;
    case MAZE_EVENT_INVALID_DATA:
        sprintf(message, "invalid data.");
        MAZE_ERROR_MESSAGE(maze_routine_name, "%s\n", message);
        if(maze){ maze_deallocate();}
        exit(EXIT_FAILURE);
    case MAZE_EVENT_MEMORY_ERROR:
        sprintf(message, "memory error.");
        MAZE_ERROR_MESSAGE(maze_routine_name, "%s\n", message);
        if(maze){ maze_deallocate();}
        exit(EXIT_FAILURE);
    case MAZE_EVENT_RUNTIME_ERROR:
        sprintf(message, "runtime error.");
        MAZE_ERROR_MESSAGE(maze_routine_name, "%s\n", message);
        if(maze){ maze_deallocate();}
        exit(EXIT_FAILURE);
    default:
        break;
    }

    return;
}

//
static void maze_set_routine_info(MazeRoutine_t routine){
    switch(routine){
    case ALLOCATE_CELL:
        MAZE_SET_ROUTINE_INFO(ALLOCATE_CELL);
        break;
    case ALLOCATE_MAZE:
        MAZE_SET_ROUTINE_INFO(ALLOCATE_MAZE);
        break;
    case DEALLOCATE_CELL:
        MAZE_SET_ROUTINE_INFO(DEALLOCATE_CELL);
        break;
    case DEALLOCATE_MAZE:
        MAZE_SET_ROUTINE_INFO(DEALLOCATE_MAZE);
        break;
    case ADD_CELL:
        MAZE_SET_ROUTINE_INFO(ADD_CELL);
        break;
    case SAVE_FILE:
        MAZE_SET_ROUTINE_INFO(SAVE_FILE);
        break;
    case READ_FILE:
        MAZE_SET_ROUTINE_INFO(READ_FILE);
    case PRINT:
        MAZE_SET_ROUTINE_INFO(PRINT);
        break;
    case FIND_PATH:
        MAZE_SET_ROUTINE_INFO(FIND_PATH);
        break;
    case GRID_SHAPE:
        MAZE_SET_ROUTINE_INFO(GRID_SHAPE);
        break;
    case GENERATE_RANDOM:
        MAZE_SET_ROUTINE_INFO(GENERATE_RANDOM);
        break;
    default:
        break;
    }
    return;
}

static void maze_error(int maze_signum, MazeRoutine_t routineIndex){
    maze_set_routine_info(routineIndex);
    switch(maze_signum){
    case MAZE_EVENT_NONE:
        raise(MAZE_EVENT_NONE);
        break;
    case MAZE_EVENT_INVALID_DATA:
        raise(MAZE_EVENT_INVALID_DATA);
        break;
    case MAZE_EVENT_MEMORY_ERROR:
        raise(MAZE_EVENT_MEMORY_ERROR);
        break;
    case MAZE_EVENT_RUNTIME_ERROR:
        raise(MAZE_EVENT_RUNTIME_ERROR);
        break;
    default:
        break;
    }
    return;
}

//
MazeCell_t* maze_allocate_cell(int row, int col, char val){
    signal(MAZE_EVENT_MEMORY_ERROR, maze_signal_handler);
    MazeCell_t *cell = (MazeCell_t*)malloc(sizeof(*cell));
    if(cell == NULL){
        maze_error(MAZE_EVENT_MEMORY_ERROR, ALLOCATE_CELL);
        return NULL;
    }
    cell->col = col;
    cell->row = row;
    cell->value = val;
    return cell;
}

//
void maze_deallocate_cell(MazeCell_t *cell){
    if(cell != NULL){
        free(cell);
    }
    cell = NULL;
    return;
}

//
void maze_allocate(int nrow, int ncol){
    signal(MAZE_EVENT_INVALID_DATA, maze_signal_handler);
    if((nrow<=0) || (nrow>MAZE_MAXROW) || (ncol<=0) || (ncol>MAZE_MAXCOL)){
        maze_error(MAZE_EVENT_INVALID_DATA, ALLOCATE_MAZE);
        return;
    }
    signal(MAZE_EVENT_MEMORY_ERROR, maze_signal_handler);
    maze = (Maze_t*)malloc(sizeof(*maze));
    if(maze == NULL){
        maze_error(MAZE_EVENT_MEMORY_ERROR, ALLOCATE_MAZE);
        return;
    }
    maze->ncol = ncol;
    maze->nrow = nrow;
    for(int i=0; i < MAZE_MAXROW; i++){
        for(int j=0; j < MAZE_MAXCOL; j++){
            maze->grid[i][j] = NULL;
        }
    }
    return;
}

void maze_deallocate(){
    if(maze != NULL){
        int nrow = maze->nrow;
        int ncol = maze->ncol;
        for(int i=0; i < nrow; i++){
            for(int j=0; j < ncol; j++){
                if(maze->grid[i][j] != NULL){
                    maze_deallocate_cell(maze->grid[i][j]);
                }
            }
        }
        free(maze);
    }
    maze = NULL;
    return;
}

//
void maze_add_cell(MazeCell_t *cell){
    signal(MAZE_EVENT_INVALID_DATA, maze_signal_handler);
    if(maze == NULL || cell == NULL){
        maze_error(MAZE_EVENT_INVALID_DATA, ADD_CELL);
    }
    int x = cell->row;
    int y = cell->col;
    maze->grid[x][y] = cell;
}

//
void maze_read_file(char const *filename){
    int nrow;
    int ncol;
    MazeCell_t* cell;
    signal(MAZE_EVENT_RUNTIME_ERROR, maze_signal_handler);
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        maze_error(MAZE_EVENT_RUNTIME_ERROR, READ_FILE);
        return;
    }
    fscanf(fp, "%d %d %d %d", &nrow, &ncol, &xstart, &ystart);
    maze_allocate(nrow, ncol);
    char value;
    int ival;
    for(int i=0; i < nrow; i++){
        for(int j=0; j < ncol; j++){
            if(i == xstart && j == ystart){
                value = MAZE_PATH_START;
                cell = maze_allocate_cell(xstart, ystart, value);
                maze_add_cell(cell);
            }
            fscanf(fp, "%d", &ival);
            if(ival == 1){ value = MAZE_PATH_WALL; }
            else if(ival==0){ value = MAZE_PATH_OPEN; }
            else if(ival==2){ value = MAZE_PATH_START; }
            //else{ value = MAZE_PATH_MARK; }
            cell = maze_allocate_cell(i, j, value);
            maze_add_cell(cell);
        }
    }
    if(fp){fclose(fp);}
    return;
}

//
void maze_save_file(char const *filename){
    signal(MAZE_EVENT_RUNTIME_ERROR, maze_signal_handler);
    signal(MAZE_EVENT_INVALID_DATA, maze_signal_handler);
    if(maze == NULL){
        maze_error(MAZE_EVENT_INVALID_DATA, SAVE_FILE);
        return;
    }
    int nrow = maze->nrow;
    int ncol = maze->ncol;
    //char cval;
    FILE *fp;
    MazeCell_t *cell;
    fp = fopen(filename, "w");
    if(fp == NULL){
        maze_error(MAZE_EVENT_RUNTIME_ERROR, SAVE_FILE);
        return;
    }
    fprintf(fp, "%d %d %d %d\n", nrow, ncol, xstart, ystart);
    int xyval;
    for(int i=0; i < nrow; i++){
        for(int j=0; j < ncol; j++){
            cell = maze->grid[i][j];
            if(cell->value == MAZE_PATH_WALL){ xyval = 1; }
            else if(cell->value == MAZE_PATH_START){ xyval = 2; }
            else if(cell->value == MAZE_PATH_MARK){ xyval = 0; }
            else if(cell->value == MAZE_PATH_OPEN){ xyval = 0; }
            fprintf(fp, "%d", xyval);
        }
        putc('\n', fp);
    }

    if(fp){fclose(fp);}
    maze_deallocate();
    return;
}

//
void maze_print(){
    signal(MAZE_EVENT_INVALID_DATA, maze_signal_handler);
    if(maze == NULL){
        maze_error(MAZE_EVENT_INVALID_DATA, PRINT);
        return;
    }
    int nrow = maze->nrow;
    int ncol = maze->ncol;
    //char cval;
    FILE *fp;
    MazeCell_t *cell;
    fp = stdout;

    for(int i=0; i < nrow; i++){
        for(int j=0; j < ncol; j++){
            cell = maze->grid[i][j];
            fprintf(fp, "%c", cell->value);
        }
        putc('\n', fp);
    }
    return;
}

//
int maze_find_path(int x, int y){
    signal(MAZE_EVENT_INVALID_DATA, maze_signal_handler);
    if(maze == NULL){
        maze_error(MAZE_EVENT_INVALID_DATA, FIND_PATH);
        return -1;
    }
    int nrow = maze->nrow;
    int ncol = maze->ncol;
    MazeCell_t *cell;
    if((x < 1) || (x > nrow) || (y < 1) || (y > ncol)){
        return 0;
    }
    cell = maze->grid[x][y];
    if(cell->value == MAZE_PATH_WALL){ return 0; }
    if(cell->value == MAZE_PATH_MARK){ return 0; }
    cell->value = MAZE_PATH_OPEN;
    if((x==1)||(x==nrow) || (y==1)||(y==ncol)){ return 1; }
    cell->value = MAZE_PATH_MARK;
    if(maze_find_path(x-1, y)){ return 1; }
    if(maze_find_path(x, y+1)){ return 1; }
    if(maze_find_path(x+1, y)){ return 1; }
    if(maze_find_path(x, y-1)){ return 1; }
    cell->value = MAZE_PATH_OPEN;

    return 0;
}

//
static char get_probability(int x, int y){
    double maxval = (double)(MAZE_MAXCOL * MAZE_MAXROW);
    int nrow = rand() % 10 + 10;
    int ncol = rand() % 10 + 10;
    double a = (double)(x*nrow)/(double)MAZE_MAXROW;
    double b = (double)(y*ncol)/(double)MAZE_MAXCOL;
    double xy = (double)(rand()%16+1) / (double)MAZE_MAXROW;
    char prob;
    double val = (a*b)/maxval;
    prob = (val < xy) ? MAZE_PATH_WALL : MAZE_PATH_OPEN; 
    //printf("%.2lf\n", prob);
    return prob;
}

//
void maze_grid_shape(){
    nrow = rand() % 10 + 10;
    ncol = rand() % 10 + 10;
    xstart = rand() % (nrow/2) + (nrow/5);
    ystart = rand() % (ncol/2) + (ncol/5);
}
//
void maze_generate_random(char const *filename){
    /*printf("nrow = %d\n", nrow);
    printf("ncol = %d\n", ncol);
    printf("xstart = %d\n", xstart);
    printf("ystart = %d\n", ystart);*/
    maze_allocate(nrow, ncol);
    char cval;
    MazeCell_t *cell;

    for(int i=0; i < nrow; i++){
        for(int j=0; j < ncol; j++){
            if((i==xstart) || (j==ystart)){
                cval = MAZE_PATH_START;
                cell = maze_allocate_cell(xstart, ystart, cval);
                maze_add_cell(cell);
            }
            cval = get_probability(i, j);
            cell = maze_allocate_cell(i, j, cval);
            maze_add_cell(cell);
        }
    }
    cell = NULL;
    maze_save_file(filename);
    return;
}
