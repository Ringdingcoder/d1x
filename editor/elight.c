/*
THE COMPUTER CODE CONTAINED HEREIN IS THE SOLE PROPERTY OF PARALLAX
SOFTWARE CORPORATION ("PARALLAX").  PARALLAX, IN DISTRIBUTING THE CODE TO
END-USERS, AND SUBJECT TO ALL OF THE TERMS AND CONDITIONS HEREIN, GRANTS A
ROYALTY-FREE, PERPETUAL LICENSE TO SUCH END-USERS FOR USE BY SUCH END-USERS
IN USING, DISPLAYING,  AND CREATING DERIVATIVE WORKS THEREOF, SO LONG AS
SUCH USE, DISPLAY OR CREATION IS FOR NON-COMMERCIAL, ROYALTY OR REVENUE
FREE PURPOSES.  IN NO EVENT SHALL THE END-USER USE THE COMPUTER CODE
CONTAINED HEREIN FOR REVENUE-BEARING PURPOSES.  THE END-USER UNDERSTANDS
AND AGREES TO THE TERMS HEREIN AND ACCEPTS THE SAME BY USE OF THIS FILE.  
COPYRIGHT 1993-1998 PARALLAX SOFTWARE CORPORATION.  ALL RIGHTS RESERVED.
*/
/*
 * $Source$
 * $Revision$
 * $Author$
 * $Date$
 * 
 * Editor lighting functions.
 * 
 * $Log$
 * Revision 1.1  2002/07/22 09:19:33  Administrator
 * Initial revision
 *
 * Revision 1.1.1.1  1999/06/14 22:02:55  donut
 * Import of d1x 1.37 source.
 *
 * Revision 2.0  1995/02/27  11:35:16  john
 * Version 2.0! No anonymous unions, Watcom 10.0, with no need
 * for bitmaps.tbl.
 * 
 * Revision 1.21  1994/06/14  16:59:23  mike
 * Fix references to tmap_num2, must strip off orientation bits.
 * 
 * Revision 1.20  1994/05/31  12:31:57  mike
 * fix bug in lighting -- WALL_IS_DOORWAY return value getting ignored,
 * almost never recursively propagated light.
 * 
 * Revision 1.19  1994/05/19  23:35:12  mike
 * Support uv coordinates in range 0..1.0.
 * 
 * Revision 1.18  1994/05/16  12:05:29  john
 * Made texturemap light be a fix from 0 to 1.
 * 
 * Revision 1.17  1994/05/14  18:00:38  matt
 * Got rid of externs in source (non-header) files
 * 
 * Revision 1.16  1994/05/03  11:04:27  mike
 * Add function to select edge.
 * 
 * Revision 1.15  1994/04/20  17:29:11  yuan
 * Fixed bug where tmaps above 256 don't light properly.
 * (duh!)
 * 
 * Revision 1.14  1994/03/22  14:20:46  yuan
 * Made texture map 1 also cast light.  (Cumulative with tmap_num2)
 * 
 * Revision 1.13  1994/03/15  16:34:14  yuan
 * Fixed bm loader (might have some changes in walls and switches)
 * 
 * Revision 1.12  1994/02/22  18:55:10  yuan
 * Ambient lighting "shines" on doors too!
 * 
 * Revision 1.11  1994/02/17  12:05:55  matt
 * Got rid of warnings
 * 
 * Revision 1.10  1994/02/16  22:28:03  mike
 * fix ambient lighting and smoothing.
 * 
 * Revision 1.9  1994/02/14  12:05:42  mike
 * change segment data structure.
 * 
 * Revision 1.8  1994/01/26  17:27:45  yuan
 * Still not perfected ambient lighting
 * 
 * Revision 1.7  1994/01/25  17:58:08  yuan
 * Added ambient lighting, and also added fixing bogus segments
 * functions to the editor... (they don't work fully... need to
 * check out seguvs.c
 * 
 * Revision 1.6  1994/01/24  11:46:10  yuan
 * *** empty log message ***
 * 
 * Revision 1.5  1994/01/24  11:03:05  yuan
 * Set lgiht maximum added... Changes are still in progress
 * 
 * Revision 1.4  1994/01/18  19:16:07  yuan
 * Added assign default to lighting pad.
 * 
 * Revision 1.3  1993/12/17  12:26:00  mike
 * Add functions for setting light values on whole segment at once.
 * 
 * Revision 1.2  1993/12/16  16:56:12  mike
 * Add new texture map lighting control functions.
 * 
 * Revision 1.1  1993/12/16  13:21:50  mike
 * Initial revision
 * 
 * 
 */


