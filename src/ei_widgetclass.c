

#include "hw_interface.h"
#include "ei_widgetclass.h"
#include "ei_frame.h"
#include "ei_button.h"
#include "ei_toplevel.h"


/* list of widgets */
struct ei_widgetclass_t *widget_list = NULL;

void			ei_widgetclass_register		(ei_widgetclass_t* widget){
        /* We search first if it's already registered */
        struct ei_widgetclass_t *widgetclass = widget_list;
        while (widgetclass != NULL){
                if (widgetclass = widget)
                        return ;
                widgetclass = widgetclass->next;
        }
        /* It's not registered, we create it then */
        if (strcmp(widget->name, "frame") == 0){
                widget->geomnotifyfunc = (ei_widgetclass_geomnotifyfunc_t) &geometry_frame;
                widget->setdefaultsfunc = (ei_widgetclass_setdefaultsfunc_t) &default_frame;
                widget->drawfunc = (ei_widgetclass_drawfunc_t) &draw_frame;
                widget->allocfunc = (ei_widgetclass_allocfunc_t) &alloc_frame;
                widget->releasefunc = (ei_widgetclass_releasefunc_t) &release_frame;
                widget->next = widget_list;
                widget_list = widget;}
        else if (strcmp(widget->name, "toplevel") == 0){
                widget->geomnotifyfunc = (ei_widgetclass_geomnotifyfunc_t) &geometry_toplevel;
                widget->setdefaultsfunc = (ei_widgetclass_setdefaultsfunc_t) &default_toplevel;
                widget->drawfunc = (ei_widgetclass_drawfunc_t) &draw_toplevel;
                widget->allocfunc = (ei_widgetclass_allocfunc_t) &alloc_toplevel;
                widget->releasefunc = (ei_widgetclass_releasefunc_t) &release_toplevel;
                widget->next = widget_list;
                widget_list = widget;}
        else if (strcmp(widget->name, "button") == 0){
                widget->geomnotifyfunc = (ei_widgetclass_geomnotifyfunc_t) &geometry_button;
                widget->setdefaultsfunc = (ei_widgetclass_setdefaultsfunc_t) &default_button;
                widget->drawfunc = (ei_widgetclass_drawfunc_t) &draw_button;
                widget->allocfunc = (ei_widgetclass_allocfunc_t) &alloc_button;
                widget->releasefunc = (ei_widgetclass_releasefunc_t) &release_button;
                widget->next = widget_list;
                widget_list = widget;}
        else
                widget->next = widget_list;
                widget_list = widget;
}
/* Une nouvelle classe de widget est enregistré d'abord puis on appelle la fonction ei_widget_from_name */
ei_widgetclass_t*	ei_widgetclass_from_name	(ei_widgetclass_name_t name){
        struct ei_widgetclass_t *widgetclass = widget_list;
        while (widgetclass != NULL){
                if (strcmp(widgetclass->name, name) == 0)
                        return widgetclass;
                widgetclass = widgetclass->next;
        }

        return NULL;
}