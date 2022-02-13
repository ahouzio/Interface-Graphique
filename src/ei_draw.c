#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "ei_types.h"
#include "ei_utils.h"
#include "hw_interface.h"
#include "ei_fonction_auxiliaire.h"
#include "ei_draw_funct.h"



uint32_t		ei_map_rgba		(ei_surface_t surface, ei_color_t color) {

        /*convert unsigned char of color pigments to unit32_t*/
        uint32_t r = (uint32_t) color.red;
        uint32_t g = (uint32_t) color.green;
        uint32_t b = (uint32_t) color.blue;
        uint32_t a;

        /* init of channels positions*/
        int ir, ig, ib, ia;
        hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

        /* determining needed variables to add alpha channel based on wether the surface accepts alpha channel or not*/
        if (hw_surface_has_alpha(surface) == EI_TRUE) {
                a = (uint32_t) color.alpha;
        }
        else {
                ia = 6 - ir - ib -ig;
                a = 255;
        }

        /* init of the 32 bit integer corresponding to the color*/
        uint32_t res;
        res = (r << (ir << 3 )) + (g << (ig << 3)) +  (b << (ib << 3)) + (a << (ia << 3 ));

        return res;
}


/**
* \brief	Converts the uint32_t pixel indicating a color to an ei_color_t object
*
*
* @param	surface		The surface where this pixel is stored, provides the channels order.
* @param       pixel            The color in the pixel we want to convert.
*
* @return 			The ei_color_t corresponding to the color represented with pixel.
*/

ei_color_t              ei_map_pixel    (ei_surface_t surface, uint32_t pixel){
        ei_color_t color;
        /* init of channels positions*/
        int ir, ig, ib, ia;
        hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);

        /* unpacking the pixel */
        color.red = (pixel >> (ir << 3)) & 0xff;
        color.green = (pixel >> (ig << 3)) & 0xff;
        color.blue = (pixel >> (ib << 3)) & 0xff;
        color.alpha = (pixel >> (ia << 3)) & 0xff;

        return color;
}

/**
 * \brief	Converts the red, green, blue and alpha components of a color into a uint32_t integer
 *              that takes into consideration the transparency parameter.
 *
 *
 *
 * @param	surface		The surface where to store this pixel, provides the channels order.
 * @param	color		The pointer towards the color we want to change to take into consideration.
 * @param       pixel           The color in the pixel we want to draw over.
 *
 * @return 			The 32 bit integer corresponding to the superposition of both the color in the arguments and the color previously set in pixel.
 */


uint32_t               ei_map_transparency      (ei_surface_t surface, ei_color_t pixel_to_show, uint32_t surface_pixel){

        ei_color_t surface_color = ei_map_pixel(surface, surface_pixel);
        ei_color_t color_to_show;

        color_to_show.alpha = surface_color.alpha;
        color_to_show.red = (pixel_to_show.alpha * pixel_to_show.red + (255 - pixel_to_show.alpha)*surface_color.red)/255;
        color_to_show.green= (pixel_to_show.alpha * pixel_to_show.green + (255 - pixel_to_show.alpha)*surface_color.green)/255;
        color_to_show.blue= (pixel_to_show.alpha * pixel_to_show.blue + (255 - pixel_to_show.alpha)*surface_color.blue)/255;

        return ei_map_rgba(surface, color_to_show);
}



