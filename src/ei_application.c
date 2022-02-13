
#include <stdio.h>
#include "hw_interface.h"
#include "ei_types.h"
#include "ei_widget.h"
#include "ei_frame.h"
#include "ei_widgetclass.h"
/**
 * \brief	Creates an application.
 *		<ul>
 *			<li> initializes the hardware (calls \ref hw_init), </li>
 *			<li> registers all classes of widget, </li>
 *			<li> creates the root window (either in a system window, or the entire screen), </li>
 *			<li> creates the root widget to access the root window. </li>
 *		</ul>
 *
 * @param	main_window_size	If "fullscreen is false, the size of the root window of the
 *					application.
 *					If "fullscreen" is true, the current monitor resolution is
 *					used as the size of the root window. \ref hw_surface_get_size
 *					can be used with \ref ei_app_root_surface to get the size.
 * @param	fullScreen		If true, the root window is the entire screen. Otherwise, it
 *					is a system window.
 */

ei_surface_t root_window;
ei_widget_t *root_widget;
void ei_app_create(ei_size_t main_window_size, ei_bool_t fullscreen){
        hw_init();
        //initializing the known classes
        ei_widgetclass_t *frame_widget = calloc(1, sizeof(ei_widgetclass_t));
        ei_widgetclass_t *button_widget = calloc(1, sizeof(ei_widgetclass_t));
        ei_widgetclass_t *toplevel_widget = calloc(1, sizeof(ei_widgetclass_t));
        ei_widgetclass_register(frame_widget);
        ei_widgetclass_register(button_widget);
        ei_widgetclass_register(toplevel_widget);
        
        root_window = hw_create_window(main_window_size, fullscreen);
        root_widget = ei_widget_create("frame",NULL,NULL,NULL);
        root_widget->requested_size = main_window_size;
        root_widget->screen_location.size.width = main_window_size.width;
        root_widget->screen_location.size.height = main_window_size.height;
};
/**
 * \brief	Releases all the resources of the application, and releases the hardware
 *		(ie. calls \ref hw_quit).
 */

void ei_app_free(void){
        hw_quit();
}

/**
 * \brief	Runs the application: enters the main event loop. Exits when
 *		\ref ei_app_quit_request is called.
 */

void ei_app_run(void){
        getchar();
}

/**
 * \brief	Adds a rectangle to the list of rectangles that must be updated on screen. The real
 *		update on the screen will be done at the right moment in the main loop.
 *
 * @param	rect		The rectangle to add, expressed in the root window coordinates.
 *				A copy is made, so it is safe to release the rectangle on return.
 */

void ei_app_invalidate_rect(ei_rect_t* rect){

}

/**
 * \brief	Tells the application to quite. Is usually called by an event handler (for example
 *		when pressing the "Escape" key).
 */

void ei_app_quit_request(void){

}

/**
 * \brief	Returns the "root widget" of the application: a "frame" widget that span the entire
 *		root window.
 *
 * @return 			The root widget.
 */

ei_widget_t* ei_app_root_widget(void){
        return root_widget;
}

/**
 * \brief	Returns the surface of the root window. Can be usesd to create surfaces with similar
 * 		r, g, b channels.
 *
 * @return 			The surface of the root window.
 */
ei_surface_t ei_app_root_surface(void){
        return root_window;
}