#ifdef RCS
static char rcsid[] = "$Id$";
#endif

#include <stdio.h>
//#include <stdlib.h>
//#include <stdarg.h>
//#include <math.h>
//#include <string.h>

#include "inferno.h"
#include "segment.h"
#include "editor.h"
#include "seguvs.h"

#include "wall.h"

#include "textures.h"

#include "fix.h"
#include "mono.h"
#include "error.h"
#include "kdefs.h"
#include "gameseg.h"

#include "texmap.h"

// -----------------------------------------------------------------------------
//	Return light intensity at an instance of a vertex on a side in a segment.
fix get_light_intensity(segment *segp, int sidenum, int vert)
{
	Assert(sidenum <= MAX_SIDES_PER_SEGMENT);
	Assert(vert <= 3);

	return segp->sides[sidenum].uvls[vert].l;
}

// -----------------------------------------------------------------------------
//	Set light intensity at a vertex, saturating in .5 to 15.5
void set_light_intensity(segment *segp, int sidenum, int vert, fix intensity)
{
	Assert(sidenum <= MAX_SIDES_PER_SEGMENT);
	Assert(vert <= 3);

	if (intensity < MIN_LIGHTING_VALUE)
		intensity = MIN_LIGHTING_VALUE;

	if (intensity > MAX_LIGHTING_VALUE)
		intensity = MAX_LIGHTING_VALUE;

	segp->sides[sidenum].uvls[vert].l = intensity;

	Update_flags |= UF_WORLD_CHANGED;
}


// -----------------------------------------------------------------------------
//	Add light intensity to a vertex, saturating in .5 to 15.5
void add_light_intensity(segment *segp, int sidenum, int vert, fix intensity)
{
//	fix	new_intensity;

	set_light_intensity(segp, sidenum, vert, segp->sides[sidenum].uvls[vert].l + intensity);
}


// -----------------------------------------------------------------------------
//	Recursively apply light to segments.
//	If current side is a wall, apply light there.
//	If not a wall, apply light to child through that wall.
//	Notes:
//		It is possible to enter a segment twice by taking different paths.  It is easy
//		to prevent this by maintaining a list of visited segments, but it is important
//		to reach segments with the greatest light intensity.  This can be done by doing
//		a breadth-first-search, or by storing the applied intensity with a visited segment,
//		and if the current intensity is brighter, then apply the difference between it and
//		the previous intensity.
//		Note that it is also possible to visit the original light-casting segment, for example
//		going from segment 0 to 2, then from 2 to 0.  This is peculiar and probably not
//		desired, but not entirely invalid.  2 reflects some light back to 0.
void apply_light_intensity(segment *segp, int sidenum, fix intensity, int depth)
{
	int	wid_result;

	if (intensity == 0)
		return;

	wid_result = WALL_IS_DOORWAY(segp, sidenum);
	if ((wid_result != WID_FLY_FLAG) && (wid_result != WID_NO_WALL)) {
		int	v;
		for (v=0; v<4; v++)							// add light to this wall
			add_light_intensity(segp, sidenum, v, intensity);
		return;										// we return because there is a wall here, and light does not shine through walls
	}

	//	No wall here, so apply light recursively
	if (depth < 3) {
		int	s;
		for (s=0; s<MAX_SIDES_PER_SEGMENT; s++)
			apply_light_intensity(&Segments[segp->children[sidenum]], s, intensity/3, depth+1);
	}

}

// -----------------------------------------------------------------------------
//	Top level recursive function for applying light.
//	Calls apply_light_intensity.
//	Uses light value on segp:sidenum (tmap_num2 defines light value) and applies
//	the associated intensity to segp.  It calls apply_light_intensity to apply intensity/3
//	to all neighbors.  apply_light_intensity recursively calls itself to apply light to
//	subsequent neighbors (and forming loops, see above).
void propagate_light_intensity(segment *segp, int sidenum) 
{
	int		v,s;
	fix		intensity;
	short		texmap;

	intensity = 0;
	texmap = segp->sides[sidenum].tmap_num;
	intensity += TmapInfo[texmap].lighting;
	texmap = (segp->sides[sidenum].tmap_num2) & 0x3fff;
	intensity += TmapInfo[texmap].lighting;

	if (intensity > 0) {
		for (v=0; v<4; v++)
			add_light_intensity(segp, sidenum, v, intensity);
	
		//	Now, for all sides which are not the same as sidenum (the side casting the light),
		//	add a light value to them (if they have no children, ie, they have a wall there).
		for (s=0; s<MAX_SIDES_PER_SEGMENT; s++)
			if (s != sidenum)
				apply_light_intensity(segp, s, intensity/2, 1);
	}

}


