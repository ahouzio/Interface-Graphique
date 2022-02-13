//
// Created by oussama on 24/05/2021.
//

#ifndef DRAW_FUNCT_H

static float pi = 3.14159265359;
/**
 * \brief       Un côté du polygone:
 * @param       ymax        Le numéro de scanline à partir de laquelle le côté n’aura plus d’intersection.
 * @param       xymin       L’abscisse de l’intersection du côté avec la première scanline qui intersecte ce côté.
 *                          Elle sera mise à jour à chaque nouvelle scanline.
 * @param       bres_par    Les paramètres du côté pour l’algorithme de Bresenham : E, |∆x|, |∆y|.
 * @param       cote_ptr    Un pointeur vers une autre structure représentant un côté.
 */
typedef struct ei_side_t{
    int                 ymax;
    int                 xymin;
    float                 inv_pente;
    struct ei_side_t*          side_ptr;
}ei_side_t;


/**
 * \brief	calculates the intersection between two rectangles and returns the pointer to the corresponding rectangle.
 *
 * @param	first_rectangle	        pointer to the first rectangle
 * @param	second_rectangle	pointer to the second rectangle
 */

ei_rect_t*              ei_intersect_rectangles(ei_rect_t* first_rectangle, ei_rect_t* second_rectangle);


/**
 * \brief	Draws an arc.
 *
 * @param	rayon	        Number of pixels between the center point and a point of the arc
 * @param	angle_debut	angle between the horizontal axis and the first point of the arc such that we go counter clockwise.
 * @param	angle_fin	angle between the horizontal axis and the last point of the arc.
 * @param	centre          center of the arc.
 */
ei_linked_point_t *arc    (int rayon, float angle_debut, float angle_fin, ei_point_t centre);

typedef enum{
    partie_haute = 1,
    partie_basse = -1,
    partie_complete = 0
}ei_partie_button;

/**
 * \brief	returns the linked list of the botton,upper part of a button or the it's rectangle inside.
 */
ei_linked_point_t *     rounded_frame (ei_rect_t* rect, int rayon, ei_partie_button position);
/**
 * \brief	returns the linked list of the botton or the upper part of a frame or the it's rectangle inside.
 */
ei_linked_point_t *     cute_frame (ei_rect_t* rect, int rayon, ei_partie_button position);

/**
 * \brief	computes the position of the point of the anchor

 */
void compute_anchor_pos(ei_anchor_t anchor, ei_size_t *size, ei_rect_t *rectangle, ei_point_t *anchor_position);
#define DRAW_FUNCT_H

#endif
