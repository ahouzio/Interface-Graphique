#include "ei_draw.h"
#include "ei_types.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_utils.h"


ei_linked_point_t *arc    (int rayon, float angle_debut, float angle_fin, ei_point_t centre) {
        ei_linked_point_t* liste_arc = calloc(1, sizeof(ei_linked_point_t));
        int nbr_point = 30;
        float angle_epsilon = (angle_fin - angle_debut) / nbr_point;
        float angle = angle_debut;
        liste_arc->point.x = rayon*cos(angle) + centre.x;
        liste_arc->point.y = -rayon*sin(angle) + centre.y;
        liste_arc->next = malloc(sizeof(ei_linked_point_t));
        angle += angle_epsilon;
        ei_linked_point_t *precedent = liste_arc;
        ei_linked_point_t *current = liste_arc->next;
        while (angle <= angle_fin) {
                current->point.x = rayon*cos(angle) + centre.x;
                current->point.y = -rayon*sin(angle) + centre.y;
                current->next = calloc(1,sizeof(ei_linked_point_t));
                angle += angle_epsilon;
                precedent->next = current;
                precedent = current;
                current = current->next;
        }
        precedent->next = NULL;
        return liste_arc;
}


ei_linked_point_t *     rounded_frame (ei_rect_t* rect, int rayon, ei_partie_button position) {


        ei_point_t centreupleft;            /* center of the upleft arc  */
        int translation = floor(rayon * (1/sqrt(2)));
        centreupleft.x = rect->top_left.x + translation;
        centreupleft.y = rect->top_left.y + translation;

        ei_point_t centreupright;              /* center of the upright arc  */
        centreupright.x = rect->top_left.x + rect->size.width - translation;
        centreupright.y = rect->top_left.y + translation;

        ei_point_t centredownleft;             /* center of the downleft arc  */
        centredownleft.x = rect->top_left.x + translation;
        centredownleft.y = rect->top_left.y + rect->size.height - translation;

        ei_point_t centredownright;            /* center of the downright arc  */
        centredownright.x = rect->top_left.x + rect->size.width - translation;
        centredownright.y = rect->top_left.y + rect->size.height - translation;

        ei_linked_point_t* mid_point_1 = malloc(sizeof(ei_linked_point_t));
        mid_point_1->point.y = rect->top_left.y + rect->size.height/2;
        mid_point_1->point.x = rect->size.height / 2 + rect->top_left.x;
        mid_point_1->next = NULL;

        ei_linked_point_t* mid_point_2 = malloc(sizeof(ei_linked_point_t));
        mid_point_2->point.y = rect->top_left.y + rect->size.height/2;
        mid_point_2->point.x = rect->top_left.x - rect->size.height / 2 + rect->size.width;
        mid_point_2->next = NULL;

        ei_linked_point_t *list1 = arc(rayon, pi/2, pi, centreupleft);  /*  upleft arc */
        ei_linked_point_t *list4_1 = arc(rayon, 0, pi/4, centreupright);     /*  upright first half arc  */
        ei_linked_point_t *list4_2 = arc(rayon, pi/4, pi/2, centreupright);     /*  upright second half arc  */
        ei_linked_point_t *list2_1 = arc(rayon, pi, 5*pi/4, centredownleft);      /* downleft first half arc  */
        ei_linked_point_t *list2_2 = arc(rayon, 5*pi/4, 3*pi/2, centredownleft);      /* downleft second half arc  */
        ei_linked_point_t *list3 = arc(rayon, 3*pi/2, 2*pi, centredownright);      /* downright arc  */

        if (position == partie_complete) {

                ei_linked_point_t *list_rounded = list1;


                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list2_1;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list2_2;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list3;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list4_1;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list4_2;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }
                list_rounded->next = list1;


                return list1;
        }

        if (position == partie_haute) {

                ei_linked_point_t *list_round = list4_2;

                while (list_round->next != NULL) {
                        list_round = list_round->next;
                }

                list_round->next = list1;

                while (list_round->next != NULL) {
                        list_round = list_round->next;
                }

                list_round->next = list2_1;

                while (list_round->next != NULL) {
                        list_round = list_round->next;
                }

                list_round->next = mid_point_1;
                list_round = list_round->next;

                list_round->next = mid_point_2;
                list_round = list_round->next;

                list_round->next = list4_2;

                return list4_2;
        }

        if (position == partie_basse) {

                ei_linked_point_t *list_rounded = list2_2;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list3;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list4_1;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = mid_point_2;
                list_rounded = list_rounded->next;

                list_rounded->next = mid_point_1;
                list_rounded = list_rounded->next;

                list_rounded->next = list2_2;

                return list2_2;
        }
}

