#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#include "maze.h"


int main(){
    const char *omazefile = "maze.out";
    const char *imazefile = "maze.in";
    maze_generate_random(imazefile);

    if(maze_find_path(xstart, ystart)){
        maze_print();
        maze_save_file(omazefile);
        FILE *fp = fopen(omazefile, "wa");
        if(fp == NULL){
            fprintf(stderr, "main(): %s", strerror(errno));
            return EXIT_FAILURE;
        }
        fprintf(fp, "\nMaze Soved.\n");
        if(fp){fclose(fp);}
    }
    else{
        maze_save_file(omazefile);
        FILE *fp = fopen(omazefile, "wa");
        if(fp == NULL){
            fprintf(stderr, "main(): %s", strerror(errno));
            return EXIT_FAILURE;
        }
        fprintf(fp, "\nNo solution.\n");
        if(fp){fclose(fp);}
    }
    if(maze){ maze_deallocate(); }
    return EXIT_SUCCESS;
}
