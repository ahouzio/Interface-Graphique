
#ifndef EI_TOPLEVEL_H
#define EI_TOPLEVEL_H

/**
 * \brief	 The structure of a top_level.
 */
typedef struct ei_toplevel_t{
    ei_widget_t*	widget;
    ei_size_t*		requested_size;
    ei_color_t*		color;
    int*		border_width;
    char**		title;
    ei_bool_t*		closable;
    ei_axis_set_t*	resizable;
    ei_size_t**		min_size;
}ei_toplevel_t;

struct widget_class* alloc_toplevel();

void	release_toplevel	(struct ei_widget_t*	widget);

void	draw_toplevel (struct ei_widget_t* widget, ei_surface_t surface, ei_surface_t pick_surface, ei_rect_t* clipper);

void	default_toplevel(struct ei_widget_t*	widget);

void    geometry_toplevel (struct ei_widget_t* widget, ei_rect_t rect);


#endif //PROJETC_IG_EI_TOPLEVEL_H