ei_linked_point_t *     cute_frame (ei_rect_t* rect, int rayon, ei_partie_button position) {


        ei_point_t centreupleft;            /* center of the upleft arc  */
        int translation = floor(rayon * (1/sqrt(2)));
        centreupleft.x = rect->top_left.x + translation;
        centreupleft.y = rect->top_left.y + translation;

        ei_point_t centreupright;              /* center of the upright arc  */
        centreupright.x = rect->top_left.x + rect->size.width - translation;
        centreupright.y = rect->top_left.y + translation;

        ei_point_t centredownleft;             /* center of the downleft arc  */
        centredownleft.x = rect->top_left.x + translation;
        centredownleft.y = rect->top_left.y + rect->size.height - translation;

        ei_point_t centredownright;            /* center of the downright arc  */
        centredownright.x = rect->top_left.x + rect->size.width - translation;
        centredownright.y = rect->top_left.y + rect->size.height - translation;

        ei_linked_point_t* mid_point_1 = malloc(sizeof(ei_linked_point_t));
        mid_point_1->point.y = rect->top_left.y + rect->size.height/2;
        mid_point_1->point.x = rect->size.height / 2 + rect->top_left.x;
        mid_point_1->next = NULL;

        ei_linked_point_t* mid_point_2 = malloc(sizeof(ei_linked_point_t));
        mid_point_2->point.y = rect->top_left.y + rect->size.height/2;
        mid_point_2->point.x = rect->top_left.x - rect->size.height / 2 + rect->size.width;
        mid_point_2->next = NULL;

        ei_linked_point_t *list1 = arc(rayon, 3*pi/4, 3*pi/4, centreupleft);  /*  upleft arc */
        ei_linked_point_t *list4 = arc(rayon, pi/4, pi/4, centreupright);     /*  upright arc */
        ei_linked_point_t *list2 = arc(rayon, 5*pi/4, 5*pi/4, centredownleft);      /* downleft */
        ei_linked_point_t *list3 = arc(rayon, 7*pi/4, 7*pi/4, centredownright);      /* downright arc  */

        if (position == partie_complete) {

                ei_linked_point_t *list_rounded = list1;


                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list2;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list3;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list4;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list1;


                return list1;
        }

        if (position == partie_haute) {

                ei_linked_point_t *list_round = list4;

                while (list_round->next != NULL) {
                        list_round = list_round->next;
                }

                list_round->next = list1;

                while (list_round->next != NULL) {
                        list_round = list_round->next;
                }

                list_round->next = list2;

                while (list_round->next != NULL) {
                        list_round = list_round->next;
                }

                list_round->next = mid_point_1;
                list_round = list_round->next;

                list_round->next = mid_point_2;
                list_round = list_round->next;

                list_round->next = list4;

                return list4;
        }

        if (position == partie_basse) {

                ei_linked_point_t *list_rounded = list2;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list3;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = list4;

                while (list_rounded->next != NULL) {
                        list_rounded = list_rounded->next;
                }

                list_rounded->next = mid_point_2;
                list_rounded = list_rounded->next;

                list_rounded->next = mid_point_1;
                list_rounded = list_rounded->next;

                list_rounded->next = list2;

                return list2;
        }
}