// -----------------------------------------------------------------------------
//	Highest level function, bound to a key.  Apply ambient light to all segments based
//	on user-defined light sources.
int LightAmbientLighting()
{
	int seg, side;

	for (seg=0; seg<=Highest_segment_index; seg++)
		for (side=0;side<MAX_SIDES_PER_SEGMENT;side++)
			propagate_light_intensity(&Segments[seg], side);
	return 0;
}


// -----------------------------------------------------------------------------
int LightSelectNextVertex(void)
{
	Curvert++;
	if (Curvert >= 4)
		Curvert = 0;

	Update_flags |= UF_WORLD_CHANGED;

	return	1;
}

// -----------------------------------------------------------------------------
int LightSelectNextEdge(void)
{
	Curedge++;
	if (Curedge >= 4)
		Curedge = 0;

	Update_flags |= UF_WORLD_CHANGED;

	return	1;
}

// -----------------------------------------------------------------------------
//	Copy intensity from current vertex to all other vertices on side.
int LightCopyIntensity(void)
{
	int	v,intensity;

	intensity = get_light_intensity(Cursegp, Curside, Curvert);

	for (v=0; v<4; v++)
		if (v != Curvert)
			set_light_intensity(Cursegp, Curside, v, intensity);

	return	1;
}

// -----------------------------------------------------------------------------
//	Copy intensity from current vertex to all other vertices on side.
int LightCopyIntensitySegment(void)
{
	int	s,v,intensity;

	intensity = get_light_intensity(Cursegp, Curside, Curvert);

	for (s=0; s<MAX_SIDES_PER_SEGMENT; s++)
		for (v=0; v<4; v++)
			if ((s != Curside) || (v != Curvert))
				set_light_intensity(Cursegp, s, v, intensity);

	return	1;
}

// -----------------------------------------------------------------------------
int LightDecreaseLightVertex(void)
{
	set_light_intensity(Cursegp, Curside, Curvert, get_light_intensity(Cursegp, Curside, Curvert)-F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}

// -----------------------------------------------------------------------------
int LightIncreaseLightVertex(void)
{
	set_light_intensity(Cursegp, Curside, Curvert, get_light_intensity(Cursegp, Curside, Curvert)+F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}

// -----------------------------------------------------------------------------
int LightDecreaseLightSide(void)
{
	int	v;

	for (v=0; v<4; v++)
		set_light_intensity(Cursegp, Curside, v, get_light_intensity(Cursegp, Curside, v)-F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}

// -----------------------------------------------------------------------------
int LightIncreaseLightSide(void)
{
	int	v;

	for (v=0; v<4; v++)
		set_light_intensity(Cursegp, Curside, v, get_light_intensity(Cursegp, Curside, v)+F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}

// -----------------------------------------------------------------------------
int LightDecreaseLightSegment(void)
{
	int	s,v;

	for (s=0; s<MAX_SIDES_PER_SEGMENT; s++)
		for (v=0; v<4; v++)
			set_light_intensity(Cursegp, s, v, get_light_intensity(Cursegp, s, v)-F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}

// -----------------------------------------------------------------------------
int LightIncreaseLightSegment(void)
{
	int	s,v;

	for (s=0; s<MAX_SIDES_PER_SEGMENT; s++)
		for (v=0; v<4; v++)
			set_light_intensity(Cursegp, s, v, get_light_intensity(Cursegp, s, v)+F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}

// -----------------------------------------------------------------------------
int LightSetDefault(void)
{
	int	v;

	for (v=0; v<4; v++)
		set_light_intensity(Cursegp, Curside, v, DEFAULT_LIGHTING);

	return	1;
}


// -----------------------------------------------------------------------------
int LightSetMaximum(void)
{
	int	v;

	for (v=0; v<4; v++)
		set_light_intensity(Cursegp, Curside, v, (NUM_LIGHTING_LEVELS-1)*F1_0/NUM_LIGHTING_LEVELS);

	return	1;
}


// -----------------------------------------------------------------------------
int LightSetDefaultAll(void)
{

	assign_default_lighting_all();

	Update_flags |= UF_WORLD_CHANGED;

	return	1;
}



