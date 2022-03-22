#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<signal.h>
#include<errno.h>
#include<stdio.h>

#include "maze.h"

#define MAZE_ROUTINE(name) maze_ ## name

#define MAZE_ERROR_MESSAGE(routine, ...) \
    do{\
        char buf[80];\
        sprintf(buf, "%s(): %s", (routine), strerror(errno));\
        fprintf(stderr, "%s\n", buf);\
        fprintf(stderr, __VA_ARGS__);\
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
    MazeCell_t *grid;
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
    WRITE_FILE,
    PRINT,
    FIND_PATH
};
typedef enum MazeRoutine_e MazeRoutine_t;

static char maze_routine_name[20];
static MazeRoutine_t maze_routine_index;

static char const *const maze_routines[] = {
    [ALLOCATE_CELL] = MAZE_ROUTINE(allocate_cell),
    [ALLOCATE_MAZE] = MAZE_ROUTINE(allocate),
    [DEALLOCATE_CELL] = MAZE_ROUTINE(deallocate_cell),
    [DEALLOCATE_MAZE] = MAZE_ROUTINE(deallocate),
    [ADD_CELL] = MAZE_ROUTINE(add_cell),
    [READ_FILE] = MAZE_ROUTINE(read_file),
    [WRITE_FILE] = MAZE_ROUTINE(write_file),
    [PRINT] = MAZE_ROUTINE(print),
    [FIND_PATH] = MAZE_ROUTINE(find_path),
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
        MAZE_ERROR_MESSAGE(maze_routine_name, message);
        exit(EXIT_FAILURE);
    case MAZE_EVENT_MEMORY_ERROR:
        sprintf(message, "memory error.");
        MAZE_ERROR_MESSAGE(maze_routine_name, message);
        exit(EXIT_FAILURE);
    case MAZE_EVENT_RUNTIME_ERROR:
        sprintf(message, "runtime error.");
        MAZE_ERROR_MESSAGE(maze_routine_name, message);
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
    case WRITE_FILE:
        MAZE_SET_ROUTINE_INFO(WRITE_FILE);
        break;
    case READ_FILE:
        MAZE_SET_ROUTINE_INFO(READ_FILE);
    case PRINT:
        MAZE_SET_ROUTINE_INFO(PRINT);
        break;
    case FIND_PATH:
        MAZE_SET_ROUTINE_INFO(FIND_PATH);
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

void maze_deallocate_cell(MazeCell_t *cell);
Maze_t* maze_allocate();
void maze_deallocate(Maze_t *maze);

void maze_add_cell(Maze_t *maze, MazeCell_t const *cell);
Maze_t* maze_readfile(char const *filename);
void maze_writefile(char const *filename, Maze_t *maze);
void maze_print(Maze_t const *maze);
int maze_find_path(Maze_t const *maze, int row, int col);