ei_rect_t*              ei_intersect_rectangles(ei_rect_t* first_rectangle, ei_rect_t* second_rectangle){

        if (first_rectangle == NULL){
                return second_rectangle;
        }

        else if (second_rectangle == NULL){
                return first_rectangle;
        }

        ei_rect_t* rect_returned = malloc(sizeof(ei_rect_t));
        /* defining extreme points of the text rectangle */
        ei_point_t first_rectangle_top_left = first_rectangle -> top_left;
        ei_point_t first_bottom_right;
        first_bottom_right.x = first_rectangle_top_left.x + first_rectangle -> size.width;
        first_bottom_right.y = first_rectangle_top_left.y + first_rectangle -> size.height;

/* defining extreme points of the second_rectangle */
        ei_point_t clipper_top_left = second_rectangle -> top_left;
        ei_point_t clipper_bottom_right;
        clipper_bottom_right.x = clipper_top_left.x + second_rectangle -> size.width;
        clipper_bottom_right.y = clipper_top_left.y + second_rectangle -> size.height;

/* initialisation of the used second_rectangle top_left */
        rect_returned->top_left.x = (clipper_top_left.x > first_rectangle_top_left.x ? clipper_top_left
                                                                                     : first_rectangle_top_left).x;

        rect_returned->top_left.y = (clipper_top_left.y > first_rectangle_top_left.y ? clipper_top_left
                                                                                     : first_rectangle_top_left).y;

/* initialisation of used second_rectangle size */
        rect_returned->size.width =
                (clipper_bottom_right.x > first_bottom_right.x ? first_bottom_right : clipper_bottom_right).x -
                clipper_top_left.x;


        rect_returned->size.height =
                (clipper_bottom_right.y > first_bottom_right.y ? first_bottom_right : clipper_bottom_right).y -
                clipper_top_left.y;

        if (rect_returned -> size.height < 0 || rect_returned -> size. width<0){
                rect_returned -> size = ei_size_zero();
                rect_returned -> top_left = ei_point_zero();
        }

        return rect_returned;

}
void compute_anchor_pos(ei_anchor_t anchor, ei_size_t *size, ei_rect_t *rectangle, ei_point_t *anchor_position) {

        if (anchor == ei_anc_center) {
                (*anchor_position).x = rectangle->top_left.x + rectangle->size.width / 2 - size->width / 2;
                (*anchor_position).y = rectangle->top_left.y + rectangle->size.height / 2 - size->height / 2;
        }
        else if (anchor == ei_anc_north){
                (*anchor_position).x = rectangle->top_left.x + rectangle->size.width / 2 - size->width / 2;
                (*anchor_position).y = rectangle->top_left.y;
}
        else if (anchor == ei_anc_northeast) {
                (*anchor_position).x = rectangle->top_left.x + rectangle->size.width - size->width;
                (*anchor_position).y = rectangle->top_left.y;
        }
        else if (anchor == ei_anc_east) {
                (*anchor_position).x = rectangle->top_left.x + rectangle->size.width - size->width;
                (*anchor_position).y = rectangle->top_left.y + rectangle->size.height / 2 - size->height / 2;
        }
        else if (anchor == ei_anc_southeast) {
                (*anchor_position).x = rectangle->top_left.x + rectangle->size.width - size->width;
                (*anchor_position).y = rectangle->top_left.y + rectangle->size.height - size->height;
        }
        else if (anchor == ei_anc_south) {
                (*anchor_position).y = rectangle->top_left.y + rectangle->size.height - size->height;
                (*anchor_position).x = rectangle->top_left.x + rectangle->size.width / 2 - size->width / 2;
        }
        else if (anchor == ei_anc_southwest) {
                (*anchor_position).y = rectangle->top_left.y + rectangle->size.height - size->height;
                (*anchor_position).x = rectangle->top_left.x;
        }
        else if (anchor == ei_anc_west) {
                (*anchor_position).x = rectangle->top_left.x;
                (*anchor_position).y = rectangle->top_left.y + rectangle->size.height / 2 - size->height;
        }
        else
                (*anchor_position).x = rectangle->top_left.x;
                (*anchor_position).y = rectangle->top_left.y;
        }
