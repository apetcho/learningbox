/** Demonstration of pointers and indirection. */
#include<stdio.h>
#include<string.h>

// ---
int main(){
    int nCounter = 33;
    int *pnCounter = (int*)NULL;
    char szSaying[] = {
        "Firestone's Law of Forecasting:\n"
        "Chicken Little only has to be right one.\n\n"
    };
    char *pszSaying = (char*)NULL;
    printf(
        "nCounter | pnCounter | *(pnCounter) | pszSaying | "
        "szSaying[0] | szSaying[0-20]\n"
    );
    printf(
        "%8d | %8p |  %8d  | %8p |   %c     | %20.20s\n",
        nCounter, pnCounter, *(pnCounter), pszSaying, *(pszSaying), szSaying
    );

    printf("pnCounter = &nCounter; \n");
    pnCounter = &nCounter;

    printf(
        "%8d |  %8p |  %8d  | %8p |   %c     | %20.20s\n",
        nCounter, pnCounter, *(pnCounter), pszSaying, *(pszSaying), szSaying
    );

    printf("pszSaying = szSaying;\n");
    pszSaying = szSaying;
    printf(
        "%8d |  %8p |  %8d  | %8p |   %c     | %20.20s\n",
        nCounter, pnCounter, *(pnCounter), pszSaying, *(pszSaying), szSaying
    );
    printf("pszSaying = &szSaying;\n");
    pszSaying = &szSaying;
    printf(
        "%8d |  %8p |  %8d  | %8p |   %c     | %20.20s\n",
        nCounter, pnCounter, *(pnCounter), pszSaying, *(pszSaying), szSaying
    );
    printf("pszSaying = &szSaying[0]; \n");
    pszSaying = &szSaying[0];
    printf(
        "%8d |  %8p |  %8d  | %8p |   %c     | %20.20s\n",
        nCounter, pnCounter, *(pnCounter), pszSaying, *(pszSaying), szSaying
    );
    printf("*(pnCounter) = 1234; \n");
    *(pnCounter) = 1234;
    printf(
        "%8d |  %8p |  %8d  | %8p |   %c     | %20.20s\n",
        nCounter, pnCounter, *(pnCounter), pszSaying, *(pszSaying), szSaying
    );

    return 0;
}
