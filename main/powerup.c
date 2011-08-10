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
 * Code for powerup objects.
 * 
 * $Log$
 * Revision 1.1  2002/07/22 09:19:35  Administrator
 * Initial revision
 *
 * Revision 1.3  2000/11/13 07:15:38  donut
 * fix autoselecting lasers even if primary autoselect turned off
 *
 * Revision 1.2  1999/09/01 01:09:10  sekmu
 * forgot update for quad powerup for new hud views
 *
 * Revision 1.1.1.1  1999/06/14 22:11:13  donut
 * Import of d1x 1.37 source.
 *
 * Revision 2.2  1995/03/24  13:50:36  john
 * Added mega-wowie zowie to release.
 * 
 * Revision 2.1  1995/03/21  14:38:39  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.0  1995/02/27  11:27:15  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.94  1995/02/22  13:46:03  allender
 * remove anonymous unions from object structure
 * 
 * Revision 1.93  1995/02/06  15:52:51  mike
 * add mini megawow powerup for giving reasonable weapons.
 * 
 * Revision 1.92  1995/01/23  22:49:59  mike
 * drop energy instead of primary weapon if you have primary weapon
 * (drop nothing if want to drop vulcan ammo and you are maxed out)
 * if you have primary weapon and primary weapon there, get energy instead.
 * 
 * Revision 1.91  1995/01/19  09:42:22  allender
 * record laser levels for demos
 * 
 * Revision 1.90  1994/12/31  12:28:01  rob
 * Added sound for coop key grabs.
 * 
 * Revision 1.89  1994/12/19  19:55:17  rob
 * Fixing key semantics for coop game.
 * 
 * Revision 1.88  1994/12/07  12:55:21  mike
 * tweak vulcan amounts.
 * 
 * Revision 1.87  1994/12/06  13:55:36  matt
 * Made shield & energy powerup messages round to match HUD message
 * 
 * Revision 1.86  1994/12/03  19:03:57  matt
 * Fixed vulcan ammo HUD message
 * 
 * Revision 1.85  1994/11/29  11:35:41  rob
 * Added sound casting for grabbing powerups.
 * 
 * Revision 1.84  1994/11/28  11:26:38  matt
 * Cleaned up hud message printing for picking up weapons
 * 
 * Revision 1.83  1994/11/27  23:14:01  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.82  1994/11/21  16:02:51  mike
 * comment out unused powerups.
 * 
 * Revision 1.81  1994/11/20  18:25:47  john
 * Fixed some #ifndef RELEASE inconsistancies.
 * 
 * Revision 1.80  1994/11/19  23:54:13  mike
 * limit megawowiezowie to shareware powerups if in shareware version.
 * 
 * Revision 1.79  1994/11/14  16:06:16  yuan
 * Made cloak and invulnerability only picked up once.
 * 
 * Revision 1.78  1994/11/07  17:41:06  mike
 * messages for when you're fully stocked with missiles.
 * 
 * Revision 1.77  1994/10/28  14:42:50  john
 * Added sound volumes to all sound calls.
 * 
 * Revision 1.76  1994/10/26  15:55:23  yuan
 * Made vulcan cannon give 100 ammo if it has less than that.
 * 
 * Revision 1.75  1994/10/26  15:54:57  yuan
 * *** empty log message ***
 * 
 * Revision 1.74  1994/10/25  14:31:25  allender
 * Fixed bug where getting cloak powerup while cloaked resulted in
 * player being cloaked forever.
 * 
 * Revision 1.73  1994/10/25  10:51:21  matt
 * Vulcan cannon powerups now contain ammo count
 * 
 * Revision 1.72  1994/10/21  20:41:32  mike
 * Fix silly backwards (- instead of +) bug in invulnerability powerup.
 * 
 * Revision 1.71  1994/10/20  09:49:23  mike
 * Fix up powerups in some way.
 * 
 * Revision 1.70  1994/10/19  11:16:25  mike
 * Limit amount of each type of ammo player can hold.
 * 
 * Revision 1.69  1994/10/17  14:12:11  matt
 * Added sound for powerup disappearance effect
 * 
 * Revision 1.68  1994/10/17  14:07:04  mike
 * Make shields and energy max out at 200.
 * 
 * Revision 1.67  1994/10/16  12:43:37  mike
 * Don't allow you to pick up a primary weapon, or invulnerability, you already have.
 * Make cloak time additive.
 * 
 * Revision 1.66  1994/10/15  19:05:30  mike
 * Define constants for vulcan ammo amounts.
 * 
 * Revision 1.65  1994/10/14  15:57:28  mike
 * When you pick up a laser boost or quad_laser powerup, update weapon display.
 * 
 * Revision 1.64  1994/10/13  10:57:51  adam
 * fiddled with powerup disappearance
 * 
 * Revision 1.63  1994/10/12  13:07:33  mike
 * Make powerup play vclip when it goes away.
 * 
 * Revision 1.62  1994/10/12  08:04:42  mike
 * Make proximity powerup worth 4 bombs.
 * 
 * Revision 1.61  1994/10/08  23:37:33  matt
 * Don't pick up weapons you already have; also fixed auto_select bug
 * for seconary weapons
 * 
 * Revision 1.60  1994/10/08  15:41:00  mike
 * Diminish palette effect due to powerups.
 * 
 * Revision 1.59  1994/10/07  23:37:45  matt
 * Made weapons select when pick up better one
 * 
 * Revision 1.58  1994/10/07  22:09:20  rob
 * Added network hook for grabbing the cloaking device.
 *
 */