/**
* \brief	draws a line segment.
*
* @param	pixel_ptr    	pointer to the the origin point of our surface.
* @param	point1		first point.
 * @param	point2		second point.
 * @param	color		color of the line segment.
 * @param	*clipper	If not NULL, the drawing is restricted within this rectangle.
 * @param	surface		The surface where to store this segment, provides the channels order.
*/
void ei_line(uint32_t *pixel_ptr,
             ei_point_t point1,
             ei_point_t point2,
             ei_color_t color,
             const ei_rect_t *clipper,
             ei_surface_t surface ) {

        // bresenham line
        int x1 = point1.x, y1 = point1.y, x2 = point2.x, y2 = point2.y, cond = abs(y2 - y1) > abs(x2 - x1), sign_y = -1;

        if (cond) {
                permuter(&x1, &y1);
                permuter(&x2, &y2);
        }

        if (x1 > x2) {
                permuter(&x1,&x2);
                permuter(&y1,&y2);
        }

        if (y1 < y2) {
                sign_y = 1;
        }
        int largeur = hw_surface_get_size(surface).width;

        int dx = abs(x2 - x1), dy = abs(y2 - y1), y = y1, x = x1, e = 0;

        for (x; x <= x2; x++) {
                if (cond) {
                        uint32_t *p = pixel_ptr + largeur * x + y;
                        if (clipping(clipper, y, x)) {
                                uint32_t color_to_draw = ei_map_rgba(surface, color);

                                if (hw_surface_has_alpha(surface)){
                                        ei_map_transparency(surface, color, *p);
                                }
                                *p= color_to_draw;
                        }



                } else {
                        uint32_t *p = pixel_ptr + largeur * y + x;
                        if (clipping(clipper, x, y)) {
                                *p= ei_map_rgba(surface, color);
                        }


                }

                if ((e + dy) << 1 < dx) {
                        e = e + dy;
                } else {
                        y += sign_y;
                        e = e + dy - dx;
                }
        }
}



void ei_draw_polyline(ei_surface_t surface,
                      const ei_linked_point_t *first_point,
                      ei_color_t color,
                      const ei_rect_t *clipper)  {
        ei_size_t main_window_size = ei_size(640, 480);
        uint32_t *pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);
        ei_linked_point_t *current_point = (ei_linked_point_t*) first_point;
        ei_linked_point_t *next_point = current_point->next;
        ei_linked_point_t* condition = current_point;
        if (next_point->next == first_point){
                condition = next_point;
        }
        do{
                ei_line(pixel_ptr, current_point->point,next_point->point,color, clipper,surface);
                current_point = next_point;
                next_point = next_point->next;
                condition = condition-> next;
        }while (condition != first_point);
}





void			ei_fill			(ei_surface_t		surface,
                                                            const ei_color_t*	color,
                                                            const ei_rect_t*	clipper){
        int largeur = hw_surface_get_size(surface).width;
        int hauteur = hw_surface_get_size(surface).height;

        /* Lock the drawing surface, paint it with color. */

        /*ei_fill		(main_window, &white, clipper_ptr);*/
        uint32_t *pixel_ptr = (uint32_t *) hw_surface_get_buffer(surface);
        uint32_t color_hex = ei_map_rgba(surface, *color);

        for (int i = 0; i < (largeur*hauteur); i++){
                if (clipping(clipper, i%largeur,i/largeur)){
                        *pixel_ptr = color_hex;
                };
                pixel_ptr++;
        }


}




ei_bool_t not_empty(ei_side_t** TC_table, int y, int len){
        for (int index = y; index <= len; index++){
                if (*(TC_table + index) != NULL){
                        return EI_TRUE;
                }
        }
        return EI_FALSE;


}
/* functions used to sort the simply linked list with nodes according to their xymin attribute
 * these functions are wirtten to be used on TCA_table but can be used on any linked list if the attribute of the its nodes
 * we want to sort the list according to is named xymin*/

/* get_end is a function that gets the last side pointed with the list starting with the side "start" before it reaches the side "stop" */

ei_side_t* get_end(ei_side_t* start, ei_side_t* stop){
        ei_side_t* current_side = start;
        while(current_side != NULL && current_side -> side_ptr != stop){
                current_side = current_side -> side_ptr;
        }
        return current_side;
}

