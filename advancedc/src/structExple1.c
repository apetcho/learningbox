#include<stdlib.h>
#include<string.h>
#include<stdio.h>

//
int main(){
    struct {
        char text[80];
        int len;
    }data[] = {
        {.text="Firestone's Law of Forecaseing:", .len=0},
        {.text="Chicken Little has to be right only once.", .len=0},
        {.text="", .len=0},
        {.text="", .len=0},
        {.text="Moer's truism:", .len=0},
        {.text="    The trouble with most jobs is the holder's", .len=0},
        {.text="    resemblance to being one of a seld dog team. No one",
            .len=0},
        {.text="    gets a change of scenery except the lead dog.", .len=0},
        {.text="", .len=0},
        {.text="", .len=0},
        {.text="Cannon's Comment:", .len=0},
        {.text="    If you tell the boss you were late for work because you",
            .len=0},
        {.text=
            "    had a flad tire, the next morning you will have a flat tire.",
            .len=0},
    };

    for(int i=0; i < sizeof(data)/sizeof(data[0]); i++){
        data[i].len = strlen(data[i].text);
    }

    printf("sizeof(data) = %lu\n", sizeof(data));
    printf("Number of elements = %lu\n", sizeof(data)/sizeof(data[0]));
    for(int i=0; i < sizeof(data)/sizeof(data[0]); i++){
        printf(
            "data[%2d] %p %3d '%s'\n",
            i, &data[i].text, data[i].len, data[i].text
        );
    }
    puts("\n");

    return EXIT_SUCCESS;
}