#ifdef RCS
#pragma off (unreferenced)
static char rcsid[] = "$Id$";
#pragma on (unreferenced)
#endif

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "3d.h"
#include "mono.h"

#include "inferno.h"
#include "object.h"
#include "game.h"

#include "fireball.h"
#include "powerup.h"
#include "gauges.h"

#include "sounds.h"
#include "player.h"

#include "wall.h"
#include "text.h"
#include "weapon.h"
#include "laser.h"
#include "scores.h"
#include "multi.h"

#include "newdemo.h"

#ifdef EDITOR
#include "gr.h"	//	for powerup outline drawing
#include "editor/editor.h"
#endif

#define	ENERGY_MAX	i2f(200)
#define	SHIELD_MAX	i2f(200)

int N_powerup_types = 0;
powerup_type_info Powerup_info[MAX_POWERUP_TYPES];

int powerup_start_level[MAX_POWERUP_TYPES];

//process this powerup for this frame
void do_powerup_frame(object *obj)
{
	vclip_info *vci = &obj->rtype.vclip_info;
	vclip *vc = &Vclip[vci->vclip_num];

	vci->frametime -= FrameTime;
	
	while (vci->frametime < 0 ) {

		vci->frametime += vc->frame_time;
		
		vci->framenum++;
		if (vci->framenum >= vc->num_frames)
			vci->framenum=0;
	}

	if (obj->lifeleft <= 0) {
		object_create_explosion(obj->segnum, &obj->pos, fl2f(3.5), VCLIP_POWERUP_DISAPPEARANCE );

		if ( Vclip[VCLIP_POWERUP_DISAPPEARANCE].sound_num > -1 )
			digi_link_sound_to_object( Vclip[VCLIP_POWERUP_DISAPPEARANCE].sound_num, (short) (obj-Objects), 0, F1_0);
	}
}

#ifdef EDITOR
extern fix blob_vertices[];

//	blob_vertices has 3 vertices in it, 4th must be computed
void draw_blob_outline(void)
{
	fix	v3x, v3y;

	v3x = blob_vertices[4] - blob_vertices[2] + blob_vertices[0];
	v3y = blob_vertices[5] - blob_vertices[3] + blob_vertices[1];

	gr_setcolor(BM_XRGB(63, 63, 63));

	mprintf((0, "[%7.3f %7.3f]  [%7.3f %7.3f]  [%7.3f %7.3f]\n", f2fl(blob_vertices[0]), f2fl(blob_vertices[1]), f2fl(blob_vertices[2]), f2fl(blob_vertices[3]), f2fl(blob_vertices[4]), f2fl(blob_vertices[5]) ));

	gr_line(blob_vertices[0], blob_vertices[1], blob_vertices[2], blob_vertices[3]);
	gr_line(blob_vertices[2], blob_vertices[3], blob_vertices[4], blob_vertices[5]);
	gr_line(blob_vertices[4], blob_vertices[5], v3x, v3y);

	gr_line(v3x, v3y, blob_vertices[0], blob_vertices[1]);
}
#endif

void draw_powerup(object *obj)
{
	#ifdef EDITOR
	blob_vertices[0] = 0x80000;
	#endif

	draw_object_blob(obj, Vclip[obj->rtype.vclip_info.vclip_num].frames[obj->rtype.vclip_info.framenum] );

	#ifdef EDITOR
	if ((Function_mode == FMODE_EDITOR) && (Cur_object_index == obj-Objects))
		if (blob_vertices[0] != 0x80000)
			draw_blob_outline();
	#endif

}

