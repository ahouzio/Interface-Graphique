#include "hw_interface.h"
#include "ei_types.h"
#include "ei_event.h"
#include "ei_utils.h"
#include "ei_draw.h"
#include "ei_draw_funct.h"


int main(){
        ei_surface_t main_window = NULL;
        ei_size_t main_window_size = ei_size(700, 700);
        ei_event_t event;
        ei_color_t green = {0x00, 0xff, 0x00, 0xff};
        ei_size_t clip_size = ei_size(320, 240);
        ei_color_t red = {0xff, 0x00, 0x00, 0xff};
        ei_color_t brown = {0xA5, 0x2A, 0x2A, 0xff};
        ei_color_t orange = {0xFF, 0xA5, 0x00, 0xff};
        //ei_color_t white = {0xff, 0xff, 0xff, 0xff};

        hw_init();
        main_window = hw_create_window(main_window_size, EI_FALSE);
        hw_surface_lock(main_window);

        int rayon_1 = 50;
        
        ei_point_t centre_1 = ei_point(350,350);
        ei_rect_t clipper = ei_rect(centre_1, clip_size);
        ei_rect_t rectangle = ei_rect(ei_point(100,100),ei_size(200,100));
        ei_partie_button high = partie_haute;
        ei_partie_button low = partie_basse;
        ei_partie_button full = partie_complete;
        ei_linked_point_t *list_basse = rounded_frame(&rectangle,rayon_1,low);
        ei_draw_polygon(main_window, list_basse,red,NULL);
        ei_linked_point_t *list_haute = rounded_frame(&rectangle,rayon_1,high);
        ei_draw_polygon(main_window, list_haute,orange,NULL);
        ei_rect_t rectangle_2 = ei_rect(ei_point(110,110),ei_size(180,80));
        ei_linked_point_t *list_complete = rounded_frame(&rectangle_2,rayon_1,full);
        ei_draw_polygon(main_window, list_complete,brown,NULL);


        hw_surface_unlock(main_window);
        hw_surface_update_rects(main_window, NULL);
        event.type = ei_ev_none;
        while (event.type != ei_ev_keydown)
                hw_event_wait_next(&event);
        hw_quit();
}
