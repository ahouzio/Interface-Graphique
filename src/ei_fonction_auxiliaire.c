#include "ei_types.h"
#include "ei_application.h"
#include <stdio.h>

int max(int a, int b){
        if (a > b) {
                return a;
        }
        return b;
}


int min(int a, int b){
        if (a < b) {
                return a;
        }
        return b;
}

void permuter(int *a, int *b ){
        int tmp = *a;
        *a = *b;
        *b = tmp;
}


ei_bool_t clipping(const ei_rect_t* clipper, int point_abscissa , int point_orderly){
        if (clipper == NULL){
                return EI_TRUE;
        }
        ei_point_t top = clipper->top_left;
        int x = point_abscissa - top.x;
        int y = point_orderly - top.y;
        return 0<=x && x<= clipper->size.width && 0<=y && y<= clipper->size.height? EI_TRUE: EI_FALSE;
}


void ei_free_linked_point (ei_linked_point_t** first_point){
        ei_linked_point_t* current_point = (*first_point) -> next;
        while(current_point!= first_point){
                (*first_point) -> next = current_point -> next;
                free(current_point);
                current_point = (*first_point) -> next;
        }
        free( *first_point);

}