//void mprintf_powerup_info(void)
//{
//	int		i;
//mprintf((0, "Powerup: %s\n", text));
//for (i=0; i<5; i++) {
//	char	has_text[12];
//
//	if (Players[Player_num].primary_weapon_flags & (1 << i))
//		strcpy(has_text,"PRESENT");
//	else
//		strcpy(has_text,"NOPE   ");
//	has_text[8] = 0;
//
//	mprintf((0, "Weapon %i = %s, ammo = %6i, name = %s\n", i, has_text, Players[Player_num].primary_ammo[i], Primary_weapon_names[i]));
//}
//
//for (i=0; i<5; i++) {
//	char	has_text[12];
//
//	if (Players[Player_num].secondary_weapon_flags & (1 << i))
//		strcpy(has_text,"PRESENT");
//	else
//		strcpy(has_text,"NOPE   ");
//
//	mprintf((0, "Weapon %i = %s, ammo = %6i, name = %s\n", i, has_text, Players[Player_num].secondary_ammo[i], Secondary_weapon_names[i]));
//}
//}

void powerup_basic(int redadd, int greenadd, int blueadd, int score, char *format, ...)
{
	char		text[120];
	va_list	args;

	va_start(args, format );
	vsprintf(text, format, args);
	va_end(args);

	PALETTE_FLASH_ADD(redadd,greenadd,blueadd);

	hud_message(MSGC_PICKUP_OK, text);

	//mprintf_powerup_info();

	add_points_to_score(score);

}

//#ifndef RELEASE
//	Give the megawow powerup!
void do_megawow_powerup(int quantity)
{
	int i;

	powerup_basic(30, 0, 30, 1, "MEGA-WOWIE-ZOWIE!");
#ifndef SHAREWARE
	Players[Player_num].primary_weapon_flags = 0xff;
	Players[Player_num].secondary_weapon_flags = 0xff;
#else
	Players[Player_num].primary_weapon_flags = 0xff ^ (HAS_PLASMA_FLAG | HAS_FUSION_FLAG);
	Players[Player_num].secondary_weapon_flags = 0xff ^ (HAS_SMART_FLAG | HAS_MEGA_FLAG);
#endif
	for (i=0; i<3; i++)
		Players[Player_num].primary_ammo[i] = 200;

	for (i=0; i<3; i++)
		Players[Player_num].secondary_ammo[i] = quantity;

#ifndef SHAREWARE
	for (i=3; i<5; i++)
		Players[Player_num].primary_ammo[i] = 200;

	for (i=3; i<5; i++)
		Players[Player_num].secondary_ammo[i] = quantity/5;
#endif

	if (Newdemo_state == ND_STATE_RECORDING)
		newdemo_record_laser_level(Players[Player_num].laser_level, MAX_LASER_LEVEL);

	Players[Player_num].energy = F1_0*200;
	Players[Player_num].shields = F1_0*200;
	Players[Player_num].flags |= PLAYER_FLAGS_QUAD_LASERS;
	Players[Player_num].laser_level = MAX_LASER_LEVEL;
	update_laser_weapon_info();

}
//#endif

int pick_up_energy(void)
{
	int	used=0;

	if (Players[Player_num].energy < ENERGY_MAX) {
		Players[Player_num].energy += 3*F1_0 + 3*F1_0*(NDL - Difficulty_level);
		if (Players[Player_num].energy > ENERGY_MAX)
			Players[Player_num].energy = ENERGY_MAX;
		powerup_basic(15,15,7, ENERGY_SCORE, "%s %s %d",TXT_ENERGY,TXT_BOOSTED_TO,f2ir(Players[Player_num].energy));
		used=1;
	} else
		hud_message(MSGC_PICKUP_TOOMUCH, TXT_MAXED_OUT,TXT_ENERGY);

	return used;
}

