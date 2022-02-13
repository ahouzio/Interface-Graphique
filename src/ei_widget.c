
#include "ei_draw.h"
#include "ei_widgetclass.h"
#include "ei_fonction_auxiliaire.h"
#include "ei_types.h"
#include "ei_application.h"
#include "hw_interface.h"
#include "ei_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_toplevel.h"


static ei_color_t widget_colour = {0,255,255,0};

/**
 * @brief 		gets a new color fot the widget.
 *
 * @return ei_color_t* 		color.
 */
static ei_color_t *color()
{
        if (widget_colour.blue < 255)
        {
                widget_colour.blue++;
        }
        else
        {
                widget_colour.blue = 0;
                if (widget_colour.green < 255)
                {
                        widget_colour.green++;
                }
                else
                {
                        widget_colour.blue = 0;
                        if (widget_colour.red < 255)
                        {
                                widget_colour.red++;
                        }
                        else
                        {
                                printf("wut?");
                        }
                }
        }
        ei_color_t *color = calloc(1, sizeof(ei_color_t));
        color->red = widget_colour.red;
        color->green = widget_colour.green;
        color->blue = widget_colour.blue;
        color->alpha = widget_colour.alpha;
        return color;
}

ei_widget_t*		ei_widget_create		(ei_widgetclass_name_t	class_name,
                                                             ei_widget_t*		parent,
                                                             void*			user_data,
                                                             ei_widget_destructor_t destructor){
        /* We verify if the widget name is valid */

        ei_widgetclass_t *widgetclass = ei_widgetclass_from_name(class_name);

        if (widgetclass) {
                ei_widget_t *widget = widgetclass->allocfunc();
                widget->wclass = widgetclass;
                /* Picking the colour for the widget */

                widget->pick_color = color();
                widget->pick_id = ei_map_rgba(ei_app_root_surface(), *(widget->pick_color));
                widget->parent = parent;
                /* put the widget in the end of the parent children list and define it's children*/
                if (parent != NULL) {
                        if (parent->children_head == NULL) {
                                parent->children_head = widget;
                                parent->children_tail = widget;
                        }
                        else {
                                parent->children_tail->next_sibling = widget;
                                parent->children_tail = widget;
                        }
                        widget->screen_location.top_left = ei_point(0,0);
                        widget->screen_location.size = ei_size(0,0);
                }
                else
                {
                        widget->screen_location.top_left.x = 0;
                        widget->screen_location.top_left.y = 0;
                }
                widget->next_sibling = NULL;
                widget->children_head = NULL;
                widget->children_tail = NULL;
                /* Defining the geometry management parameters */
                widget->placer_params = NULL;
                widget->screen_location.size.width = 0;
                widget->screen_location.size.height = 0;
                widget->requested_size.width = 0;
                widget->requested_size.height = 0;
                widget->content_rect = malloc(sizeof(ei_rect_t));
                widget->content_rect->top_left.x = widget->screen_location.top_left.x;
                widget->content_rect->top_left.y = widget->screen_location.top_left.y;
                widget->content_rect->size.width = 0;
                widget->content_rect->size.height = 0;
                widgetclass->setdefaultsfunc(widget);
                return widget;
        }
        return NULL;
}



void			ei_widget_destroy		(ei_widget_t*		widget){


}



ei_widget_t*		ei_widget_pick			(ei_point_t*		where){



}

void			ei_frame_configure		(ei_widget_t*		widget,
                                                               ei_size_t*		requested_size,
                                                               const ei_color_t*	color,
                                                               int*			border_width,
                                                               ei_relief_t*		relief,
                                                               char**			text,
                                                               ei_font_t*		text_font,
                                                               ei_color_t*		text_color,
                                                               ei_anchor_t*		text_anchor,
                                                               ei_surface_t*		img,
                                                               ei_rect_t**		img_rect,
                                                               ei_anchor_t*		img_anchor){

        /* Defining a frame attributes of the widget */
        ei_frame_t *frame = (ei_frame_t*) widget;

        /* Prototype to define the default values */
        if (img_anchor != NULL)
                frame->img_anchor = img_anchor; /* updating the new value */
        else if (frame->img_anchor == NULL)
                frame->img_anchor = ei_anc_center; /*Defining the attribute if it wasn't defined before */

        if (img_rect != NULL)
                frame->img_rect = img_rect;
        else if (frame->img_rect == NULL)
                frame->img_rect = NULL;

        if (img != NULL)
                frame->img = img;
        else if (frame->img == NULL)
                frame->text = text;

        if (text_font != NULL)
                frame->text_font = text_font;
        else if (frame->text_font == NULL)
                frame->text_font = ei_default_font;

        if (text_anchor != NULL)
                frame->text_anchor = text_anchor;
        else if (frame->text_anchor == NULL)
                frame->text_anchor = ei_anc_center;

        if (text_color != NULL)
                frame->text_color = text_color;
        else if (frame->text_color == NULL)
                frame->text_color = &ei_font_default_color;

        if (relief != NULL)
                frame->relief = relief;
        else if (frame->relief == NULL)
                frame->text = ei_relief_none;

        if (border_width != NULL)
                frame->border_width = border_width;
        else if (frame->border_width == NULL)
                frame->border_width = 0;

        if (color != NULL)
                frame->color = color;
        else if (frame->color == NULL)
                frame->color = &ei_default_background_color;

        if (img != NULL)
                frame->img = img;
        else if (frame->img == NULL)
                frame->text = text;

        if (requested_size != NULL){
                frame->requested_size = requested_size;}

        else
        {
                widget->requested_size = widget->content_rect->size;}

        widget->requested_size.height = max(widget->requested_size.height, frame->requested_size->height);
        widget->requested_size.width = max(widget->requested_size.height, frame->requested_size->width);

}