/* function partition returns the node (here a side) "pivot" of the linked list after switching nodes (here sides)
so that they are in the right side of pivot according to the attribute xymin */
ei_side_t* partition(ei_side_t* start, ei_side_t* end, ei_side_t** new_start, ei_side_t** new_end){
        ei_side_t* pivot = end;
        ei_side_t* previous_side = NULL;
        ei_side_t* current_side = start;
        ei_side_t* stop = pivot;
        while(current_side != pivot) {
                if (current_side->xymin < pivot->xymin) {
                        if ((*new_start) == NULL) {
                                (*new_start) = current_side;
                        }
                        previous_side = current_side;
                        current_side = current_side->side_ptr;
                } else {
                        if (previous_side != NULL) {
                                previous_side->side_ptr = current_side->side_ptr;
                        }
                        ei_side_t *tmp = current_side->side_ptr;
                        current_side->side_ptr = NULL;
                        stop->side_ptr = current_side;
                        stop = current_side;
                        current_side = tmp;
                }
        }
        if (*new_start == NULL){
                *new_start = pivot;
        }
        *new_end = stop;
        return pivot;
}

/* a fucntion that executes the quick sort recursively on the table passed in the argument with the finishing node being end
if end is NULL it sorts the hole list */

ei_side_t* quick_sort_recursive( ei_side_t* table, ei_side_t* end){
        if (!table || table == end){
                return table;
        }
        ei_side_t* new_start = NULL;
        ei_side_t* new_end = NULL;

        ei_side_t* pivot = partition(table, end, &new_start, &new_end);
        if (new_start != pivot){
                ei_side_t* tmp = get_end(new_start, pivot);
                tmp -> side_ptr = NULL;
                new_start = quick_sort_recursive(new_start, tmp);
                tmp = get_end(new_start, NULL);
                tmp -> side_ptr = pivot;
        }
        pivot -> side_ptr = quick_sort_recursive(pivot -> side_ptr, new_end);
        return new_start;
}

/* it's useful calling the quicksort like that */
void quick_sort(ei_side_t** table){
        *table = quick_sort_recursive(*table, get_end(*table, NULL));
        return;
}


/* function that rounds float given in the parameter lists according to filling rules given */

int round_x(float xymin, ei_bool_t start){
        int floor_x = (int) xymin;
        if (start) {
                if (floor(xymin) == xymin){
                        return floor_x;
                }
                return floor_x + 1;
        }
        else{
                if (floor(xymin) == xymin){
                        return floor_x - 1;
                }
                return floor_x;
        }
}