int pick_up_vulcan_ammo(void)
{
	int	used=0;

//added/killed on 1/21/99 by Victor Rachels ... how is this wrong?
//-killed-        int     pwsave = Primary_weapon;                // Ugh, save selected primary weapon around the picking up of the ammo.  I apologize for this code.  Matthew A. Toschlog
	if (pick_up_ammo(CLASS_PRIMARY, VULCAN_INDEX, VULCAN_AMMO_AMOUNT)) {
		powerup_basic(7, 14, 21, VULCAN_AMMO_SCORE, "%s!", TXT_VULCAN_AMMO);
		used = 1;
	} else {
		hud_message(MSGC_PICKUP_TOOMUCH, "%s %d %s!",TXT_ALREADY_HAVE,f2i(VULCAN_AMMO_SCALE * Primary_ammo_max[VULCAN_INDEX]),TXT_VULCAN_ROUNDS);
		used = 0;
	}
//-killed-        Primary_weapon = pwsave;
//end this section kill - VR

	return used;
}

//	returns true if powerup consumed
int do_powerup(object *obj)
{
	int used=0;
	int vulcan_ammo_to_add_with_cannon;

	if ((Player_is_dead) || (ConsoleObject->type == OBJ_GHOST))
		return 0;

	switch (obj->id) {
		case POW_EXTRA_LIFE:
			Players[Player_num].lives++;
			powerup_basic(15, 15, 15, 0, TXT_EXTRA_LIFE);
			used=1;
			break;
		case POW_ENERGY:
			used = pick_up_energy();
			break;
		case POW_SHIELD_BOOST:
			if (Players[Player_num].shields < SHIELD_MAX) {
				Players[Player_num].shields += 3*F1_0 + 3*F1_0*(NDL - Difficulty_level);
				if (Players[Player_num].shields > SHIELD_MAX)
					Players[Player_num].shields = SHIELD_MAX;
				powerup_basic(0, 0, 15, SHIELD_SCORE, "%s %s %d",TXT_SHIELD,TXT_BOOSTED_TO,f2ir(Players[Player_num].shields));
				used=1;
			} else
				hud_message(MSGC_PICKUP_TOOMUCH, TXT_MAXED_OUT,TXT_SHIELD);
			break;
		case POW_LASER:
			if (Players[Player_num].laser_level >= MAX_LASER_LEVEL) {
				Players[Player_num].laser_level = MAX_LASER_LEVEL;
				hud_message(MSGC_PICKUP_TOOMUCH, TXT_MAXED_OUT,TXT_LASER);
                        } else {
				if (Newdemo_state == ND_STATE_RECORDING)
					newdemo_record_laser_level(Players[Player_num].laser_level, (byte) (Players[Player_num].laser_level + 1));
				Players[Player_num].laser_level++;
				powerup_basic(10, 0, 10, LASER_SCORE, "%s %s %d",TXT_LASER,TXT_BOOSTED_TO, Players[Player_num].laser_level+1);
				update_laser_weapon_info();
                                //added on 3/21/99 by Victor Rachels for update
                                gauge_update_hud_mode=1;
                                //end this section addition -VR
				used=1;
        			if (Allow_primary_cycle){//fix laser select even if autoselect off -MPM
                                 if(Players[Player_num].flags&PLAYER_FLAGS_QUAD_LASERS)
                                  maybe_select_primary(9+Players[Player_num].laser_level);
                                 else
                                  maybe_select_primary(5+Players[Player_num].laser_level);
				}
			}
			if (!used && !(Game_mode & GM_MULTI) )
				used = pick_up_energy();
			break;
		case POW_MISSILE_1:
			used=pick_up_secondary(CONCUSSION_INDEX,1);
			break;
		case POW_MISSILE_4:
			used=pick_up_secondary(CONCUSSION_INDEX,4);
			break;

		case POW_KEY_BLUE:
			if (Players[Player_num].flags & PLAYER_FLAGS_BLUE_KEY)
				break;
			#ifdef NETWORK
			multi_send_play_sound(Powerup_info[obj->id].hit_sound, F1_0);
			#endif
			digi_play_sample( Powerup_info[obj->id].hit_sound, F1_0 );
			Players[Player_num].flags |= PLAYER_FLAGS_BLUE_KEY;
			powerup_basic(0, 0, 15, KEY_SCORE, "%s %s",TXT_BLUE,TXT_ACCESS_GRANTED);
			if (Game_mode & GM_MULTI)
				used=0;
			else
				used=1;
			break;
		case POW_KEY_RED:
			if (Players[Player_num].flags & PLAYER_FLAGS_RED_KEY)
				break;
			#ifdef NETWORK
			multi_send_play_sound(Powerup_info[obj->id].hit_sound, F1_0);
			#endif
			digi_play_sample( Powerup_info[obj->id].hit_sound, F1_0 );
			Players[Player_num].flags |= PLAYER_FLAGS_RED_KEY;
			powerup_basic(15, 0, 0, KEY_SCORE, "%s %s",TXT_RED,TXT_ACCESS_GRANTED);
			if (Game_mode & GM_MULTI)
				used=0;
			else
				used=1;
			break;
		case POW_KEY_GOLD:
			if (Players[Player_num].flags & PLAYER_FLAGS_GOLD_KEY)
				break;
			#ifdef NETWORK
			multi_send_play_sound(Powerup_info[obj->id].hit_sound, F1_0);
			#endif
			digi_play_sample( Powerup_info[obj->id].hit_sound, F1_0 );
			Players[Player_num].flags |= PLAYER_FLAGS_GOLD_KEY;
			powerup_basic(15, 15, 7, KEY_SCORE, "%s %s",TXT_YELLOW,TXT_ACCESS_GRANTED);
			if (Game_mode & GM_MULTI)
				used=0;
			else
				used=1;
			break;
		case POW_QUAD_FIRE:
			if (!(Players[Player_num].flags & PLAYER_FLAGS_QUAD_LASERS)) {
				Players[Player_num].flags |= PLAYER_FLAGS_QUAD_LASERS;
				powerup_basic(15, 15, 7, QUAD_FIRE_SCORE, "%s!",TXT_QUAD_LASERS);
				update_laser_weapon_info();
                                //added on 8/31/99 by Victor Rachels for update
                                gauge_update_hud_mode=1;
                                //end this section addition -VR
                                //added on 10/8/98 by Victor Rachels for quad autoselect
                                //changed on 10/21/98 by Victor Rachels to add other lasers
        			if (Allow_primary_cycle)//fix laser select even if autoselect off -MPM
                                	maybe_select_primary(9+Players[Player_num].laser_level);
                                //end change
                                //end this section addition
				used=1;
			} else
				hud_message(MSGC_PICKUP_ALREADY, "%s %s!",TXT_ALREADY_HAVE,TXT_QUAD_LASERS);
			if (!used && !(Game_mode & GM_MULTI) )
				used = pick_up_energy();
			break;
		case	POW_VULCAN_WEAPON:
			if ((used = pick_up_primary(VULCAN_INDEX)) != 0) {
				vulcan_ammo_to_add_with_cannon = obj->ctype.powerup_info.count;
				if (vulcan_ammo_to_add_with_cannon < VULCAN_WEAPON_AMMO_AMOUNT) vulcan_ammo_to_add_with_cannon = VULCAN_WEAPON_AMMO_AMOUNT;
				pick_up_ammo(CLASS_PRIMARY, VULCAN_INDEX, vulcan_ammo_to_add_with_cannon);
			}

//added/edited 8/3/98 by Victor Rachels to fix vulcan multi bug
//check if multi, if so, pick up ammo w/o using, set ammo left. else, normal

//killed 8/27/98 by Victor Rachels to fix vulcan ammo multiplying.  new way
// is by spewing the current held ammo when dead.
//-killed                        if (!used && (Game_mode & GM_MULTI))
//-killed                        {
//-killed                         int tempcount;                          
//-killed                           tempcount=Players[Player_num].primary_ammo[VULCAN_INDEX];
//-killed                            if (pick_up_ammo(CLASS_PRIMARY, VULCAN_INDEX, obj->ctype.powerup_info.count))
//-killed                             obj->ctype.powerup_info.count -= Players[Player_num].primary_ammo[VULCAN_INDEX]-tempcount;
//-killed                        }
//end kill - Victor Rachels

			if (!used && !(Game_mode & GM_MULTI) )
//end addition/edit - Victor Rachels
				used = pick_up_vulcan_ammo();
			break;
		case	POW_SPREADFIRE_WEAPON:
			used = pick_up_primary(SPREADFIRE_INDEX);
			if (!used && !(Game_mode & GM_MULTI) )
				used = pick_up_energy();
			break;
		case	POW_PLASMA_WEAPON:
			used = pick_up_primary(PLASMA_INDEX);
			if (!used && !(Game_mode & GM_MULTI) )
				used = pick_up_energy();
			break;
		case	POW_FUSION_WEAPON:
			used = pick_up_primary(FUSION_INDEX);
			if (!used && !(Game_mode & GM_MULTI) )
				used = pick_up_energy();
			break;

		case	POW_PROXIMITY_WEAPON:
			used=pick_up_secondary(PROXIMITY_INDEX,4);
			break;
		case	POW_SMARTBOMB_WEAPON:
			used=pick_up_secondary(SMART_INDEX,1);
			break;
		case	POW_MEGA_WEAPON:
			used=pick_up_secondary(MEGA_INDEX,1);
			break;
		case	POW_VULCAN_AMMO: {
			used = pick_up_vulcan_ammo();
			if (!used && !(Game_mode & GM_MULTI) )
				used = pick_up_vulcan_ammo();
			break;
		}
			break;
		case	POW_HOMING_AMMO_1:
			used=pick_up_secondary(HOMING_INDEX,1);
			break;
		case	POW_HOMING_AMMO_4:
			used=pick_up_secondary(HOMING_INDEX,4);
			break;
		case	POW_CLOAK:
			if (Players[Player_num].flags & PLAYER_FLAGS_CLOAKED) {
				hud_message(MSGC_PICKUP_ALREADY, "%s %s!",TXT_ALREADY_ARE,TXT_CLOAKED);
				break;
			} else {
				Players[Player_num].cloak_time = GameTime;	//	Not! changed by awareness events (like player fires laser).
				Players[Player_num].flags |= PLAYER_FLAGS_CLOAKED;
				ai_do_cloak_stuff();
				#ifdef NETWORK
				if (Game_mode & GM_MULTI)
					multi_send_cloak();
				#endif
				powerup_basic(-10,-10,-10, CLOAK_SCORE, "%s!",TXT_CLOAKING_DEVICE);
				used = 1;
				break;
			}
		case	POW_INVULNERABILITY:
			if (Players[Player_num].flags & PLAYER_FLAGS_INVULNERABLE) {
				hud_message(MSGC_PICKUP_ALREADY, "%s %s!",TXT_ALREADY_ARE,TXT_INVULNERABLE);
				break;
			} else {
				Players[Player_num].invulnerable_time = GameTime;
				Players[Player_num].flags |= PLAYER_FLAGS_INVULNERABLE;
				powerup_basic(7, 14, 21, INVULNERABILITY_SCORE, "%s!",TXT_INVULNERABILITY);
				used = 1;
				break;
			}
	#ifndef RELEASE
		case	POW_MEGAWOW:
			do_megawow_powerup(50);
			used = 1;
			break;
	#endif

		default:
			break;
		}

//always say used, until physics problem (getting stuck on unused powerup)
//is solved.  Note also the break statements above that are commented out
//!!	used=1;

	if (used && Powerup_info[obj->id].hit_sound  > -1 ) {
		#ifdef NETWORK
		if (Game_mode & GM_MULTI) // Added by Rob, take this out if it turns out to be not good for net games!
			multi_send_play_sound(Powerup_info[obj->id].hit_sound, F1_0);
		#endif
		digi_play_sample( Powerup_info[obj->id].hit_sound, F1_0 );
	}

	return used;

}

