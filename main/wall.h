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
 * $Log$
 * Revision 1.1  2002/07/22 09:19:35  Administrator
 * Initial revision
 *
 * Revision 1.1.1.1  1999/06/14 22:13:22  donut
 * Import of d1x 1.37 source.
 *
 * Revision 2.0  1995/02/27  11:31:36  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.47  1994/11/19  15:20:35  mike
 * rip out unused code and data
 * 
 * Revision 1.46  1994/10/25  15:40:12  yuan
 * MAX_WALLS pumped up
 * 
 * Revision 1.45  1994/10/23  19:17:07  matt
 * Fixed bug with "no key" messages
 * 
 * Revision 1.44  1994/10/18  15:38:03  mike
 * Define hidden walls.
 * 
 * Revision 1.43  1994/10/04  13:32:26  adam
 * commented out MAX_DOOR_ANIMS
 * 
 * Revision 1.42  1994/10/04  13:31:21  adam
 * upped MAX_WALL_ANIMS to 30
 * 
 * Revision 1.41  1994/09/29  00:42:30  matt
 * Made hitting a locked door play a sound
 * 
 * Revision 1.40  1994/09/27  15:42:41  mike
 * Prototype Wall_names.
 * 
 * Revision 1.39  1994/09/23  22:15:32  matt
 * Made doors not close on objects, made doors open again if shot while
 * closing, and cleaned up walls/doors a bit.
 * 
 * Revision 1.38  1994/09/22  15:31:33  matt
 * Mucked with, and hopefully improved, exploding walls
 * 
 * Revision 1.37  1994/09/21  17:17:05  mike
 * Make objects stuck in doors go away when door opens.
 * 
 * Revision 1.36  1994/09/13  21:10:46  matt
 * Added wclips that use tmap1 instead of tmap2, saving lots of merging
 * 
 * Revision 1.35  1994/09/13  20:11:08  yuan
 * *** empty log message ***
 * 
 * Revision 1.34  1994/09/10  13:31:53  matt
 * Made exploding walls a type of blastable walls.
 * Cleaned up blastable walls, making them tmap2 bitmaps.
 * 
 * Revision 1.33  1994/08/17  12:55:34  matt
 * Added external walls to wall_is_doorway
 * 
 * Revision 1.32  1994/08/15  17:54:35  john
 * *** empty log message ***
 * 
 * Revision 1.31  1994/08/15  17:46:56  yuan
 * Added external walls, fixed blastable walls.
 * 
 * Revision 1.30  1994/08/05  21:17:21  matt
 * Allow two doors to be linked together
 * 
 * Revision 1.29  1994/08/01  10:39:10  matt
 * Parenthesized parms to WID() macro
 * 
 * Revision 1.28  1994/07/20  17:35:03  yuan
 * Some minor bug fixes and new key gauges...
 * 
 * Revision 1.27  1994/07/19  14:32:03  yuan
 * Fixed keys bug... renumbered some constants.
 * 
 * Revision 1.26  1994/07/14  22:38:29  matt
 * Added exploding doors
 * 
 * Revision 1.25  1994/07/11  15:08:43  yuan
 * Wall anim file names stored in structure.
 *  
 */

#ifndef _WALL_H
#define _WALL_H

#include "inferno.h"
#include "segment.h"
#include "object.h"

//#include "vclip.h"

#define MAX_WALLS					175	// Maximum number of walls
#define MAX_WALL_ANIMS			30		// Maximum different types of doors
#define MAX_DOORS					50		// Maximum number of open doors
// not used -> #define MAX_DOOR_ANIMS			20		// Maximum different types of doors

// Various wall types.
#define WALL_NORMAL				0  	// Normal wall
#define WALL_BLASTABLE			1  	// Removable (by shooting) wall
#define WALL_DOOR					2  	// Door 
#define WALL_ILLUSION			3  	// Wall that appears to be there, but you can fly thru
#define WALL_OPEN					4		// Just an open side. (Trigger)
#define WALL_CLOSED				5		// Wall.  Used for transparent walls.

// Various wall flags.
#define WALL_BLASTED				1  	// Blasted out wall.
#define WALL_DOOR_OPENED		2  	// Open door. 
#define WALL_DOOR_LOCKED		8		// Door is locked.
#define WALL_DOOR_AUTO			16		// Door automatically closes after time.
#define WALL_ILLUSION_OFF		32		// Illusionary wall is shut off.

// Wall states
#define WALL_DOOR_CLOSED		0		// Door is closed
#define WALL_DOOR_OPENING		1		// Door is opening.
#define WALL_DOOR_WAITING		2		// Waiting to close
#define WALL_DOOR_CLOSING		3		// Door is closing

//note: a door is considered opened (i.e., it has WALL_OPENED set) when it 
//is more than half way open.  Thus, it can have any of OPENING, CLOSING, 
//or WAITING bits set when OPENED is set.

#define KEY_NONE					1
#define KEY_BLUE					2
#define KEY_RED				   4
#define KEY_GOLD				   8

#define WALL_HPS					100*F1_0		// Normal wall's hp
#define WALL_DOOR_INTERVAL	 	5*F1_0		// How many seconds a door is open

#define DOOR_OPEN_TIME			i2f(2)		// How long takes to open
#define DOOR_WAIT_TIME			i2f(5)		// How long before auto door closes

