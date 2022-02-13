#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "hw_interface.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "ei_types.h"
#include "ei_event.h"


/* test_copy_surface --
 *
 *	Copies surface passed in parameters. This is meant to test the function that copies a surface.
 */
void test_copy_surface(ei_surface_t surface, ei_rect_t* clipper)
{

        ei_surface_t surface_copy;
        ei_copy_surface(surface_copy, NULL, surface, clipper, EI_FALSE);
        /* Unlock and update the surface. */
        hw_surface_unlock(surface_copy);
        hw_surface_update_rects(surface_copy, NULL);

        /* Wait for a character on command line. */
        event.type = ei_ev_none;
        while (event.type != ei_ev_keydown)
                hw_event_wait_next(&event);

        hw_surface_free(surface_copy);
}



/* test_text --
 *
 *	Draws a text in the middle of the scree. This is meant to test the
 *	algorithm that draws a text.
 */
void test_text(ei_surface_t surface, ei_rect_t* clipper)
{
        ei_color_t		color		= { 0, 255, 0, 255 };
        ei_point_t start = {200, 200};
        const char* text = "MOI"
        ei_draw_text(surface, &start, text, NULL, color, NULL);
}


/*
 * ei_main --
 *
 *	Main function of the application.
 */
int main(int argc, char** argv)
{
        ei_size_t		win_size	= ei_size(800, 600);
        ei_surface_t		main_window	= NULL;
        ei_color_t		white		= { 0xff, 0xff, 0xff, 0xff };
        ei_color_t      black       = {0x00, 0x00, 0x00, 0xff};
        ei_rect_t*		clipper_ptr	= NULL;
        ei_event_t		event;
        ei_color_t		green		= { 0, 255, 0, 255 };
        hw_init();

        main_window = hw_create_window(win_size, EI_FALSE);

        /* Lock the drawing surface, paint it white. */
        hw_surface_lock	(main_window);
        ei_fill		(main_window, &white, NULL);

        ei_rect_t		clipper		= ei_rect(ei_point(200, 150), ei_size(200, 300));
        clipper_ptr		= &clipper;

        test_copy_surface(surface, clipper_ptr);

        test_polygon(main_window, black, NULL);
        /* Draw polylines. */

        test_line	(main_window, clipper_ptr);
        test_octogone	(main_window, clipper_ptr);
        test_square	(main_window, clipper_ptr);
        test_dot	(main_window, clipper_ptr);

        /* Unlock and update the surface. */
        hw_surface_unlock(main_window);
        hw_surface_update_rects(main_window, NULL);

        /* Wait for a character on command line. */
        event.type = ei_ev_none;
        while (event.type != ei_ev_keydown)
                hw_event_wait_next(&event);

        hw_quit();
        return (EXIT_SUCCESS);
}
