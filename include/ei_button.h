
#ifndef EI_BUTTON_H
#define EI_BUTTON_H
#include "ei_widget.h"
/**
 * \brief	 The structure of a button.
 */
typedef struct ei_button_t {
    ei_widget_t         *widget;
    ei_size_t*          requested_size;
    const ei_color_t    *color;
    int                 *border_width;
    int                 *corner_radius;
    ei_relief_t*        relief;
    char                **text;
    ei_font_t*          text_font;
    ei_color_t          *text_color;
    ei_anchor_t*        text_anchor;
    ei_surface_t        *img;
    ei_rect_t**         img_rect;
    ei_anchor_t         *img_anchor;
    ei_callback_t*      callback;
    void                **user_param;
}ei_button_t;

struct widget_class* alloc_button();

void	release_button		(struct ei_widget_t*	widget);

void	draw_button	 (struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);

void	default_button(struct ei_widget_t*	widget);

void    geometry_button (struct ei_widget_t* widget, ei_rect_t rect);




#endif