void pow_count_add(int *pow_level, int id, int count, object *pow) {
	switch (id) {
		case POW_VULCAN_WEAPON:
			if (pow != NULL)
				pow_level[POW_VULCAN_AMMO] += pow->ctype.powerup_info.count;
			else
				pow_level[POW_VULCAN_AMMO] += VULCAN_WEAPON_AMMO_AMOUNT * count;
			pow_level[POW_VULCAN_WEAPON] += count;
			break;
		case POW_VULCAN_AMMO:
			pow_level[POW_VULCAN_AMMO] += VULCAN_AMMO_AMOUNT * count;
			break;
		case POW_MISSILE_4:
		case POW_HOMING_AMMO_4:
			pow_level[id - 1] += 4 * count;
			break;
		default:
			pow_level[id] += count;
	}
}

void pow_count_level(int *pow_level) {
	int i;

	memset(pow_level, 0, MAX_POWERUP_TYPES * sizeof(pow_level[0]));
	for (i = 0; i <= Highest_object_index; i++)
		if (!(Objects[i].flags & OF_SHOULD_BE_DEAD))
			switch (Objects[i].type) {
			    case OBJ_POWERUP:
				    pow_count_add(pow_level, Objects[i].id, 1, &Objects[i]);
				    break;
#if 0 // now not added until released by robot
			    case OBJ_ROBOT:
				    if (Objects[i].contains_type == OBJ_POWERUP)
					    pow_count_add(pow_level, Objects[i].contains_id, Objects[i].contains_count, NULL);
				    break;
#endif
			}
}

