#include "ei_placer.h"
#include "ei_widget.h"
#include "ei_types.h"
#include <stdlib.h>
#include <stdio.h>


void		ei_place	(struct ei_widget_t*	widget,
                                     ei_anchor_t*		anchor,
                                     int*			x,
                                     int*			y,
                                     int*			width,
                                     int*			height,
                                     float*			rel_x,
                                     float*			rel_y,
                                     float*			rel_width,
                                     float*			rel_height) {

        ei_placer_params_t* placer_params = malloc(sizeof(ei_placer_params_t));
        widget->placer_params = placer_params;

        if (anchor != NULL) {
                placer_params->anchor = anchor;
                placer_params->anchor_data = *anchor;
        }else{
                placer_params->anchor_data = ei_anc_northwest;
                placer_params->anchor = &(placer_params->anchor_data);
        }

        if (x != NULL) {
                placer_params->x = x;
                placer_params->x_data = *x;
        }else{
                placer_params->x_data = 0;
                placer_params->x = &(placer_params->x_data);
        }

        if (y != NULL) {
                placer_params->y = y;
                placer_params->y_data = *y;
        }else{
                placer_params->y_data = 0;
                placer_params->y = &(placer_params->y_data);
        }

        if (width != NULL) {
                placer_params->w = width;
                placer_params->w_data = *width;
        }else{
                if (rel_width == NULL) {
                        placer_params->w_data = widget->requested_size.width;
                } else {
                        placer_params->w_data = 0;
                }
                placer_params->w = &(placer_params->w_data);
        }

        if (height != NULL) {
                placer_params->h = height;
                placer_params->h_data = *height;
        }else{
                if (rel_height == NULL) {
                        placer_params->h_data = widget->requested_size.height;
                } else {
                        placer_params->h_data = 0;
                }
                placer_params->h = &(placer_params->h_data);
        }

        if (rel_x != NULL) {
                placer_params->rx = rel_x;
                placer_params->rx_data = *rel_x;
        }else{
                placer_params->rx_data = 0.0;
                placer_params->rx = &(placer_params->rx_data);
        }

        if (rel_y != NULL) {
                placer_params->ry = rel_y;
                placer_params->ry_data = *rel_y;
        }else{
                placer_params->ry_data = 0.0;
                placer_params->ry = &(placer_params->ry_data);
        }

        if (rel_height != NULL) {
                placer_params->rh = rel_height;
                placer_params->rh_data = *rel_height;
        }else{

                placer_params->rh_data = 0.0;
                placer_params->rh = &(placer_params->rh_data);
        }

        if (rel_width != NULL) {
                placer_params->rw = rel_width;
                placer_params->rw_data = *rel_width;
        }else{
                placer_params->rw_data = 0.0;
                placer_params->rw = &(placer_params->rw_data);
        }



}

void ei_placer_run(struct ei_widget_t* widget) {


}
