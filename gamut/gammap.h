
/* 
 * Argyll Gamut Mapping Library
 *
 * Author:  Graeme W. Gill
 * Date:    1/10/2000
 * Version: 2.00
 *
 * Copyright 2000 - 2006 Graeme W. Gill
 * All rights reserved.
 *
 * This material is licenced under the GNU AFFERO GENERAL PUBLIC LICENSE Version 3 :-
 * see the License.txt file for licencing details.
 */

/* Gamut mapping object */
struct _gammap {

/* Private: */
	int dbg;			/* NZ to turn on debug messages */
						/* neutral axis alignment transform applied to source: */
	double grot[3][4];	/* Incoming grey axis rotation matrix */
	double igrot[3][4];	/* Inverse of above */
	rspl *grey;			/* Forward L map */
	rspl *igrey;		/* Inverse L map */
						/* Source to destination gamut map applied */
						/* to transformed source: */
	rspl *map;			/* Rotated, L mapped Lab -> Lab gamut map */
	double imin[3], imax[3];	/* Input range limits of map */

/* Public: */

	/* Methods */
	void (*del)(struct _gammap *s);			/* Free ourselves */
	void (*domap)(struct _gammap *s, double *out, double *in);	/* Do the mapping */

}; typedef struct _gammap gammap;

/* Method of black point adaptation */
typedef enum {
	gmm_BPadpt    = 0,		/* Adapt source black point to destination */
	gmm_noBPadpt  = 1,		/* Don't adapt black point to destination */ 
	gmm_bendBP    = 2,		/* Don't adapt black point, bend it to dest. at end */  
	gmm_clipBP    = 3		/* Don't adapt black point, clip it to dest. at end */  
} gmm_BPmap;

/* Creator */
gammap *new_gammap(
	int verb,			/* Verbose flag */
	gamut *sc_gam,		/* Source colorspace gamut */
	gamut *s_gam,		/* Source image gamut (NULL if none) */
	gamut *d_gam,		/* Destination colorspace gamut */
	icxGMappingIntent *gmi, /* Gamut mapping specification */
	int src_kbp,		/* Use K only black point as src gamut black point */
	int dst_kbp,		/* Use K only black point as dst gamut black point */
	int dst_cmymap,		/* masks C = 1, M = 2, Y = 4 to force 100% cusp map */
	int    mapres,		/* Gamut map resolution, typically 9 - 33 */
	double *mn,			/* If not NULL, set minimum mapping input range */
	double *mx,			/* for rspl grid */
	char *diagname		/* If non-NULL, write a gamut mapping diagnostic WRL */
);


	