void count_powerup_start_level() {
	int player_pows[MAX_POWERUP_TYPES];

	pow_count_level(powerup_start_level);
	player_to_pow_count(&Players[Player_num], player_pows);
	pow_add_level_pow_count(player_pows);
}

#ifndef NDEBUG
void dump_pow_count(char *title, int *pow_count);
#endif

// add a random created powerup to the level count
void pow_add_random(object *obj) {
	if (obj->contains_count > 0 && obj->contains_type == OBJ_POWERUP)
		pow_count_add(powerup_start_level, obj->contains_id, obj->contains_count, NULL);
	#ifndef NDEBUG
#ifdef NETWORK
	if (!(Game_mode & GM_NETWORK) ||
            Netgame.protocol_version != MULTI_PROTO_D1X_VER)
                return;
#endif
	mprintf((1, "pow_add_random: type=%d, id=%d, count=%d\n",obj->contains_type,
	    obj->contains_id,obj->contains_count));
	dump_pow_count("pow_add_random: now start level", powerup_start_level);
	#endif
}

void pow_add_level_pow_count(int *pow_count) {
	int i;

	for (i = 0; i < MAX_POWERUP_TYPES; i++)
		powerup_start_level[i] += pow_count[i];
	#ifndef NDEBUG
#ifdef NETWORK
	if (!(Game_mode & GM_NETWORK) ||
            Netgame.protocol_version != MULTI_PROTO_D1X_VER)
		return;
#endif
	dump_pow_count("pow_add_level_pow_count: pow_count", pow_count);
	dump_pow_count("pow_add_level_pow_count: now start level", powerup_start_level);
	#endif
}