void			ei_button_configure		(ei_widget_t*		widget,
                                                                ei_size_t*		requested_size,
                                                                const ei_color_t*	color,
                                                                int*			border_width,
                                                                int*			corner_radius,
                                                                ei_relief_t*		relief,
                                                                char**			text,
                                                                ei_font_t*		text_font,
                                                                ei_color_t*		text_color,
                                                                ei_anchor_t*		text_anchor,
                                                                ei_surface_t*		img,
                                                                ei_rect_t**		img_rect,
                                                                ei_anchor_t*		img_anchor,
                                                                ei_callback_t*		callback,
                                                                void**			user_param){

        /* Defining a button attributes of the widget */
        ei_button_t *button = (ei_button_t*) widget;

        /* Prototype to define the default values */
        if (img_anchor != NULL)
                button->img_anchor = img_anchor; /* updating the new value */
        else if (button->img_anchor == NULL)
                button->img_anchor = ei_anc_center; /*Defining the attribute if it wasn't defined before */

        if (img_rect != NULL)
                button->img_rect = img_rect;
        else if (button->img_rect == NULL)
                button->img_rect = NULL;

        if (img != NULL)
                button->img = img;
        else if (button->img == NULL)
                button->text = text;

        if (text_font != NULL)
                button->text_font = text_font;
        else if (button->text_font == NULL)
                button->text_font = ei_default_font;

        if (text_anchor != NULL)
                button->text_anchor = text_anchor;
        else if (button->text_anchor == NULL)
                button->text_anchor = ei_anc_center;

        if (text_color != NULL)
                button->text_color = text_color;
        else if (button->text_color == NULL)
                button->text_color = &ei_font_default_color;

        if (relief != NULL)
                button->relief = relief;
        else if (button->relief == NULL)
                button->text = ei_relief_raised;

        if (border_width != NULL)
                button->border_width = border_width;
        else if (button->border_width == NULL)
                button->border_width = k_default_button_border_width;

        if (color != NULL)
                button->color = color;
        else if (button->color == NULL)
                button->color = &ei_default_background_color;

        if (img != NULL)
                button->img = img;
        else if (button->img == NULL)
                button->text = text;

        if (requested_size != NULL)
                button->requested_size = requested_size;
        else if (button->requested_size == NULL)
                button->requested_size = &widget->requested_size;

        widget->requested_size.height = max(widget->requested_size.height, button->requested_size->height);
        widget->requested_size.width = max(widget->requested_size.height, button->requested_size->width);

        if (corner_radius != NULL)
                button->corner_radius = corner_radius;
        else if (button->corner_radius == NULL)
                button->corner_radius = k_default_button_corner_radius;

        /* PROBLEM : adding user_param to callback parameters */
        if (callback != NULL)
                button->callback = callback;
                if (user_param != NULL)
                        button->user_param = user_param;
        else if (button->callback == NULL)
                button->callback = NULL;

        if (img != NULL)
                button->img = img;
        else if (button->img == NULL)
                button->text = text;

}

void			ei_toplevel_configure		(ei_widget_t*		widget,
                                                                  ei_size_t*		requested_size,
                                                                  ei_color_t*		color,
                                                                  int*			border_width,
                                                                  char**			title,
                                                                  ei_bool_t*		closable,
                                                                  ei_axis_set_t*		resizable,
                                                                  ei_size_t**		min_size) {
        /* Defining a button attributes of the widget */
        ei_toplevel_t *toplevel = (ei_toplevel_t*) widget;
        ei_size_t default_size = {320,240};
        ei_size_t default_min_size = {160,120};
        if (color != NULL)
                toplevel->color = color;
        else if (toplevel->color == NULL)
                toplevel->color = &ei_default_background_color;

        if (border_width != NULL)
                toplevel->border_width = border_width;
        else if (toplevel->border_width == NULL)
                toplevel->border_width = 4;

        if (title != NULL)
                toplevel->title = title;
        else if (toplevel->title == NULL)
                toplevel->title = "TopLevel";

        if (closable != NULL)
                toplevel->closable = closable;
        else if (toplevel->closable == NULL)
                toplevel->closable = EI_TRUE;

        if (resizable != NULL)
                toplevel->resizable = resizable;
        else if (toplevel->resizable == NULL)
                toplevel->resizable = ei_axis_both;

        if (min_size != NULL)
                toplevel->min_size = min_size;
        else if (*toplevel->min_size == NULL)
                toplevel->resizable = &default_min_size; /* Not sure */

        if (requested_size != NULL)
                toplevel->requested_size = requested_size;
        else if (toplevel->requested_size == NULL)
                toplevel->requested_size = &default_size;

        widget->requested_size.height = max(widget->requested_size.height, toplevel->requested_size->height);
        widget->requested_size.width = max(widget->requested_size.height, toplevel->requested_size->width);

}