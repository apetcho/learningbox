#ifndef _MAZE_H
#define _MAZE_H

#define MAZE_MAXROW     20
#define MAZE_MAXCOL     20

typedef struct MazeCell_s MazeCell_t;
typedef struct Maze_s Maze_t;

const char MAZE_PATH_WALL = '#';
const char MAZE_PATH_OPEN = ' ';
const char MAZE_PATH_MARK = 'X';
const char MAZE_PATH_START = 'S';
extern int xstart;
extern int ystart;
extern Maze_t *maze;

MazeCell_t* maze_allocate_cell(int row, int col, char val);
void maze_deallocate_cell(MazeCell_t *cell);
void maze_allocate(int nrow, int ncol);
void maze_deallocate();
void maze_add_cell(MazeCell_t const *cell);
void maze_read_file(char const *filename);
void maze_save_file(char const *filename);
void maze_print();
int maze_find_path(int row, int col);
void maze_generate_random(char const *filename);
#endif
