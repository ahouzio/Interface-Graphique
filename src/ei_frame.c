#include "ei_types.h"
#include "ei_application.h"
#include "hw_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ei_frame.h"
#include "ei_draw.h"
#include "ei_draw_funct.h"


struct widget_class* alloc_frame(){
        return calloc(1, sizeof(struct ei_frame_t));
};


void	release_frame	(struct ei_widget_t*	widget){
        ei_frame_t *frame = (ei_frame_t *)widget;
        if (frame->text)
                free(frame->text);
        if (frame->img_rect)
                free(frame->img_rect);
};

void	draw_frame	 (struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper){

        ei_frame_t *frame = (ei_frame_t *)widget;
        ei_rect_t location = frame->widget->screen_location;
        //ei_section_rectangle(clipper, &(frame->widget.screen_location), &);
        frame->widget->screen_location.size.width = location.size.width;
        frame->widget->screen_location.size.height = location.size.height;
        frame->widget->screen_location.top_left.x = location.top_left.x;
        frame->widget->screen_location.top_left.y = location.top_left.y;
        frame->widget->content_rect->top_left.x = location.top_left.x;
        frame->widget->content_rect->top_left.y = location.top_left.y;
        frame->widget->content_rect->size.width = location.size.width;
        frame->widget->content_rect->size.height = location.size.height;

        if (frame->border_width > 0)
        {


                ei_color_t *low_color = frame->color;
                ei_color_t *high_color = frame->color;
                high_color->alpha = min(255,frame->color->alpha * 1.4);
                low_color->alpha = frame->color->alpha * 0.3;
                int rayon = frame->border_width;
                ei_partie_button low = partie_basse;
                ei_partie_button high = partie_haute;
                ei_partie_button complete = partie_complete;
                ei_linked_point_t high_link = *cute_frame(&location,rayon,low);
                ei_linked_point_t low_link = *cute_frame(&location,rayon,high);

                ei_rect_t* sub_rect;
                sub_rect->top_left.x = location.top_left.x + frame->border_width;
                sub_rect->top_left.y = location.top_left.y + frame->border_width;
                sub_rect->size.width = location.size.width - 2 * *(frame->border_width);
                sub_rect->size.height = location.size.height - 2 * *(frame->border_width);

                ei_linked_point_t complete_link = *cute_frame(sub_rect,rayon,complete);

                if (frame->relief == ei_relief_none)
                {
                        ei_fill(surface, &frame->color,&location);
                }
                else if (frame->relief == ei_relief_raised)
                {

                        ei_draw_polygon(surface, &low_link,*low_color,NULL);
                        ei_draw_polygon(surface, &high_link,*high_color,NULL);
                        ei_draw_polygon(surface, &complete_link,*frame->color,NULL);
                        ei_fill(surface, &frame->color,&location);
                }
                else if (frame->relief == ei_relief_sunken)
                {
                        ei_draw_polygon(surface, &low_link,*high_color,NULL);
                        ei_draw_polygon(surface, &high_link,*low_color,NULL);
                        ei_draw_polygon(surface, &complete_link,*frame->color,NULL);
                        ei_fill(surface, &frame->color,&location);
                }
        }
        else
        {
                ei_fill(surface, &frame->color,&location);
        }

        if (pick_surface)
        {
                ei_point_t top_left_high = location.top_left;
                ei_point_t top_right_high = {top_left_high.x + location.size.width, top_left_high.y};
                ei_point_t down_right_high = {top_left_high.x +  location.size.width, top_left_high.y + location.size.height};
                ei_point_t down_left_high = {top_left_high.x, top_left_high.y + location.size.height};

                ei_linked_point_t top_exter = {top_left_high, NULL};
                ei_linked_point_t right_exter = {top_right_high, &top_exter};
                ei_linked_point_t bot_exter = {down_right_high, &right_exter};
                ei_linked_point_t left_exter = {down_left_high, &bot_exter};
                ei_draw_polygon(pick_surface, &left_exter, *(frame->widget->pick_color), &location);
        }

        if (frame->text != 0 && strcmp(frame->text, "") != 0)
        {
                ei_point_t where;
                ei_size_t text_size;
                hw_text_compute_size(frame->text, frame->text_font, &(text_size.width), &(text_size.height));
                compute_anchor_pos(*frame->text_anchor, &text_size, &location, &where);
                //ei_draw_text(surface, &where, frame->text, NULL, *frame->text_color, &location);
        }
        else
        {
                if (frame->img)
                {
                        ei_point_t image_position;
                        ei_size_t image_size;
                        ei_rect_t image_surface;
                        if (frame->img_rect)
                        {
                                image_surface= hw_surface_get_rect(frame->img_rect);
                                image_size = image_surface.size;
                        }
                        else
                        {
                                image_surface = hw_surface_get_rect(frame->img);
                                image_size = image_surface.size;
                        }
                        //ei_anchor_spot(frame->img_anchor, &size_img, &, &pos_img);
                        ei_rect_t rect_img = {image_position, image_size};

                        hw_surface_lock(frame->img);
                        ei_bool_t alpha_img = hw_surface_has_alpha(frame->img);
                        ei_rect_t surface_rect = hw_surface_get_rect(ei_app_root_surface());

                        ei_rect_t clipper_img;
                        //ei_intersection_rectangle(&, &surface_rect, &clipper_img);

                        ei_rect_t dest_final;
                        //ei_intersection_rectangle(&clipper_img, &rect_img, &dest_final);

                        rect_img.top_left.x = image_surface.top_left.x + dest_final.top_left.x - image_position.x;
                        rect_img.top_left.y = image_surface.top_left.y;
                        rect_img.size = dest_final.size;
//                      ei_copy_surface(surface, &dest_final, frame->img, &rect_img, alpha_img);
                        hw_surface_unlock(frame->img);
                }
        }
}



void default_frame(ei_widget_t *widget)
{
        ei_frame_t *frame = (ei_frame_t *)widget;
        frame->widget = widget;
        frame->color = &ei_default_background_color;
        frame->requested_size->width = 0;
        frame->requested_size->height = 0;
        frame->border_width = 0;
        frame->relief = ei_relief_none;
        frame->text = NULL;
        frame->text_font = ei_default_font;
        frame->text_color = &ei_font_default_color;
        frame->text_anchor = ei_anc_center;
        frame->img = NULL;
        frame->img_rect = NULL;
        frame->img_anchor = ei_anc_center;
};

void    geometry_frame (struct ei_widget_t* widget, ei_rect_t rect){

};