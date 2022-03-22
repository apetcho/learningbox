#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<time.h>

#include "maze.h"

static void _save_status(const char *filename, const char* info){
    FILE *fp = fopen(filename, "wa");
    if(fp == NULL){
        fprintf(stderr, "main(): %s", strerror(errno));
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "\n%s.\n", info);
    if(fp){fclose(fp);}
    return;
}

int main(){
    srand((unsigned)time(NULL));
    const char *omazefile = "maze.out";
    const char *imazefile = "maze.in";
    maze_grid_shape();
    maze_generate_random(imazefile);
    maze_read_file(imazefile);

    if(maze_find_path(xstart, ystart)){
        maze_print();
    }
    else{
        maze_save_file(omazefile);
        _save_status(omazefile, "No Solution.");
        return EXIT_FAILURE;
    }
    maze_save_file(omazefile);
    _save_status(omazefile, "Maze Solved");
    return EXIT_SUCCESS;
}