#if 0 // clipping version
// fill pow_count with items that would be dropped if player dies
void player_to_pow_count(player *player, int *pow_count)
{
	memset(pow_count, 0, sizeof(int) * MAX_POWERUP_TYPES);
	pow_count[POW_LASER] = player->laser_level;
	pow_count[POW_QUAD_FIRE] = (player->flags & PLAYER_FLAGS_QUAD_LASERS) != 0;
	pow_count[POW_CLOAK] = (player->flags & PLAYER_FLAGS_CLOAKED) != 0;
	pow_count[POW_VULCAN_WEAPON] = (player->primary_weapon_flags & HAS_VULCAN_FLAG) != 0;
	pow_count[POW_SPREADFIRE_WEAPON] = (player->primary_weapon_flags & HAS_SPREADFIRE_FLAG) != 0;
	pow_count[POW_PLASMA_WEAPON] = (player->primary_weapon_flags & HAS_PLASMA_FLAG) != 0;
	pow_count[POW_FUSION_WEAPON] = (player->primary_weapon_flags & HAS_FUSION_FLAG) != 0;
	pow_count[POW_MISSILE_1] = MIN(player->secondary_ammo[CONCUSSION_INDEX], 4);
	pow_count[POW_HOMING_AMMO_1] = MIN(player->secondary_ammo[HOMING_INDEX], 6);
	pow_count[POW_PROXIMITY_WEAPON] = MIN((player->secondary_ammo[PROXIMITY_INDEX]+2)/4, 3);
	pow_count[POW_SMARTBOMB_WEAPON] = MIN(player->secondary_ammo[SMART_INDEX], 3);
	pow_count[POW_MEGA_WEAPON] = MIN(player->secondary_ammo[MEGA_INDEX], 3);
	pow_count[POW_VULCAN_AMMO] = MIN(player->primary_ammo[VULCAN_INDEX], 200);
	pow_count[POW_INVULNERABILITY] = (player->flags & PLAYER_FLAGS_INVULNERABLE) != 0;
	// Always drop a shield and energy powerup in multiplayer
	if (Game_mode & GM_MULTI) {
		pow_count[POW_SHIELD_BOOST] = 1;
		pow_count[POW_ENERGY] = 1;
	}
}
#else
// fill pow_count with items that player currently has
void player_to_pow_count(player *player, int *pow_count)
{
	memset(pow_count, 0, sizeof(int) * MAX_POWERUP_TYPES);
	pow_count[POW_LASER] = player->laser_level;
	pow_count[POW_QUAD_FIRE] = (player->flags & PLAYER_FLAGS_QUAD_LASERS) != 0;
	pow_count[POW_CLOAK] = (player->flags & PLAYER_FLAGS_CLOAKED) != 0;
	pow_count[POW_VULCAN_WEAPON] = (player->primary_weapon_flags & HAS_VULCAN_FLAG) != 0;
	pow_count[POW_SPREADFIRE_WEAPON] = (player->primary_weapon_flags & HAS_SPREADFIRE_FLAG) != 0;
	pow_count[POW_PLASMA_WEAPON] = (player->primary_weapon_flags & HAS_PLASMA_FLAG) != 0;
	pow_count[POW_FUSION_WEAPON] = (player->primary_weapon_flags & HAS_FUSION_FLAG) != 0;
	pow_count[POW_MISSILE_1] = player->secondary_ammo[CONCUSSION_INDEX];
	pow_count[POW_HOMING_AMMO_1] = player->secondary_ammo[HOMING_INDEX];
	pow_count[POW_PROXIMITY_WEAPON] = (player->secondary_ammo[PROXIMITY_INDEX]+2)/4;
	pow_count[POW_SMARTBOMB_WEAPON] = player->secondary_ammo[SMART_INDEX];
	pow_count[POW_MEGA_WEAPON] = player->secondary_ammo[MEGA_INDEX];
	pow_count[POW_VULCAN_AMMO] = player->primary_ammo[VULCAN_INDEX];
	pow_count[POW_INVULNERABILITY] = (player->flags & PLAYER_FLAGS_INVULNERABLE) != 0;
	// Always drop a shield and energy powerup in multiplayer
	if (Game_mode & GM_MULTI) {
		pow_count[POW_SHIELD_BOOST] = 1;
		pow_count[POW_ENERGY] = 1;
	}
}
#endif