void			ei_draw_polygon		(ei_surface_t			surface,
                                                            const ei_linked_point_t*	first_point,
                                                            ei_color_t			color,
                                                            const ei_rect_t*		clipper){
        /* Creation of TC Table */
        int M, m, M_prev;
        M = first_point->point.y;
        m = first_point->point.y;
        ei_linked_point_t* current_point = (ei_linked_point_t*) first_point;
        do {
                M_prev = M;
                M = max(M, current_point->point.y);
                m = min(m, current_point->point.y);
                current_point = current_point->next;
        }while (current_point != first_point);
        int len = M_prev - m;
        ei_side_t** TC_table;
        TC_table = calloc(len ,sizeof(ei_side_t));

        /* filling TC table */
        for (int i =0; i<=len; i++){
                *(TC_table + i) = NULL;
        }
        ei_linked_point_t* next_point = current_point->next;
        do {
                if (current_point->point.y != next_point->point.y) {
                        int max_y, x_min_y, min_y;
                        if (current_point->point.y < next_point->point.y) {
                                max_y = next_point->point.y;
                                min_y = current_point->point.y;
                                x_min_y = current_point->point.x;
                        } else {
                                max_y = current_point->point.y;
                                min_y = next_point->point.y;
                                x_min_y = next_point->point.x;
                        };
                        ei_point_t diff = ei_point_sub(current_point->point, next_point->point);
                        float coeff = (float) diff.x / diff.y; /* converted to a float division by adding float to diif.x*/

                        ei_side_t *current_side = malloc(sizeof(ei_side_t*));
                        current_side->ymax = max_y;
                        current_side->xymin = x_min_y;
                        current_side->inv_pente = coeff;
                        int index = min_y -m;
                        current_side->side_ptr = *(TC_table + index);
                        *(TC_table +index) = current_side;
                }
                current_point = next_point;
                next_point = current_point->next;
        }while (current_point != first_point);


        /*Creation of TCA table */
        ei_side_t* sent = malloc(sizeof(ei_side_t));
        sent->xymin = -1; sent->ymax = -1; sent->inv_pente = 0; sent->side_ptr = NULL;
        ei_side_t* TCA_table;
        int y = 0;
        do{
                ei_side_t* current_side = sent->side_ptr;
                ei_side_t* previous_side = sent;
                /* insert in TCA_table sides of TC_table(y) without respecting the crescent order according to xymin*/
                if ( y < len && *(TC_table +y) != NULL){
                        previous_side = *(TC_table +y);
                        current_side = (*(TC_table +y)) -> side_ptr;
                        while (current_side != NULL){
                                current_side = current_side -> side_ptr;
                                previous_side = previous_side -> side_ptr;
                        }
                        previous_side -> side_ptr = sent->side_ptr;
                        sent->side_ptr = *(TC_table +y);
                        *(TC_table +y) = NULL;
                }
                TCA_table = sent -> side_ptr;
                /* delete sides in TCA_table with y == ymax */
                previous_side = sent;
                current_side = TCA_table;
                while( current_side != NULL){
                        if ( current_side ->ymax == y+m){
                                previous_side->side_ptr = current_side ->side_ptr;
                                free(current_side);
                                current_side = previous_side -> side_ptr;
                                continue;
                        }
                        previous_side = current_side;
                        current_side = current_side -> side_ptr;

                }
                TCA_table = sent -> side_ptr;

        /* Creation of TC Table */
                /* update TCA_table to keep the right order */
                quick_sort(&TCA_table);
                sent -> side_ptr = TCA_table;

                /*fill the polygon*/
                previous_side = TCA_table;
                int width = hw_surface_get_size(surface).width;
                int sup;
                int x;
                while (previous_side != NULL){
                        x = round_x(previous_side->xymin, EI_TRUE);
                        current_side = previous_side -> side_ptr;
                        uint32_t* first_pixel = (uint32_t*) hw_surface_get_buffer(surface)+ (y+m)*width + x;
                        if (current_side != NULL){
                                sup = round_x(current_side-> xymin, EI_FALSE) - x;
                                previous_side = current_side -> side_ptr;
                        }
                        else{
                                sup = width - x;
                                previous_side = current_side;
                        }
                        for (int i = 0; i<= sup; i++){
                                ei_bool_t var = clipping(clipper, x+i, y+m);
                                if (var){
                                        uint32_t color_to_draw = ei_map_rgba(surface, color);
                                        if (hw_surface_has_alpha(surface)){
                                                ei_map_transparency(surface, color, *first_pixel);
                                        }

                                        *first_pixel = color_to_draw;
                                }
                                first_pixel++;
                        }
                }

                /* update xymin */
                current_side = TCA_table;
                while( current_side != NULL){
                        current_side->xymin = current_side ->xymin + current_side ->inv_pente;
                        current_side = current_side->side_ptr;
                }

                y++;
        } while (not_empty(TC_table, y, len) || TCA_table != NULL);
        free(sent);
        free(TC_table);
}


int same_copy_surface(ei_surface_t dst_surface, const ei_rect_t* dst_clipper, ei_surface_t src_surface, const ei_rect_t* src_clipper){
        int src_width, src_height, dst_width, dst_height;
        src_width = hw_surface_get_size(src_surface). width;
        src_height = hw_surface_get_size(src_surface).height;
        dst_width = hw_surface_get_size(dst_surface).width;
        dst_height = hw_surface_get_size(dst_surface).height;
        int n;
        if (dst_clipper == NULL && src_clipper == NULL) {
                n = (int) (src_width == dst_width && src_height == dst_height);
        }
        else if (dst_clipper != NULL && src_clipper == NULL){
                n = (int) (src_width == dst_clipper ->size.width && src_height == dst_clipper->size.height);
        }
        else if (dst_clipper == NULL){
                n = (int) (dst_width == src_clipper ->size.width && dst_height == src_clipper->size.height);
        }
        else{
                n = (int) (dst_clipper->size.width == src_clipper ->size.width && dst_clipper->size.height == src_clipper->size.height);
        }
        return n;
}





