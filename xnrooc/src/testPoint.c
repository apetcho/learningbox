#include "xnr_point.h"
#include "xnr_object.h"

//
int main(int argc, char **argv){
    void *pt;
    while(* ++argv){
        switch(**argv){
        case 'p':
            pt = xnr_new(xnr_point, 1, 2);
            break;
        default:
            continue;
        }
        xnr_draw(pt);
        xnr_point_move(pt, 10, 20);
        xnr_draw(pt);
        xnr_delete(pt);
    }

    return 0;
}