#define MAX_CLIP_FRAMES			20

// WALL_IS_DOORWAY flags.
#define WID_FLY_FLAG					1
#define WID_RENDER_FLAG				2
#define WID_RENDPAST_FLAG			4
#define WID_EXTERNAL_FLAG			8

//	WALL_IS_DOORWAY return values			F/R/RP
#define WID_WALL						2	// 0/1/0		wall	
#define WID_TRANSPARENT_WALL		6	//	0/1/1		transparent wall
#define WID_ILLUSORY_WALL			3	//	1/1/0		illusory wall
#define WID_TRANSILLUSORY_WALL	7	//	1/1/1		transparent illusory wall
#define WID_NO_WALL					5	//	1/0/1		no wall, can fly through
#define WID_EXTERNAL					8	// 0/0/0/1	don't see it, dont fly through it

#define	MAX_STUCK_OBJECTS	32

typedef struct stuckobj {
	short	objnum, wallnum;
	int	signature;
} stuckobj;

typedef struct wall {
	int	segnum,sidenum;	// Seg & side for this wall
	fix   hps;				  	// "Hit points" of the wall. 
	int	linked_wall;		// number of linked wall
	ubyte	type; 			  	// What kind of special wall.
	ubyte	flags;				// Flags for the wall.		
	ubyte	state;				// Opening, closing, etc.
	byte	trigger;				// Which trigger is associated with the wall.
	byte	clip_num;			// Which	animation associated with the wall. 
	ubyte	keys;					// which keys are required
	short	pad;					// keep longword aligned
	} __pack__ wall;

typedef struct active_door {
	int		n_parts;					// for linked walls
	short		front_wallnum[2];		// front wall numbers for this door
	short		back_wallnum[2]; 		// back wall numbers for this door
	fix		time;						// how long been opening, closing, waiting
} __pack__ active_door;

//wall clip flags
#define WCF_EXPLODES		1		//door explodes when opening
#define WCF_BLASTABLE	2		//this is a blastable wall
#define WCF_TMAP1			4		//this uses primary tmap, not tmap2
#define WCF_HIDDEN		8		//this uses primary tmap, not tmap2

typedef struct {
	fix				play_time;
	short				num_frames;
	short				frames[MAX_CLIP_FRAMES];
	short				open_sound;
	short				close_sound;
	short				flags;
	char				filename[13];
	char				pad;
} __pack__ wclip;

extern char	Wall_names[7][10];

//#define WALL_IS_DOORWAY(seg,side) wall_is_doorway(seg, side)

#define WALL_IS_DOORWAY(seg,side) (((seg)->children[(side)] == -1) ? WID_WALL : ((seg)->children[(side)] == -2) ? WID_EXTERNAL_FLAG : ((seg)->sides[(side)].wall_num == -1) ? WID_NO_WALL : wall_is_doorway((seg), (side)))

extern wall Walls[MAX_WALLS];			// Master walls array
extern int Num_walls;					// Number of walls

extern active_door ActiveDoors[MAX_DOORS];	//	Master doors array
extern int Num_open_doors;				// Number of open doors

extern wclip WallAnims[MAX_WALL_ANIMS];
extern int Num_wall_anims;

extern int walls_bm_num[MAX_WALL_ANIMS];

// Initializes all walls (i.e. no special walls.)
extern void wall_init();
																							 
// Automatically checks if a there is a doorway (i.e. can fly through)
extern int wall_is_doorway ( segment *seg, int side );

// Deteriorate appearance of wall. (Changes bitmap (paste-ons)) 
extern void wall_damage(segment *seg, int side, fix damage);

// Destroys a blastable wall. (So it is an opening afterwards)
extern void wall_destroy(segment *seg, int side);

void wall_illusion_on(segment *seg, int side);

void wall_illusion_off(segment *seg, int side);

// Opens a door, including animation and other processing.
void do_door_open(int door_num);

// Closes a door, including animation and other processing.
void do_door_close(int door_num);

// Opens a door  
extern void wall_open_door(segment *seg, int side);

// Closes a door (called after given interval)
extern void wall_close_door(int wall_num);

//return codes for wall_hit_process()
#define WHP_NOT_SPECIAL		0		//wasn't a quote-wall-unquote
#define WHP_NO_KEY			1		//hit door, but didn't have key
#define WHP_BLASTABLE		2		//hit blastable wall
#define WHP_DOOR				3		//a door (which will now be opening)

// Determines what happens when a wall is shot
//obj is the object that hit...either a weapon or the player himself
extern int wall_hit_process(segment *seg, int side, fix damage, int playernum, object *obj );

// Opens/destroys specified door.
extern void wall_toggle(segment *seg, int side);

// Tidy up Walls array for load/save purposes.
extern void reset_walls();

// Called once per frame..
void wall_frame_process();

extern stuckobj	Stuck_objects[MAX_STUCK_OBJECTS];

//	An object got stuck in a door (like a flare).
//	Add global entry.
extern void add_stuck_object(object *objp, int segnum, int sidenum);
extern void remove_obsolete_stuck_objects(void);

//set the tmap_num or tmap_num2 field for a wall/door
extern void wall_set_tmap_num(segment *seg,int side,segment *csegp,int cside,int anim_num,int frame_num);

#endif
