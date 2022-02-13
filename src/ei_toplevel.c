#include "ei_types.h"
#include "ei_application.h"
#include "hw_interface.h"
#include "ei_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_toplevel.h"
#include "ei_draw_funct.h"

struct widget_class* alloc_toplevel(){
        struct ei_widget_t *ptr = calloc(1, sizeof(struct ei_toplevel_t));
        return ptr;
};

void	release_toplevel	(struct ei_widget_t*	widget){

};

void	draw_toplevel	 (struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper){

        ei_toplevel_t *toplevel = (ei_toplevel_t *) widget;
        ei_color_t red = {0x0A,0x00,0x00,0xff};
        ei_rect_t *rect = toplevel->requested_size;
        ei_size_t text_size;
        hw_text_compute_size(toplevel->title, ei_default_font, &(text_size.width), &(text_size.height));

        ei_color_t bar_color = *toplevel->color;
        bar_color.alpha = toplevel->color->alpha * 0.5;


        ei_rect_t *up_bar;
        up_bar->top_left = rect->top_left;
        up_bar->size.width = rect->size.width;
        up_bar->size.height = text_size.height * 4 ;

        ei_partie_button complete = partie_complete;

        ei_linked_point_t bar = *rounded_frame(&up_bar, 20,  complete);

        ei_rect_t *main_rect;
        main_rect->top_left.x = rect->top_left.x;
        main_rect->top_left.y = rect->top_left.y + up_bar->size.height / 2;
        main_rect->size.width = rect->size.width;
        main_rect->size.height = rect->size.height - up_bar->size.height / 2;

        ei_linked_point_t win = *cute_frame(&main_rect, 20, complete);

        ei_draw_polygon(surface, &bar, bar_color, NULL);
        ei_draw_polygon(surface, &win, *toplevel->color, NULL);
        if (toplevel->resizable != ei_axis_none)
        {
                // Creating the clickable square on bottom-right (toplevel resizer)
                ei_rect_t resize_rect;
                resize_rect.top_left.x = toplevel->widget->screen_location.top_left.x + toplevel->widget->screen_location.size.width - 4 * *toplevel->border_width;
                resize_rect.top_left.y = toplevel->widget->screen_location.top_left.y + toplevel->widget->screen_location.size.height - 4 * *toplevel->border_width;
                resize_rect.size.width = 4 * *toplevel->border_width;
                resize_rect.size.height = 4 * *toplevel->border_width;
                ei_linked_point_t *resize_rectangle = cute_frame(&resize_rect,20,complete);
                ei_draw_polygon(surface, resize_rectangle, *toplevel->color, &rect);
        }
        int button_radius = 10;

        // Drawing the close button
        if (toplevel->closable == EI_TRUE)
        {


                ei_rect_t rect_button;
                rect_button.size = ei_size( 2*button_radius, 2*button_radius);
                rect_button.top_left = ei_point( rect->top_left.x + toplevel->border_width, rect->top_left.y + toplevel->border_width ) ;
                ei_linked_point_t *button_list = rounded_frame (rect, button_radius,complete);
                ei_draw_polygon(surface,button_list,red,clipper);
        }

        if (toplevel->title && strcmp(toplevel->title, "") != 0)
        {
                ei_point_t text_start = ei_point(rect->top_left.x + toplevel->border_width + 3*button_radius,rect->top_left.y + *toplevel->border_width + button_radius*0.2);
                ei_rect_t title_rect = ei_rect(text_start, text_size);
                ei_point_t where;
                compute_anchor_pos(ei_anc_none, &text_size, &title_rect, &where);
//                ei_draw_text(surface, &where, toplevel->title, ei_default_font, ei_font_default_color, &clipper);
        }

        if (pick_surface) {
                //ei_draw_polygon(pick_surface, exter_first_point, *(widget->pick_color), &intersection);
        }










};

void default_toplevel(struct ei_widget_t *widget)
{
        ei_toplevel_t *toplevel = (ei_toplevel_t *)widget;
        toplevel->widget = widget;
        toplevel->color = &ei_default_background_color;
        toplevel->border_width = 4;
        toplevel->title = "TopLevel";
        toplevel->closable = EI_TRUE;
        toplevel->resizable = ei_axis_both;
        toplevel->min_size = NULL;
        toplevel->closable = EI_TRUE;
}

void    geometry_toplevel (struct ei_widget_t* widget, ei_rect_t rect){

};

