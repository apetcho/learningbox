/** A program with nested structures */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


// ---
int main(){
    typedef struct{
        char *info[35];
        int lengths[35];
    } Data_t;

    struct{
        Data_t murphy;
        Data_t peter;
    }data = {
        .murphy = {
            .info={
                "Firestone's Law of Forecasting:",
                "   Chicken Little has to be right only once.",
                "",
                "",
                "Manly's Maxim:",
                "   Logic is a systematic method of coming to",
                "   the wrong conclusion with confidence.",
                "",
                "",
                "Moer's truism",
                "   The trouble with most jobs is the job holder's",
                "   resemblance to being one of a sled dog team. No one",
                "   gets a change of scenery except the lead dog.",
                "",
                "",
                "Cannon's Comment:",
                "   If you tell the boss you were late for work because you",
                "   has a flat tire, the next morning you will have a flat"
                " tire.",
                NULL,
            },
            .lengths[0] = 0,
        },
        .peter = {
            .info = {
                "David's rule:",
                "   Software should be as easy to use as a Coke machine.",
                "",
                "",
                "Peter's Maxim:",
                "   To be successful, you must work hard, but",
                "   Hard work doesn't guarantee success.",
                "",
                "",
                "Teacher's truism:",
                "   Successful people learn.",
                "",
                "",
                "Player's Comment:",
                "   If you don't play to win,",
                "   you don't win.",
                NULL
            },
            .lengths[0]=0,
        }
    };

    for(int i=0; data.murphy.info[i]; i++){
        data.murphy.lengths[i] = strlen(data.murphy.info[i]);
    }

    printf("sizeof(data.murphy) = %lu\n", sizeof(data.murphy));
    for(int i=0; data.murphy.info[i]; i++){
        printf(
            "data.murphy %p %3d '%s'\n",
            &data.murphy.info[i],
            data.murphy.lengths[i],
            data.murphy.info[i]
        );
    }

    puts("\n");
    for(int i=0; data.peter.info[i]; i++){
        data.peter.lengths[i] = strlen(data.peter.info[i]);
    }

    printf("sizeof(data.peter) = %lu\n", sizeof(data.peter));
    for(int i=0; data.peter.info[i]; i++){
        printf(
            "data.peter %p %3d '%s'\n",
            &data.peter.info[i],
            data.peter.lengths[i],
            data.peter.info[i]
        );
    }

    return EXIT_SUCCESS;
}
