#ifndef _MAZE_H
#define _MAZE_H

#define MAZE_MAXROW     20
#define MAZE_MAXCOL     20

const char MAZE_PATH_WALL = '#';
const char MAZE_PATH_OPEN = ' ';
const char MAZE_PATH_MARK = 'X';

typedef struct maze_cell_s{
    int row;
    int col;
    int val;
} maze_cell_t;

typedef struct maze_s{
    int nrow;
    int ncol;
    maze_cell_t *grid;
} maze_t;

maze_cell_t* maze_allocate_cell(int row, int col);
void maze_deallocate_cell(maze_cell_t *cell);
maze_t* maze_allocate();
void maze_deallocate(maze_t *maze);
void maze_add_cell(maze_t *maze, maze_cell_t const *cell);
maze_t* maze_readfile(char const *filename);
void make_writefile(char const *filename, maze_t *maze);
void maze_print(maze_t const *maze);
int maze_find_path(maze_t const *maze, int row, int col);

#endif
