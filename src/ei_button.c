#include "hw_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "ei_widget.h"

struct widget_class* alloc_button(){
        struct ei_widget_t *ptr = calloc(1, sizeof(struct ei_button_t));
        return ptr;
};

void	release_button	(struct ei_widget_t*	widget){
        ei_button_t* button = (ei_button_t*)widget;
        if (button->text)
                free(button->text);
        
        if (button->img_rect)
                free(button->img_rect);
};


void	draw_button	 (struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper){
        struct ei_button_t *button = (struct ei_button_t*) widget;

        ei_color_t *low_color = button->color;
        ei_color_t *high_color = button->color;
        high_color->alpha = min(255,button->color->alpha * 1.4);
        low_color->alpha = button->color->alpha * 0.3;


        ei_partie_button high = partie_haute;
        ei_partie_button low = partie_basse;
        ei_partie_button full = partie_complete;
        ei_rect_t content_rect = *(widget->parent->content_rect);
        ei_rect_t rectangle = ei_rect(content_rect.top_left,content_rect.size);

        ei_rect_t* sub_rect;
        sub_rect->top_left.x = rectangle.top_left.x + button->border_width;
        sub_rect->top_left.y = rectangle.top_left.y + button->border_width;
        sub_rect->size.width = rectangle.size.width - 2 * *(button->border_width);
        sub_rect->size.height = rectangle.size.height - 2 * *(button->border_width);

        int rayon = button->corner_radius;
        ei_linked_point_t *list_basse = rounded_frame(&rectangle, rayon, low);
        ei_linked_point_t *list_haute = rounded_frame(&rectangle,rayon,high);

        if (button->relief == ei_relief_raised){
                ei_draw_polygon(surface, list_basse,*low_color,NULL);
                ei_draw_polygon(surface, list_haute,*high_color,NULL);
        } else {
                ei_draw_polygon(surface, list_basse,*high_color,NULL);
                ei_draw_polygon(surface, list_haute,*low_color,NULL);
        }
        ei_linked_point_t *list_complete = rounded_frame(&sub_rect,rayon,full);
        ei_draw_polygon(surface, list_complete,*button->color,NULL);
};

void default_button(ei_widget_t *widget)
{
        ei_button_t *button = (ei_button_t *)widget;
        button->widget = widget;
        button->color = &ei_default_background_color;
        button->border_width = k_default_button_border_width;
        button->corner_radius = k_default_button_corner_radius;
        button->relief = ei_relief_raised;
        button->text = NULL;
        button->text_font = ei_default_font;
        button->text_color = &ei_font_default_color;
        button->text_anchor = ei_anc_center;
        button->img = NULL;
        button->img_rect = NULL;
        button->img_anchor = ei_anc_center;
        button->callback = NULL;
        button->user_param = NULL;
};

void    geometry_button (struct ei_widget_t* widget, ei_rect_t rect){

};