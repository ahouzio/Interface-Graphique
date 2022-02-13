
#ifndef EI_FRAME_H
#define EI_FRAME_H

/**
 * \brief	The structure of a frame.
 */

typedef struct ei_frame_t{
    ei_widget_t*	widget;
    ei_size_t*		requested_size;
    const ei_color_t*	color;
    int*		border_width;
    ei_relief_t*	relief;
    char**		text;
    ei_font_t*		text_font;
    ei_color_t*		text_color;
    ei_anchor_t*	text_anchor;
    ei_surface_t*	img;
    ei_rect_t**		img_rect;
    ei_anchor_t*	img_anchor;
}ei_frame_t;


struct widget_class* alloc_frame();

void	release_frame		(struct ei_widget_t*	widget);

void	draw_frame	 (struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);

void	default_frame(struct ei_widget_t*	widget);

void    geometry_frame (struct ei_widget_t* widget, ei_rect_t rect);


#endif //PROJETC_IG_EI_FRAME_H
