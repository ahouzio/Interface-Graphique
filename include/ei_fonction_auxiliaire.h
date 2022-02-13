#ifndef FCT_AUX_H
#define FCT_AUX_H




/**
 * \brief	Returns the maximum between two integers.
 *
 * @param	a 	first integer.
 * @param       b       second integer
 */
int max(int a, int b);

/**
 * \brief	Returns the minimum between two integers.
 *
 * @param	a 	first integer.
 * @param       b       second integer
 */
int min(int a, int b);


/**
* \brief	exchange the values of two integer variables.
*
* @param	*a    	pointer to the first integer.
* @param	*b	pointer to the second integer.
*/
static void permuter(int *a, int *b );



/**
* \brief	returns ei_bool_t to tell if the point is inside clipper.
*
* @param	*clipper    	pointer to the clipper.
* @param	point_abscissa	abscissa of the point.
 * @param	point_orderly	orderly of the point.
*/
ei_bool_t clipping(const ei_rect_t* clipper, int point_abscissa , int point_orderly);


/**
* \brief	frees a circular list
*
* @param	** first_point    	pointer to the pointer to the first point of a linked list of points.
*/
void ei_free_linked_point (ei_linked_point_t** first_point);


#endif
