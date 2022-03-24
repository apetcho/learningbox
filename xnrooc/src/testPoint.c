#include "xnr_point.h"

//
int main(int argc, char **argv){
    void *pt;
    xnr_init_point();
    
    while(* ++argv){
        switch(**argv){
        case 'p':
            pt = xnr_new(xnr_point, 1, 2);
            break;
        default:
            continue;
        }
        xnr_draw(pt);
        xnr_move(pt, 10, 20);
        xnr_draw(pt);
        xnr_delete(pt);
    }

    return 0;
}
