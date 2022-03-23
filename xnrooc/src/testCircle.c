#include "xnr_circle.h"
#include "xnr_object.h"


int main(int argc, char **argv){
    void *xnrobj;

    while(* ++argv){
        switch(**argv){
        case 'c':
            xnrobj = xnr_new(xnr_circle, 1, 2, 3);
            break;
        case 'p':
            xnrobj = xnr_new(xnr_point, 1, 2);
            break;
        default:
            continue;
        }
        xnr_draw(xnrobj);
        xnr_point_move(xnrobj, 10, 20);
        xnr_draw(xnrobj);
        xnr_delete(xnrobj);
    }
    return 0;
}
