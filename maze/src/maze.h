#ifndef _MAZE_H
#define _MAZE_H

#define MAZE_MAXROW     20
#define MAZE_MAXCOL     20

const char MAZE_PATH_WALL = '#';
const char MAZE_PATH_OPEN = ' ';
const char MAZE_PATH_MARK = 'X';

typedef struct MazeCell_s MazeCell_t;

typedef struct Maze_s Maze_t;

MazeCell_t* maze_allocate_cell(int row, int col);
void maze_deallocate_cell(MazeCell_t *cell);
Maze_t* maze_allocate();
void maze_deallocate(Maze_t *maze);
void maze_add_cell(Maze_t *maze, MazeCell_t const *cell);
Maze_t* maze_read_file(char const *filename);
void maze_write_file(char const *filename, Maze_t *maze);
void maze_print(Maze_t const *maze);
int maze_find_path(Maze_t const *maze, int row, int col);

#endif