int			ei_copy_surface		(ei_surface_t		destination,
                                                           const ei_rect_t*	dst_rect,
                                                           ei_surface_t		source,
                                                           const ei_rect_t*	src_rect,
                                                           ei_bool_t		alpha) {

        int n = same_copy_surface(destination, dst_rect, source, src_rect);

        if (n){
                /* source and destination pixel pointers both start at the top_left of the clipper_used */
                uint32_t *source_pixel = (uint32_t *) hw_surface_get_buffer(source) + (src_rect->top_left.y) * hw_surface_get_size(source).width + (src_rect->top_left.x);
                uint32_t *dst_pixel = (uint32_t *) hw_surface_get_buffer(destination) + (dst_rect->top_left.y) * hw_surface_get_size(destination).width + (dst_rect->top_left.x);
                int x, y;
                for (y = 0; y <=src_rect->size.height; y++) {
                        /* each y for loop copies one line inside the clipper */
                        for (x = 0; x <= src_rect->size.width; x++) {
                                /* each x for loop copies one line inside the clipper */
                                if (alpha) { /* pixel is combination of source and destination */
                                        *dst_pixel = ei_map_transparency(destination, ei_map_pixel(source, *source_pixel),
                                                                         *dst_pixel);
                                } else { /* pixel is source only and alpha channel is set to opaque */
                                        ei_color_t source_color = ei_map_pixel(source, *source_pixel);
                                        source_color.alpha = 255;
                                        *dst_pixel = ei_map_rgba(destination, source_color);
                                }
                                source_pixel++;
                                dst_pixel++;
                        }
                        source_pixel += hw_surface_get_size(source).width - src_rect->size.width - 1;
                        dst_pixel += hw_surface_get_size(destination).width - dst_rect->size.width - 1;
                }
        }
        return (!n);
}

void			ei_draw_text		(ei_surface_t		surface,
                                                         const ei_point_t*	where,
                                                         const char*		text,
                                                         ei_font_t		font,
                                                         ei_color_t		color,
                                                         const ei_rect_t*	clipper){
        /* does nothing if there is no text to display */
        if((text != NULL) && (text[0] == '\0')){
                return;
        }

        /*initialisation of the font used to draw text */
        ei_font_t font_used = font;
        if (font == NULL){
                font_used = ei_default_font;
        }

        /* initialise text surface */
        ei_surface_t text_surface;
        text_surface = hw_text_create_surface(text, font_used, color);
        hw_surface_lock(text_surface);
        ei_rect_t text_rectangle = hw_surface_get_rect(text_surface);
        ei_bool_t alpha_existence = hw_surface_has_alpha(text_surface);


        ei_rect_t* surface_clipper = malloc(sizeof(ei_rect_t));
        if (clipper != NULL){
                surface_clipper ->top_left  = ei_point_zero();
                surface_clipper -> size = clipper ->size;
        }
        else {
                surface_clipper = NULL;
        }

        /* get drawing zone */
        ei_rect_t* text_clipper = ei_intersect_rectangles(&text_rectangle, surface_clipper);
        surface_clipper = ei_intersect_rectangles(text_clipper, surface_clipper);
        surface_clipper-> top_left = *where;

        /* drawing text */
        ei_copy_surface(surface, surface_clipper, text_surface, text_clipper, alpha_existence);


        /* getting rid of text surface */
        hw_surface_unlock(text_surface);
        hw_surface_free(text_surface);
        free(text_clipper);
        free(surface_clipper);
}