// This must be in a special order to keep the
// Net_create_objnums[] order compatible
int player_drop_powerups[] = { POW_LASER, POW_QUAD_FIRE, POW_CLOAK,
	POW_VULCAN_WEAPON, POW_SPREADFIRE_WEAPON, POW_PLASMA_WEAPON,
	POW_FUSION_WEAPON, POW_PROXIMITY_WEAPON, POW_SMARTBOMB_WEAPON,
	POW_MEGA_WEAPON, POW_HOMING_AMMO_1, POW_VULCAN_AMMO,
	POW_MISSILE_1, POW_SHIELD_BOOST, POW_ENERGY,
	POW_INVULNERABILITY };

// reduce player drop powerups
void clip_player_pow_count(int *pow_count)
{
	int i;
	 /*laser,quad,cloak,vulc,spread,plasma,fusion,*/
	 /*prox,smart,mega,hom,vula,con,sh,en,invul*/
	static int pow_max[NUM_PLAYER_DROP_POWERUPS] =
		{ 3,1,1,1,1,1,1,3,3,3,6,VULCAN_AMMO_MAX,4,1,1,0 };
	for (i = 0; i < NUM_PLAYER_DROP_POWERUPS; i++)
		if (pow_count[player_drop_powerups[i]] > pow_max[i])
			pow_count[player_drop_powerups[i]] = pow_max[i];
}

// may this powerup be added to the level?
// returns number of powerups left if true, -1 if unknown, otherwise 0.
int may_create_powerup(int powerup)
{
#ifdef NETWORK
	int pow_count[MAX_POWERUP_TYPES];

	if (!(Game_mode & GM_NETWORK)
#ifdef NETWORK
		|| Netgame.protocol_version != MULTI_PROTO_D1X_VER
#endif
		)
	    return -1; // say unknown if not in D1X network game
	pow_count_level(pow_count);
#ifndef NDEBUG
	dump_pow_count("may_create_powerup: now in level:", pow_count);
	mprintf((1,"may_create_powerup %d: now: %d start: %d remaining: %d\n",
	     powerup, pow_count[powerup], powerup_start_level[powerup],
	     powerup_start_level[powerup] - pow_count[powerup]));
#endif
//        if(powerup==POW_SHIELD_BOOST) return 1;
	return MAX(powerup_start_level[powerup] - pow_count[powerup], 0);
#endif
        return -1;
}


#ifndef NDEBUG
void dump_pow_count(char *title, int *pow_count) {
    int i, j = 0;

    mprintf((1, "-- powerup count: %s\n", title));
    for (i = 0; i < MAX_POWERUP_TYPES; i++) {
	    if (pow_count[i]) {
		    mprintf((1, "powerup %2d: %4d x\n", i, pow_count[i]));
		    j++;
	    }
    }
    mprintf((1, "-- powerup count different: %d\n", j));
}
#endif
