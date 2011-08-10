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
 * Routines to configure keyboard, joystick, etc..
 * 
 * $Log$
 * Revision 1.1  2002/07/22 09:19:34  Administrator
 * Initial revision
 *
 * Revision 1.11  2000/11/30 10:34:48  donut
 * make next axis config key skip currently allocated axes
 *
 * Revision 1.10  2000/11/30 10:13:38  donut
 * joy configuration next axis key from WraithX
 *
 * Revision 1.9  2000/10/27 04:08:33  donut
 * allow up to 16 mouse buttons to be used (dependant upon arch supporting that many)
 *
 * Revision 1.8  2000/10/27 02:57:28  donut
 * key/joy/etc config boxes and text appear in the right places when modifying config
 *
 * Revision 1.7  2000/10/17 22:14:29  sekmu
 * mingw version joystick 0 movement bug fixed
 *
 * Revision 1.6  2000/04/19 21:27:56  sekmu
 * movable death-cam from WraithX
 *
 * Revision 1.5  1999/11/21 13:00:08  donut
 * Changed screen_mode format.  Now directly encodes res into a 32bit int, rather than using arbitrary values.
 *
 * Revision 1.4  1999/11/20 10:05:17  donut
 * variable size menu patch from Jan Bobrowski.  Variable menu font size support and a bunch of fixes for menus that didn't work quite right, by me (MPM).
 *
 * Revision 1.3  1999/10/14 20:33:06  donut
 * alpha fixes from Falk Hueffner
 *
 * Revision 1.2  1999/09/06 07:01:37  sekmu
 * better dos jostick config menu
 *
 * Revision 1.1.1.1  1999/06/14 22:08:14  donut
 * Import of d1x 1.37 source.
 *
 * Revision 2.11  1995/08/23  16:08:04  john
 * Added version 2 of external controls that passes the ship
 * position and orientation the drivers.
 * 
 * Revision 2.10  1995/07/07  16:48:01  john
 * Fixed bug with new interface.
 * 
 * Revision 2.9  1995/07/03  15:02:32  john
 * Added new version of external controls for Cybermouse absolute position.
 * 
 * Revision 2.8  1995/06/30  12:30:28  john
 * Added -Xname command line.
 * 
 * Revision 2.7  1995/03/30  16:36:56  mike
 * text localization.
 * 
 * Revision 2.6  1995/03/21  14:39:31  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.5  1995/03/16  10:53:07  john
 * Move VFX center to Shift+Z instead of Enter because
 * it conflicted with toggling HUD on/off.
 * 
 * Revision 2.4  1995/03/10  13:47:24  john
 * Added head tracking sensitivity.
 * 
 * Revision 2.3  1995/03/09  18:07:06  john
 * Fixed bug with iglasses tracking not "centering" right.
 * Made VFX have bright headlight lighting.
 * 
 * Revision 2.2  1995/03/08  15:32:39  john
 * Made VictorMaxx head tracking use Greenleaf code.
 * 
 * Revision 2.1  1995/03/06  15:23:31  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:29:26  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.105  1995/02/22  14:11:58  allender
 * remove anonymous unions from object structure
 * 
 * Revision 1.104  1995/02/13  12:01:56  john
 * Fixed bug with buggin not mmaking player faster.
 * 
 * Revision 1.103  1995/02/09  22:00:46  john
 * Added i-glasses tracking.
 * 
 * Revision 1.102  1995/01/24  21:25:47  john
 * Fixed bug with slide/bank on not working with
 * Cyberman heading.,
 * 
 * Revision 1.101  1995/01/24  16:09:56  john
 * Fixed bug with Wingman extreme customize text overwriting title.
 * 
 * Revision 1.100  1995/01/24  12:37:46  john
 * Made Esc exit key define menu.
 * 
 * Revision 1.99  1995/01/23  23:54:43  matt
 * Made keypad enter work
 * 
 * Revision 1.98  1995/01/23  16:42:00  john
 * Made the external controls always turn banking off, leveling off
 * and passed automap state thru to the tsr.
 * 
 * Revision 1.97  1995/01/12  11:41:33  john
 * Added external control reading.
 * 
 * Revision 1.96  1995/01/05  10:43:58  mike
 * Handle case when timer_get_fixed_seconds() goes negative.  Happens at 9.1
 * hours.  Previously, joystick would stop functioning.  Now will work.
 * 
 * Revision 1.95  1994/12/29  11:17:38  john
 * Took out some warnings and mprintf.
 * 
 * Revision 1.94  1994/12/29  11:07:41  john
 * Fixed Thrustmaster and Logitech Wingman extreme
 * Hat by reading the y2 axis during the center stage
 * of the calibration, and using 75, 50, 27, and 3 %
 * as values for the 4 positions.
 * 
 * Revision 1.93  1994/12/27  12:16:20  john
 * Fixed bug with slide on not working with joystick or mouse buttons.
 * 
 * Revision 1.92  1994/12/20  10:34:15  john
 * Made sensitivity work for mouse & joystick and made
 * it only affect, pitch, heading, and roll.
 * 
 * Revision 1.91  1994/12/16  00:11:23  matt
 * Made delete key act normally when debug out
 * 
 * Revision 1.90  1994/12/14  17:41:15  john
 * Added more buttons so that  Yoke would work.
 * 
 * Revision 1.89  1994/12/13  17:25:35  allender
 * Added Assert for bogus time for joystick reading.
 * 
 * Revision 1.88  1994/12/13  14:48:01  john
 * Took out some debugging mprintf's
 * 
 * 
 * Revision 1.87  1994/12/13  14:43:02  john
 * Took out the code in kconfig to build direction array.
 * Called kc_set_controls after selecting a new control type.
 * 
 * Revision 1.86  1994/12/13  01:11:32  john
 * Fixed bug with message clearing overwriting 
 * right border.
 * 
 * Revision 1.85  1994/12/12  00:35:58  john
 * Added or thing for keys.
 * 
 * Revision 1.84  1994/12/09  17:08:06  john
 * Made mouse a bit less sensitive.
 * 
 * Revision 1.83  1994/12/09  16:04:00  john
 * Increased mouse sensitivity.
 * 
 * Revision 1.82  1994/12/09  00:41:26  mike
 * fix hang in automap print screen
 * 
 * Revision 1.81  1994/12/08  11:50:37  john
 * Made strcpy only copy corect number of chars,.
 * 
 * Revision 1.80  1994/12/07  16:16:06  john
 * Added command to check to see if a joystick axes has been used.
 * 
 * Revision 1.79  1994/12/07  14:52:28  yuan
 * Localization 492
 * 
 * Revision 1.78  1994/12/07  13:37:40  john
 * Made the joystick thrust work in reverse.
 * 
 * Revision 1.77  1994/12/07  11:28:24  matt
 * Did a little localization support
 * 
 * Revision 1.76  1994/12/04  12:30:03  john
 * Made the Thrustmaster stick read every frame, not every 10 frames,
 * because it uses analog axis as buttons.
 * 
 * Revision 1.75  1994/12/03  22:35:25  yuan
 * Localization 412
 * 
 * Revision 1.74  1994/12/03  15:39:24  john
 * Made numeric keypad move in conifg.
 * 
 * Revision 1.73  1994/12/01  16:23:39  john
 * Fixed include mistake.
 * 
 * Revision 1.72  1994/12/01  16:07:57  john
 * Fixed bug that disabled joystick in automap because it used gametime, which is
 * paused during automap. Fixed be used timer_Get_fixed_seconds instead of GameTime.
 * 
 * Revision 1.71  1994/12/01  12:30:49  john
 * Made Ctrl+D delete, not Ctrl+E
 * 
 * Revision 1.70  1994/12/01  11:52:52  john
 * Added default values for GamePad.
 * 
 * Revision 1.69  1994/11/30  00:59:12  mike
 * optimizations.
 * 
 * Revision 1.68  1994/11/29  03:45:50  john
 * Added joystick sensitivity; Added sound channels to detail menu.  Removed -maxchannels
 * command line arg.
 * 
 * Revision 1.67  1994/11/27  23:13:44  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.66  1994/11/27  19:52:12  matt
 * Made screen shots work in a few more places
 * 
 * Revision 1.65  1994/11/22  16:54:50  mike
 * autorepeat on missiles.
 * 
 * Revision 1.64  1994/11/21  11:16:17  rob
 * Changed calls to GameLoop to calls to multi_menu_poll and changed
 * conditions under which they are called.
 * 
 * Revision 1.63  1994/11/19  15:14:48  mike
 * remove unused code and data
 * 
 * Revision 1.62  1994/11/18  23:37:56  john
 * Changed some shorts to ints.
 * 
 * Revision 1.61  1994/11/17  13:36:35  rob
 * Added better network hook in kconfig menu.
 * 
 * Revision 1.60  1994/11/14  20:09:13  john
 * Made Tab be default for automap.
 * 
 * Revision 1.59  1994/11/13  16:34:07  matt
 * Fixed victormaxx angle conversions
 * 
 * Revision 1.58  1994/11/12  14:47:05  john
 * Added support for victor head tracking.
 * 
 * Revision 1.57  1994/11/08  15:14:55  john
 * Added more calls so net doesn't die in net game.
 * 
 * Revision 1.56  1994/11/07  14:01:07  john
 * Changed the gamma correction sequencing.
 * 
 * Revision 1.55  1994/11/01  16:40:08  john
 * Added Gamma correction.
 * 
 * Revision 1.54  1994/10/25  23:09:26  john
 * Made the automap key configurable.
 * 
 * Revision 1.53  1994/10/25  13:11:59  john
 * Made keys the way Adam speced 'em for final game.
 * 
 * Revision 1.52  1994/10/24  17:44:22  john
 * Added stereo channel reversing.
 * 
 * Revision 1.51  1994/10/22  13:23:18  john
 * Made default rear view key be R.
 * 
 * Revision 1.50  1994/10/22  13:20:09  john
 * Took out toggle primary/secondary weapons.  Fixed black
 * background for 'axes' and 'buttons' text.
 * 
 * Revision 1.49  1994/10/21  15:20:15  john
 * Made PrtScr do screen dump, not F2.
 * 
 * Revision 1.48  1994/10/21  13:41:36  john
 * Allowed F2 to screen dump.
 * 
 * Revision 1.47  1994/10/17  13:07:05  john
 * Moved the descent.cfg info into the player config file.
 * 
 * Revision 1.46  1994/10/14  15:30:22  john
 * Added Cyberman default positions.
 * 
 * Revision 1.45  1994/10/14  15:24:54  john
 * Made Cyberman work with config.
 * 
 * Revision 1.44  1994/10/14  12:46:04  john
 * Added the ability to reset all to default.
 * 
 * Revision 1.43  1994/10/14  12:18:31  john
 * Made mouse invert axis always be 0 or 1.
 * 
 * Revision 1.42  1994/10/14  12:16:03  john
 * Changed code so that by doing DEL+F12 saves the current kconfig
 * values as default. Added support for drop_bomb key.  Took out
 * unused slots for keyboard.  Made keyboard use control_type of 0
 * save slots.
 * 
 * Revision 1.41  1994/10/13  21:27:02  john
 * Made axis invert value always be 0 or 1.
n * 
 * Revision 1.40  1994/10/13  20:18:15  john
 * Added some more system keys, such as F? and CAPSLOCK.
 * 
 * Revision 1.39  1994/10/13  19:22:29  john
 * Added separate config saves for different devices.
 * Made all the devices work together better, such as mice won't
 * get read when you're playing with the joystick.
 * 
 * Revision 1.38  1994/10/13  15:41:57  mike
 * Remove afterburner.
 * 
 */

#ifdef RCS
static char rcsid[] = "$Id$";
#endif

#define TABLE_CREATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifdef __MSDOS__
#include <dos.h>
#include <io.h>
#endif


#include "error.h"
#include "types.h"
#include "gr.h"
#include "mono.h"
#include "key.h"
#include "palette.h"
#include "game.h"
#include "gamefont.h"
#include "iff.h"
#include "u_mem.h"
#include "joy.h"
#include "mouse.h"
#include "kconfig.h"
#include "gauges.h"
#include "joydefs.h"
#include "render.h"
#include "digi.h"
#include "newmenu.h"
#include "endlevel.h"
#include "multi.h"
#include "timer.h"
#include "text.h"
#include "player.h"
#include "menu.h"
#include "args.h"
#include "key.h"

//added on 2/4/99 by Victor Rachels for new weapon selectable keys
#include "reorder.h"
//end this section addition

//added on 9/2/98 by Matt Mueller
#include "d_delay.h"
//end addition -MM

//added on 3/12/99 by VR to screw with sporbs
#include "physics.h"
//end this section addition - VR

//added on 4/16/99 by VR to add alt vulcan fire
#include "vlcnfire.h"
//end this section addition - VR



// Array used to 'blink' the cursor while waiting for a keypress.
byte fades[64] = { 1,1,1,2,2,3,4,4,5,6,8,9,10,12,13,15,16,17,19,20,22,23,24,26,27,28,28,29,30,30,31,31,31,31,31,30,30,29,28,28,27,26,24,23,22,20,19,17,16,15,13,12,10,9,8,6,5,4,4,3,2,2,1,1 };

//char * invert_text[2] = { "N", "Y" };
//char * joybutton_text[28] = { "BTN 1", "BTN 2", "BTN 3", "BTN 4", "", "TRIG", "LEFT", "HAT �", "RIGHT", "", "", "HAT �", "MID", "", "", "HAT ", "", "", "", "HAT �", "TRIG", "LEFT", "RIGHT", "", "UP","DOWN","LEFT", "RIGHT" };
//char * joyaxis_text[4] = { "X1", "Y1", "X2", "Y2" };
//char * mouseaxis_text[2] = { "L/R", "F/B" };
//char * mousebutton_text[3] = { "Left", "Right", "Mid" };

int invert_text[2] = { TNUM_N, TNUM_Y };
#ifndef __LINUX__
int joybutton_text[28] = 
{ TNUM_BTN_1, TNUM_BTN_2, TNUM_BTN_3, TNUM_BTN_4,
  -1, TNUM_TRIG, TNUM_LEFT, TNUM_HAT_L,
 TNUM_RIGHT, -1, TNUM_HAT2_D, TNUM_HAT_R,
 TNUM_MID, -1, TNUM_HAT2_R, TNUM_HAT_U,
 TNUM_HAT2_L, -1, TNUM_HAT2_U, TNUM_HAT_D,
 TNUM_TRIG, TNUM_LEFT, TNUM_RIGHT, -1, 
  TNUM_UP, TNUM_DOWN, TNUM_LEFT, TNUM_RIGHT };
int joyaxis_text[4] = { TNUM_X1, TNUM_Y1, TNUM_X2, TNUM_Y2 };
#endif
int mouseaxis_text[2] = { TNUM_L_R, TNUM_F_B };
int mousebutton_text[3] = { TNUM_LEFT, TNUM_RIGHT, TNUM_MID };
char * mousebutton_textra[13] = { "M4", "M5", "M6", "M7", "M8", "M9", "M10","M11","M12","M13","M14","M15","M16" };//text for buttons above 3. -MPM

//added/removed by Victor Rachels for adding rebindable keys for these
// KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0
ubyte system_keys[] = { KEY_ESC, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, KEY_MINUS, KEY_EQUAL, KEY_PRINT_SCREEN };

//extern void GameLoop(int, int );

control_info Controls;

ubyte Config_digi_volume = 16;
ubyte Config_midi_volume = 16;
ubyte Config_control_type = 0;
ubyte Config_channels_reversed = 0;
ubyte Config_joystick_sensitivity = 8;

fix Cruise_speed=0;


//added/edited on 11/01/98 by Victor Rachels for primary/secondary autotoggle
int Allow_primary_cycle=1;
int Allow_secondary_cycle=1;
//end this section edit - Victor Rachels

#define BT_KEY                  0
#define BT_MOUSE_BUTTON 	1
#define BT_MOUSE_AXIS		2
#define BT_JOY_BUTTON 		3
#define BT_JOY_AXIS             4
#define BT_INVERT               5

char *btype_text[] = { "BT_KEY", "BT_MOUSE_BUTTON", "BT_MOUSE_AXIS", "BT_JOY_BUTTON", "BT_JOY_AXIS", "BT_INVERT" };

#define INFO_Y (188*scale) //scale to res. -MPM

typedef struct kc_item {
        short id;               // The id of this item
	short x, y;				
	short w1;
	short w2;
	short u,d,l,r;
	short text_num1;
	ubyte type;
	ubyte value;		// what key,button,etc
} kc_item;

int Num_items=23;
kc_item *All_items;

ubyte kconfig_settings[CONTROL_MAX_TYPES][MAX_CONTROLS];

//added on 2/4/99 by Victor Rachels to add d1x new keys
ubyte kconfig_d1x_settings[MAX_D1X_CONTROLS];
//end this section addition - VR

//----------- WARNING!!!!!!! -------------------------------------------
// THESE NEXT FOUR BLOCKS OF DATA ARE GENERATED BY PRESSING DEL+F12 WHEN
// IN THE KEYBOARD CONFIG SCREEN.  BASICALLY, THAT PROCEDURE MODIFIES THE
// U,D,L,R FIELDS OF THE ARRAYS AND DUMPS THE NEW ARRAYS INTO KCONFIG.COD
//-------------------------------------------------------------------------

ubyte default_kconfig_settings[CONTROL_MAX_TYPES][MAX_CONTROLS] = {
{KEY_UP, KEY_PAD8, KEY_DOWN, KEY_PAD2, KEY_LEFT, KEY_PAD4, KEY_RIGHT, KEY_PAD6,
 KEY_LALT, 255, 255, KEY_PAD1, 255, KEY_PAD3, 255, KEY_PADMINUS, 255, KEY_PADPLUS,
 255, 255, KEY_Q, KEY_PAD7, KEY_E, KEY_PAD9, KEY_LCTRL, KEY_RCTRL, KEY_SPACEBAR,
 255, KEY_F, 255, KEY_A, 255, KEY_Z, 255, KEY_B, 255, KEY_R, 0xff,0xff,0xff,0xff,
 0xff,0xff,0xff, KEY_TAB, 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
{0x0 ,0x1 ,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1 ,0x0 ,
 0x0 ,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
{0x5 ,0xc ,0xff,0xff,0xff,0xff,0x7 ,0xf ,0x13,0xb ,0xff,0x6 ,0x8 ,0x1 ,0x0 ,
 0x0 ,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
{0x0 ,0x1 ,0xff,0xff,0x2 ,0xff,0x7 ,0xf ,0x13,0xb ,0xff,0xff,0xff,0x1 ,0x0 ,
 0x0 ,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x3 ,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
{0x3 ,0x0 ,0x1 ,0x2 ,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1 ,0x0 ,
 0x0 ,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
{0x0 ,0x1 ,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x1 ,0x0 ,
 0x0 ,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
{0x0 ,0x1 ,0xff,0xff,0x2 ,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x0 ,
 0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0x0 ,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,
//added/edited on 9/3/98 by Victor Rachels to fix the default keysetting
                          0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff},
//end this section change - Victor Rachels
};
//added on 2/4/99 by Victor Rachels to add new keys system
ubyte default_kconfig_d1x_settings[MAX_D1X_CONTROLS] = {
 0x2 ,0xff,0x3 ,0xff,0x4 ,0xff,0x5 ,0xff,0x6 ,0xff,0x7 ,0xff,0x8 ,0xff,0x9 ,
 0xff,0xa ,0xff,0xb ,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
//end this section addition - VR

kc_item kc_keyboard[NUM_ALL_KEY_CONTROLS] = {
        {  0, 15, 49, 71, 26, 43,  2, 23,  1,TNUM_PITCH_FORWARD, BT_KEY, 255 },
	{  1, 15, 49,100, 26, 22,  3,  0, 24,TNUM_PITCH_FORWARD, BT_KEY, 255 },
	{  2, 15, 57, 71, 26,  0,  4, 25,  3,TNUM_PITCH_BACKWARD, BT_KEY, 255 },
	{  3, 15, 57,100, 26,  1,  5,  2, 26,TNUM_PITCH_BACKWARD, BT_KEY, 255 },
	{  4, 15, 65, 71, 26,  2,  6, 27,  5,TNUM_TURN_LEFT, BT_KEY, 255 },
	{  5, 15, 65,100, 26,  3,  7,  4, 28,TNUM_TURN_LEFT, BT_KEY, 255 },
	{  6, 15, 73, 71, 26,  4,  8, 29,  7,TNUM_TURN_RIGHT, BT_KEY, 255 },
	{  7, 15, 73,100, 26,  5,  9,  6, 34,TNUM_TURN_RIGHT, BT_KEY, 255 },
	{  8, 15, 85, 71, 26,  6, 10, 35,  9,TNUM_SLIDE_ON, BT_KEY, 255 },
	{  9, 15, 85,100, 26,  7, 11,  8, 36,TNUM_SLIDE_ON, BT_KEY, 255 },
	{ 10, 15, 93, 71, 26,  8, 12, 37, 11,TNUM_SLIDE_LEFT, BT_KEY, 255 },
	{ 11, 15, 93,100, 26,  9, 13, 10, 44,TNUM_SLIDE_LEFT, BT_KEY, 255 },
	{ 12, 15,101, 71, 26, 10, 14, 45, 13,TNUM_SLIDE_RIGHT, BT_KEY, 255 },
	{ 13, 15,101,100, 26, 11, 15, 12, 30,TNUM_SLIDE_RIGHT, BT_KEY, 255 },
	{ 14, 15,109, 71, 26, 12, 16, 31, 15,TNUM_SLIDE_UP, BT_KEY, 255 },
	{ 15, 15,109,100, 26, 13, 17, 14, 32,TNUM_SLIDE_UP, BT_KEY, 255 },
	{ 16, 15,117, 71, 26, 14, 18, 33, 17,TNUM_SLIDE_DOWN, BT_KEY, 255 },
	{ 17, 15,117,100, 26, 15, 19, 16, 38,TNUM_SLIDE_DOWN, BT_KEY, 255 },
	{ 18, 15,129, 71, 26, 16, 20, 39, 19,TNUM_BANK_ON, BT_KEY, 255 },
	{ 19, 15,129,100, 26, 17, 21, 18, 40,TNUM_BANK_ON, BT_KEY, 255 },
	{ 20, 15,137, 71, 26, 18, 22, 41, 21,TNUM_BANK_LEFT, BT_KEY, 255 },
	{ 21, 15,137,100, 26, 19, 23, 20, 42,TNUM_BANK_LEFT, BT_KEY, 255 },
	{ 22, 15,145, 71, 26, 20,  1, 43, 23,TNUM_BANK_RIGHT, BT_KEY, 255 },
        { 23, 15,145,100, 26, 21, 24, 22,  0,TNUM_BANK_RIGHT, BT_KEY, 255 },
        { 24,158, 49, 83, 26, 23, 26,  1, 25,TNUM_FIRE_PRIMARY, BT_KEY, 255 },
        { 25,158, 49,112, 26, 42, 27, 24,  2,TNUM_FIRE_PRIMARY, BT_KEY, 255 },
	{ 26,158, 57, 83, 26, 24, 28,  3, 27,TNUM_FIRE_SECONDARY, BT_KEY, 255 },
	{ 27,158, 57,112, 26, 25, 29, 26,  4,TNUM_FIRE_SECONDARY, BT_KEY, 255 },
	{ 28,158, 65, 83, 26, 26, 34,  5, 29,TNUM_FIRE_FLARE, BT_KEY, 255 },
	{ 29,158, 65,112, 26, 27, 35, 28,  6,TNUM_FIRE_FLARE, BT_KEY, 255 },
	{ 30,158,105, 83, 26, 44, 32, 13, 31,TNUM_ACCELERATE, BT_KEY, 255 },
	{ 31,158,105,112, 26, 45, 33, 30, 14,TNUM_ACCELERATE, BT_KEY, 255 },
	{ 32,158,113, 83, 26, 30, 38, 15, 33,TNUM_REVERSE, BT_KEY, 255 },
	{ 33,158,113,112, 26, 31, 39, 32, 16,TNUM_REVERSE, BT_KEY, 255 },
	{ 34,158, 73, 83, 26, 28, 36,  7, 35,TNUM_DROP_BOMB, BT_KEY, 255 },
	{ 35,158, 73,112, 26, 29, 37, 34,  8,TNUM_DROP_BOMB, BT_KEY, 255 },
	{ 36,158, 85, 83, 26, 34, 44,  9, 37,TNUM_REAR_VIEW, BT_KEY, 255 },
	{ 37,158, 85,112, 26, 35, 45, 36, 10,TNUM_REAR_VIEW, BT_KEY, 255 },
	{ 38,158,125, 83, 26, 32, 40, 17, 39,TNUM_CRUISE_FASTER, BT_KEY, 255 },
	{ 39,158,125,112, 26, 33, 41, 38, 18,TNUM_CRUISE_FASTER, BT_KEY, 255 },
	{ 40,158,133, 83, 26, 38, 42, 19, 41,TNUM_CRUISE_SLOWER, BT_KEY, 255 },
	{ 41,158,133,112, 26, 39, 43, 40, 20,TNUM_CRUISE_SLOWER, BT_KEY, 255 },
        { 42,158,141, 83, 26, 40, 25, 21, 43,TNUM_CRUISE_OFF, BT_KEY, 255 },
        { 43,158,141,112, 26, 41,  0, 42, 22,TNUM_CRUISE_OFF, BT_KEY, 255 },
	{ 44,158, 93, 83, 26, 36, 30, 11, 45,TNUM_AUTOMAP, BT_KEY, 255 },
	{ 45,158, 93,112, 26, 37, 31, 44, 12,TNUM_AUTOMAP, BT_KEY, 255 },
};
kc_item kc_joystick[NUM_ALL_OTHER_CONTROLS] = {
	{  0, 25, 46, 85, 26, 15,  1, 24,  5,TNUM_FIRE_PRIMARY, BT_JOY_BUTTON, 255 },
	{  1, 25, 54, 85, 26,  0,  4,  5,  6,TNUM_FIRE_SECONDARY, BT_JOY_BUTTON, 255 },
        {  2, 25, 82, 85, 26, 26,  3,  9,  3,TNUM_ACCELERATE, BT_JOY_BUTTON, 255 },
        {  3, 25, 90, 85, 26,  2, 25,  2, 10,TNUM_REVERSE, BT_JOY_BUTTON, 255 },
	{  4, 25, 62, 85, 26,  1, 26,  6,  7,TNUM_FIRE_FLARE, BT_JOY_BUTTON, 255 },
	{  5,180, 46, 59, 26, 23,  6,  0,  1,TNUM_SLIDE_ON, BT_JOY_BUTTON, 255 },
	{  6,180, 54, 59, 26,  5,  7,  1,  4,TNUM_SLIDE_LEFT, BT_JOY_BUTTON, 255 },
	{  7,180, 62, 59, 26,  6,  8,  4, 26,TNUM_SLIDE_RIGHT, BT_JOY_BUTTON, 255 },
	{  8,180, 70, 59, 26,  7,  9, 26,  9,TNUM_SLIDE_UP, BT_JOY_BUTTON, 255 },
	{  9,180, 78, 59, 26,  8, 10,  8,  2,TNUM_SLIDE_DOWN, BT_JOY_BUTTON, 255 },
        { 10,180, 90, 59, 26,  9, 11,  3, 11,TNUM_BANK_ON, BT_JOY_BUTTON, 255 },
        { 11,180, 98, 59, 26, 10, 12, 10, 25,TNUM_BANK_LEFT, BT_JOY_BUTTON, 255 },
        { 12,180,106, 59, 26, 11, 18, 25, 13,TNUM_BANK_RIGHT, BT_JOY_BUTTON, 255 },
        { 13, 22,146, 51, 26, 24, 15, 12, 14,TNUM_PITCH_UD, BT_JOY_AXIS, 255 },
        { 14, 22,146, 99,  8, 25, 16, 13, 17,TNUM_PITCH_UD, BT_INVERT, 255 },
	{ 15, 22,154, 51, 26, 13,  0, 18, 16,TNUM_TURN_LR, BT_JOY_AXIS, 255 },
	{ 16, 22,154, 99,  8, 14, 17, 15, 19,TNUM_TURN_LR, BT_INVERT, 255 },
	{ 17,164,146, 58, 26, 16, 19, 14, 18,TNUM_SLIDE_LR, BT_JOY_AXIS, 255 },
        { 18,164,146,106,  8, 12, 20, 17, 15,TNUM_SLIDE_LR, BT_INVERT, 255 },
	{ 19,164,154, 58, 26, 17, 21, 16, 20,TNUM_SLIDE_UD, BT_JOY_AXIS, 255 },
	{ 20,164,154,106,  8, 18, 22, 19, 21,TNUM_SLIDE_UD, BT_INVERT, 255 },
	{ 21,164,162, 58, 26, 19, 23, 20, 22,TNUM_BANK_LR, BT_JOY_AXIS, 255 },
	{ 22,164,162,106,  8, 20, 24, 21, 23,TNUM_BANK_LR, BT_INVERT, 255 },
	{ 23,164,174, 58, 26, 21,  5, 22, 24,TNUM_THROTTLE, BT_JOY_AXIS, 255 },
	{ 24,164,174,106,  8, 22, 13, 23,  0,TNUM_THROTTLE, BT_INVERT, 255 },
        { 25, 25,102, 85, 26,  3, 14, 11, 12,TNUM_REAR_VIEW, BT_JOY_BUTTON, 255 },
	{ 26, 25, 70, 85, 26,  4,  2,  7,  8,TNUM_DROP_BOMB, BT_JOY_BUTTON, 255 },
};
kc_item kc_mouse[NUM_OTHER_CONTROLS] = {
	{  0, 25, 46, 85, 26, 12,  1, 24,  5,TNUM_FIRE_PRIMARY, BT_MOUSE_BUTTON, 255 },
	{  1, 25, 54, 85, 26,  0,  4,  5,  6,TNUM_FIRE_SECONDARY, BT_MOUSE_BUTTON, 255 },
	{  2, 25, 85, 85, 26, 26,  3,  9, 10,TNUM_ACCELERATE, BT_MOUSE_BUTTON, 255 },
	{  3, 25, 93, 85, 26,  2, 25, 10, 11,TNUM_REVERSE, BT_MOUSE_BUTTON, 255 },
	{  4, 25, 62, 85, 26,  1, 26,  6,  7,TNUM_FIRE_FLARE, BT_MOUSE_BUTTON, 255 },
	{  5,180, 46, 59, 26, 24,  6,  0,  1,TNUM_SLIDE_ON, BT_MOUSE_BUTTON, 255 },
	{  6,180, 54, 59, 26,  5,  7,  1,  4,TNUM_SLIDE_LEFT, BT_MOUSE_BUTTON, 255 },
	{  7,180, 62, 59, 26,  6,  8,  4, 26,TNUM_SLIDE_RIGHT, BT_MOUSE_BUTTON, 255 },
	{  8,180, 70, 59, 26,  7,  9, 26,  9,TNUM_SLIDE_UP, BT_MOUSE_BUTTON, 255 },
	{  9,180, 78, 59, 26,  8, 10,  8,  2,TNUM_SLIDE_DOWN, BT_MOUSE_BUTTON, 255 },
	{ 10,180, 90, 59, 26,  9, 11,  2,  3,TNUM_BANK_ON, BT_MOUSE_BUTTON, 255 },
	{ 11,180, 98, 59, 26, 10, 12,  3, 12,TNUM_BANK_LEFT, BT_MOUSE_BUTTON, 255 },
	{ 12,180,106, 59, 26, 11,  0, 11, 25,TNUM_BANK_RIGHT, BT_MOUSE_BUTTON, 255 },
	{ 13,103,138, 58, 26, 25, 15, 25, 14,TNUM_PITCH_UD, BT_MOUSE_AXIS, 255 },
	{ 14,103,138,106,  8, 23, 16, 13, 15,TNUM_PITCH_UD, BT_INVERT, 255 },
	{ 15,103,146, 58, 26, 13, 17, 14, 16,TNUM_TURN_LR, BT_MOUSE_AXIS, 255 },
	{ 16,103,146,106,  8, 14, 18, 15, 17,TNUM_TURN_LR, BT_INVERT, 255 },
	{ 17,103,154, 58, 26, 15, 19, 16, 18,TNUM_SLIDE_LR, BT_MOUSE_AXIS, 255 },
	{ 18,103,154,106,  8, 16, 20, 17, 19,TNUM_SLIDE_LR, BT_INVERT, 255 },
	{ 19,103,162, 58, 26, 17, 21, 18, 20,TNUM_SLIDE_UD, BT_MOUSE_AXIS, 255 },
	{ 20,103,162,106,  8, 18, 22, 19, 21,TNUM_SLIDE_UD, BT_INVERT, 255 },
	{ 21,103,170, 58, 26, 19, 23, 20, 22,TNUM_BANK_LR, BT_MOUSE_AXIS, 255 },
	{ 22,103,170,106,  8, 20, 24, 21, 23,TNUM_BANK_LR, BT_INVERT, 255 },
	{ 23,103,182, 58, 26, 21, 14, 22, 24,TNUM_THROTTLE, BT_MOUSE_AXIS, 255 },
	{ 24,103,182,106,  8, 22,  5, 23,  0,TNUM_THROTTLE, BT_INVERT, 255 },
	{ 25, 25,109, 85, 26,  3, 13, 12, 13,TNUM_REAR_VIEW, BT_MOUSE_BUTTON, 255 },
	{ 26, 25, 70, 85, 26,  4,  2,  7,  8,TNUM_DROP_BOMB, BT_MOUSE_BUTTON, 255 },
};
//added on 2/4/99 by Victor Rachels to add d1x new keys
kc_item kc_d1x[NUM_D1X_CONTROLS] = {
//        id,x,y,w1,w2,u,d,l,r,text_num1,type,value
        {  0, 15, 49, 71, 26, 27,  2, 27,  1,TNUM_PRIMARY_1, BT_KEY, 255},
        {  1, 15, 49,100, 26, 26,  3,  0,  2,TNUM_PRIMARY_1, BT_JOY_BUTTON, 255},
        {  2, 15, 57, 71, 26,  0,  4,  1,  3,TNUM_PRIMARY_2, BT_KEY, 255},
        {  3, 15, 57,100, 26,  1,  5,  2,  4,TNUM_PRIMARY_2, BT_JOY_BUTTON, 255},
        {  4, 15, 65, 71, 26,  2,  6,  3,  5,TNUM_PRIMARY_3, BT_KEY, 255},
        {  5, 15, 65,100, 26,  3,  7,  4,  6,TNUM_PRIMARY_3, BT_JOY_BUTTON, 255},
        {  6, 15, 73, 71, 26,  4,  8,  5,  7,TNUM_PRIMARY_4, BT_KEY, 255},
        {  7, 15, 73,100, 26,  5,  9,  6,  8,TNUM_PRIMARY_4, BT_JOY_BUTTON, 255},
        {  8, 15, 81, 71, 26,  6, 10,  7,  9,TNUM_PRIMARY_5, BT_KEY, 255},
        {  9, 15, 81,100, 26,  7, 11,  8, 10,TNUM_PRIMARY_5, BT_JOY_BUTTON, 255},

        { 10, 15, 89, 71, 26,  8, 12,  9, 11,TNUM_SECONDARY_1, BT_KEY, 255},
        { 11, 15, 89,100, 26,  9, 13, 10, 12,TNUM_SECONDARY_1, BT_JOY_BUTTON, 255},
        { 12, 15, 97, 71, 26, 10, 14, 11, 13,TNUM_SECONDARY_2, BT_KEY, 255},
        { 13, 15, 97,100, 26, 11, 15, 12, 14,TNUM_SECONDARY_2, BT_JOY_BUTTON, 255},
        { 14, 15,105, 71, 26, 12, 16, 13, 15,TNUM_SECONDARY_3, BT_KEY, 255},
        { 15, 15,105,100, 26, 13, 17, 14, 16,TNUM_SECONDARY_3, BT_JOY_BUTTON, 255},
        { 16, 15,113, 71, 26, 14, 18, 15, 17,TNUM_SECONDARY_4, BT_KEY, 255},
        { 17, 15,113,100, 26, 15, 19, 16, 18,TNUM_SECONDARY_4, BT_JOY_BUTTON, 255},
        { 18, 15,121, 71, 26, 16, 20, 17, 19,TNUM_SECONDARY_5, BT_KEY, 255},
        { 19, 15,121,100, 26, 17, 21, 18, 20,TNUM_SECONDARY_5, BT_JOY_BUTTON, 255},

        { 20, 15,131, 71, 26, 18, 22, 19, 21,TNUM_PRIMARY_CYCLE, BT_KEY, 255},
        { 21, 15,131,100, 26, 19, 23, 20, 22,TNUM_PRIMARY_CYCLE, BT_JOY_BUTTON, 255},
        { 22, 15,139, 71, 26, 20, 24, 21, 23,TNUM_SECONDARY_CYCLE, BT_KEY, 255},
        { 23, 15,139,100, 26, 21, 25, 22, 24,TNUM_SECONDARY_CYCLE, BT_JOY_BUTTON, 255},
        { 24,  8,147, 78, 26, 22, 26, 23, 25,TNUM_CYCLE_P_TOGGLE, BT_KEY, 255},
        { 25,  8,147,107, 26, 23, 27, 24, 26,TNUM_CYCLE_P_TOGGLE, BT_JOY_BUTTON, 255},
        { 26,  8,155, 78, 26, 24,  1, 25, 27,TNUM_CYCLE_S_TOGGLE, BT_KEY, 255},
        { 27,  8,155,107, 26, 25,  0, 26,  0,TNUM_CYCLE_S_TOGGLE, BT_JOY_BUTTON, 255},
};

//end this section addition - VR

void kc_drawitem( kc_item *item, int is_current );
void kc_change_key( kc_item * item );
void kc_change_joybutton( kc_item * item );
void kc_change_mousebutton( kc_item * item );
void kc_next_joyaxis( kc_item * item );  //added by WraithX on 11/22/00
void kc_change_joyaxis( kc_item * item );
void kc_change_mouseaxis( kc_item * item );
void kc_change_invert( kc_item * item );
void kconfig_read_fcs( int raw_axis );
void kconfig_set_fcs_button( int btn, int button );

//the following methods added by WraithX, 4/17/00
int isJoyRotationKey(int test_key)
{
	if (  test_key == kc_joystick[11].value ||
		test_key == kc_joystick[12].value)
	{
		return 1;
	}//end if

	//else...
	return 0;
}//method isJoyRotationKey

int isMouseRotationKey(int test_key)
{
	if (  test_key == kc_mouse[11].value ||
		test_key == kc_mouse[12].value)
	{
		return 1;
	}//end if

	//else...
	return 0;
}//method isMouseRotationKey

int isKeyboardRotationKey(int test_key)
{
	if (  test_key == kc_keyboard[0].value ||
		test_key == kc_keyboard[1].value ||
		test_key == kc_keyboard[2].value ||
		test_key == kc_keyboard[3].value ||
		test_key == kc_keyboard[4].value ||
		test_key == kc_keyboard[5].value ||
		test_key == kc_keyboard[6].value ||
		test_key == kc_keyboard[7].value ||
		test_key == kc_keyboard[20].value ||
		test_key == kc_keyboard[21].value ||
		test_key == kc_keyboard[22].value ||
		test_key == kc_keyboard[23].value)
	{
		return 1;
	}//end if

	//else...
	return 0;
}//method isKeyboardRotationKey
//end addition - WraithX

int kconfig_is_axes_used(int axis)
{
	int i;
	for (i=0; i<NUM_ALL_OTHER_CONTROLS; i++ )   {
		if (( kc_joystick[i].type == BT_JOY_AXIS ) && (kc_joystick[i].value == axis ))
		     return 1;
	}
	return 0;
}

#ifdef TABLE_CREATION
int find_item_at( kc_item * items, int nitems, int x, int y )
{
	int i;
	
	for (i=0; i<nitems; i++ )	{
		if ( ((items[i].x+items[i].w1)==x) && (items[i].y==y))
			return i;
	}
	return -1;
}

int find_next_item_up( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		y--;
		if ( y < 0 ) {
			y = grd_curcanv->cv_bitmap.bm_h-1;
			x--;
			if ( x < 0 ) {
				x = grd_curcanv->cv_bitmap.bm_w-1;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}

int find_next_item_down( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		y++;
		if ( y > grd_curcanv->cv_bitmap.bm_h-1 ) {
			y = 0;
			x++;
			if ( x > grd_curcanv->cv_bitmap.bm_w-1 ) {
				x = 0;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}

int find_next_item_right( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		x++;
		if ( x > grd_curcanv->cv_bitmap.bm_w-1 ) {
			x = 0;
			y++;
			if ( y > grd_curcanv->cv_bitmap.bm_h-1 ) {
				y = 0;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}

int find_next_item_left( kc_item * items, int nitems, int citem )
{
	int x, y, i;

	y = items[citem].y;
	x = items[citem].x+items[citem].w1;
	
	do {	
		x--;
		if ( x < 0 ) {
			x = grd_curcanv->cv_bitmap.bm_w-1;
			y--;
			if ( y < 0 ) {
				y = grd_curcanv->cv_bitmap.bm_h-1;
			}
		}
		i = find_item_at( items, nitems, x, y );
	} while ( i < 0 );
	
	return i;
}
#endif



static float scale=1.0;
void kconfig_sub(kc_item * items,int nitems, char * title)
{
	grs_canvas * save_canvas, canvas;
	grs_font * save_font;
	int old_keyd_repeat;

 int i,k,ocitem,citem;
 int time_stopped = 0;


  All_items = items;
  Num_items = nitems;

#ifdef NETWORK
   if (! ( (Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence) ) )
#else
   if (Endlevel_sequence)
#endif
    {
      time_stopped = 1;
      stop_time();
    }

  save_canvas = grd_curcanv;

  // menu screen scaling, 10/14/99 Jan Bobrowski - scaling for different font sizes 11/18/99 Matt Mueller
		scale=GAME_FONT->ft_h/5.0;//5 is the size of the standard font the menus were designed for.
		printf("scale=%f\n",scale);
		gr_init_sub_canvas(&canvas, &grd_curscreen->sc_canvas, (SWIDTH - 320*scale)/2, (SHEIGHT - 200*scale)/2, 320*scale, 200*scale);
		gr_set_current_canvas(&canvas);
  
  save_font = grd_curcanv->cv_font;
  game_flush_inputs();
  old_keyd_repeat = keyd_repeat;
  keyd_repeat = 1;

  nm_draw_background(0,0,grd_curcanv->cv_bitmap.bm_w-1, grd_curcanv->cv_bitmap.bm_h-1 );//args are x,y,x2,y2 NOT x,y,w,h

  grd_curcanv->cv_font = Gamefonts[GFONT_MEDIUM_3];

    {
     char * p;
      p = strchr( title, '\n' );
       if ( p ) *p = 32;
        gr_string( 0x8000, 8*scale, title );
       if ( p ) *p = '\n';
    }


  grd_curcanv->cv_font = GAME_FONT;
  gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

  gr_string( 0x8000, 28*scale, TXT_KCONFIG_STRING_1 );
  gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
   if ( items == kc_keyboard )
    {
      gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
      gr_setcolor( BM_XRGB(31,27,6) );
        
      gr_scanline( 98*scale, 106*scale, 42*scale );
      gr_scanline( 120*scale, 128*scale, 42*scale );
	  gr_pixel( 98*scale, 43*scale );
      gr_pixel( 98*scale, 44*scale );
      gr_pixel( 128*scale, 43*scale );
      gr_pixel( 128*scale, 44*scale );
       
      gr_string( 109*scale, 40*scale, "OR" );

      gr_scanline( 253*scale, 261*scale, 42*scale );
      gr_scanline( 274*scale, 283*scale, 42*scale );
      gr_pixel( 253*scale, 43*scale );
      gr_pixel( 253*scale, 44*scale );
      gr_pixel( 283*scale, 43*scale );
      gr_pixel( 283*scale, 44*scale );

      gr_string( 264*scale, 40*scale, "OR" );

    }
   else if ( items == kc_joystick )
    {
      gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
      gr_setcolor( BM_XRGB(31,27,6) );
      gr_scanline( 18*scale, 135*scale, 37*scale );
      gr_scanline( 181*scale, 294*scale, 37*scale );
      gr_scanline( 18*scale, 144*scale, (122+10)*scale );        //122 was 119
      gr_scanline( 174*scale, 294*scale, (122+10)*scale );       //122 was 119 
      gr_string( 0x8000, 35*scale, TXT_BUTTONS );
      gr_string( 0x8000,(120+10)*scale, TXT_AXES );  //120 was 117
      gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
      gr_string( 81*scale, 137*scale, TXT_AXIS );
      gr_string( 111*scale, 137*scale, TXT_INVERT );
      gr_string( 222*scale, 137*scale, TXT_AXIS );
      gr_string( 252*scale, 137*scale, TXT_INVERT );
    }
   else if ( items == kc_mouse )
    {
      gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
      gr_setcolor( BM_XRGB(31,27,6) );
      gr_scanline( 18*scale, 135*scale, 37*scale );
      gr_scanline( 181*scale, 294*scale, 37*scale );
      gr_scanline( 18*scale, 144*scale, (119+5)*scale );
      gr_scanline( 174*scale, 294*scale, (119+5)*scale );
      gr_string( 0x8000, 35*scale, TXT_BUTTONS );
      gr_string( 0x8000,(117+5)*scale, TXT_AXES );
      gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
      gr_string( 169*scale, 129*scale, TXT_AXIS );
      gr_string( 199*scale, 129*scale, TXT_INVERT );
    }
   else if ( items == kc_d1x )
    {
      gr_set_fontcolor( BM_XRGB(31,27,6), -1 );
      gr_setcolor( BM_XRGB(31,27,6) );

      gr_string( 94*scale, 40*scale, "KB");
      gr_string(121*scale, 40*scale, "JOY");
    }
	
   for (i=0; i<nitems; i++ )
    kc_drawitem( &items[i], 0 );


  citem = 0;
  kc_drawitem( &items[citem], 1 );

   while(1)
    {
      gr_update();
      k = key_inkey();
       #ifdef NETWORK
       if ( !time_stopped )
        if (multi_menu_poll() == -1)
         k = -2;
       #endif
      ocitem = citem;
       switch( k )
        {
		case KEY_BACKSP:
			Int3();
			break;
		case KEY_PRINT_SCREEN:
			save_screen_shot(0);
			break;							
		case KEY_CTRLED+KEY_D:
			items[citem].value = 255;
			kc_drawitem( &items[citem], 1 );
			break;
		case KEY_CTRLED+KEY_R:	
                         if ( items==kc_keyboard )
                          {
                             for (i=0; i<NUM_ALL_KEY_CONTROLS; i++ )
                              {
                                items[i].value=default_kconfig_settings[0][i];
                                kc_drawitem( &items[i], 0 );
                              }
                          }
                         else if ( items==kc_d1x )
                          {
                             for(i=0;i<NUM_D1X_CONTROLS;i++)
                              {
                                items[i].value=default_kconfig_d1x_settings[i];
                                kc_drawitem( &items[i], 0 );
                              }
                          }
                         else
                          {
                             for (i=0; i<NUM_OTHER_CONTROLS; i++ )
                              {
                                items[i].value = default_kconfig_settings[Config_control_type][i];
                                kc_drawitem( &items[i], 0 );
                              }
                         }
			kc_drawitem( &items[citem], 1 );
			break;
		case KEY_UP: 		
		case KEY_PAD8:
#ifdef TABLE_CREATION
			if (items[citem].u==-1) items[citem].u=find_next_item_up( items,nitems, citem);
#endif
			citem = items[citem].u; 
			break;
		case KEY_DOWN: 	
		case KEY_PAD2:
#ifdef TABLE_CREATION
			if (items[citem].d==-1) items[citem].d=find_next_item_down( items,nitems, citem);
#endif
			citem = items[citem].d; 
			break;
		case KEY_LEFT: 	
		case KEY_PAD4:
#ifdef TABLE_CREATION
			if (items[citem].l==-1) items[citem].l=find_next_item_left( items,nitems, citem);
#endif
			citem = items[citem].l; 
			break;
		case KEY_RIGHT: 	
		case KEY_PAD6:
#ifdef TABLE_CREATION
			if (items[citem].r==-1) items[citem].r=find_next_item_right( items,nitems, citem);
#endif
			citem = items[citem].r; 
			break;
		case KEY_ENTER:	
		case KEY_PADENTER:	
			switch( items[citem].type )	{
                        case BT_KEY:            kc_change_key(         &items[citem] ); break;
                        case BT_MOUSE_BUTTON:   kc_change_mousebutton( &items[citem] ); break;
                        case BT_MOUSE_AXIS:     kc_change_mouseaxis(   &items[citem] ); break;
                        case BT_JOY_BUTTON:     kc_change_joybutton(   &items[citem] ); break;
                        case BT_JOY_AXIS:       kc_change_joyaxis(     &items[citem] ); break;
                        case BT_INVERT:         kc_change_invert(      &items[citem] ); break;
			}
			break;
            //the following case added by WraithX on 11/22/00 to work around the weird joystick bug...
		case KEY_SPACEBAR:
			switch( items[citem].type )	{
				case BT_JOY_AXIS:		kc_next_joyaxis(		&items[citem] ); break;
			}
			break;
		//end addition by WraithX
		case -2:	
		case KEY_ESC:
			grd_curcanv->cv_font	= save_font;
			gr_set_current_canvas( save_canvas );			
			keyd_repeat = old_keyd_repeat;
			game_flush_inputs();
			if (time_stopped)
				start_time();
			return;
#ifdef TABLE_CREATION
                case KEY_F12: { //KEY_DEBUGGED+KEY_F12:      {
			FILE * fp;
                        for (i=0; i<NUM_KEY_CONTROLS; i++ )     {
                                kc_keyboard[i].u = find_next_item_up( kc_keyboard,NUM_ALL_KEY_CONTROLS, i);
                                kc_keyboard[i].d = find_next_item_down( kc_keyboard,NUM_ALL_KEY_CONTROLS, i);
                                kc_keyboard[i].l = find_next_item_left( kc_keyboard,NUM_ALL_KEY_CONTROLS, i);
                                kc_keyboard[i].r = find_next_item_right( kc_keyboard,NUM_ALL_KEY_CONTROLS, i);
			}
                        for (i=0; i<NUM_ALL_OTHER_CONTROLS; i++ )   {
                                kc_joystick[i].u = find_next_item_up( kc_joystick,NUM_ALL_OTHER_CONTROLS, i);
                                kc_joystick[i].d = find_next_item_down( kc_joystick,NUM_ALL_OTHER_CONTROLS, i);
                                kc_joystick[i].l = find_next_item_left( kc_joystick,NUM_ALL_OTHER_CONTROLS, i);
                                kc_joystick[i].r = find_next_item_right( kc_joystick,NUM_ALL_OTHER_CONTROLS, i);
			}
			for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
				kc_mouse[i].u = find_next_item_up( kc_mouse,NUM_OTHER_CONTROLS, i);
				kc_mouse[i].d = find_next_item_down( kc_mouse,NUM_OTHER_CONTROLS, i);
				kc_mouse[i].l = find_next_item_left( kc_mouse,NUM_OTHER_CONTROLS, i);
				kc_mouse[i].r = find_next_item_right( kc_mouse,NUM_OTHER_CONTROLS, i);
			}
			fp = fopen( "kconfig.cod", "wt" );

			fprintf( fp, "ubyte default_kconfig_settings[CONTROL_MAX_TYPES][MAX_CONTROLS] = {\n" );
			for (i=0; i<CONTROL_MAX_TYPES; i++ )	{
				int j;
                                fprintf( fp, "{0x%2x", kconfig_settings[i][0] );
				for (j=1; j<MAX_CONTROLS; j++ )
                                        fprintf( fp, ",0x%2x", kconfig_settings[i][j] );
				fprintf( fp, "},\n" );
			}
			fprintf( fp, "};\n" );
		
                        fprintf( fp, "\nkc_item kc_keyboard[NUM_ALL_KEY_CONTROLS] = {\n" );
                        for (i=0; i<(NUM_ALL_KEY_CONTROLS); i++ )     {
				fprintf( fp, "\t{ %2d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%c%s%c, %s, 255 },\n", 
					kc_keyboard[i].id, kc_keyboard[i].x, kc_keyboard[i].y, kc_keyboard[i].w1, kc_keyboard[i].w2,
					kc_keyboard[i].u, kc_keyboard[i].d, kc_keyboard[i].l, kc_keyboard[i].r,
					34, Text_string[kc_keyboard[i].text_num1], 34, btype_text[kc_keyboard[i].type] );
			}
			fprintf( fp, "};" );

                        fprintf( fp, "\nkc_item kc_joystick[NUM_ALL_OTHER_CONTROLS] = {\n" );
                        for (i=0; i<NUM_ALL_OTHER_CONTROLS; i++ )   {
				fprintf( fp, "\t{ %2d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%c%s%c, %s, 255 },\n", 
					kc_joystick[i].id, kc_joystick[i].x, kc_joystick[i].y, kc_joystick[i].w1, kc_joystick[i].w2,
					kc_joystick[i].u, kc_joystick[i].d, kc_joystick[i].l, kc_joystick[i].r,
					34, Text_string[kc_joystick[i].text_num1], 34, btype_text[kc_joystick[i].type] );
			}
			fprintf( fp, "};" );

			fprintf( fp, "\nkc_item kc_mouse[NUM_OTHER_CONTROLS] = {\n" );
			for (i=0; i<NUM_OTHER_CONTROLS; i++ )	{
				fprintf( fp, "\t{ %2d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%3d,%c%s%c, %s, 255 },\n", 
					kc_mouse[i].id, kc_mouse[i].x, kc_mouse[i].y, kc_mouse[i].w1, kc_mouse[i].w2,
					kc_mouse[i].u, kc_mouse[i].d, kc_mouse[i].l, kc_mouse[i].r,
					34, Text_string[kc_mouse[i].text_num1], 34, btype_text[kc_mouse[i].type] );
			}
			fprintf( fp, "};" );

			fclose(fp);

			}
			break;
#endif
        }
       if (ocitem!=citem)
        {
          kc_drawitem( &items[ocitem], 0 );
          kc_drawitem( &items[citem], 1 );
        }
    }
}


void kc_drawitem( kc_item *item, int is_current )
{
	int x, w, h, aw;
	char btext[10];

	if (is_current)
		gr_set_fontcolor( BM_XRGB(20,20,29), -1 );
	else
		gr_set_fontcolor( BM_XRGB(15,15,24), -1 );


         if((item->text_num1) < N_TEXT_STRINGS)
          gr_string( item->x*scale, item->y*scale, Text_string[item->text_num1] );
         else
          {
            switch(item->text_num1-N_TEXT_STRINGS)
             {
             case 0:  gr_string( item->x*scale, item->y*scale,"CYC PRIMARY"); break;
             case 1:  gr_string( item->x*scale, item->y*scale,"CYC SECONDARY"); break;
             case 2:  gr_string( item->x*scale, item->y*scale,"TOGGLE PRIM AUTO"); break;
             case 3:  gr_string( item->x*scale, item->y*scale,"TOGGLE SEC AUTO"); break;
             case 4:  gr_string( item->x*scale, item->y*scale,"WEAPON 1"); break;
             case 5:  gr_string( item->x*scale, item->y*scale,"WEAPON 2"); break;
             case 6:  gr_string( item->x*scale, item->y*scale,"WEAPON 3"); break;
             case 7:  gr_string( item->x*scale, item->y*scale,"WEAPON 4"); break;
             case 8:  gr_string( item->x*scale, item->y*scale,"WEAPON 5"); break;
             case 9:  gr_string( item->x*scale, item->y*scale,"WEAPON 6"); break;
             case 10: gr_string( item->x*scale, item->y*scale,"WEAPON 7"); break;
             case 11: gr_string( item->x*scale, item->y*scale,"WEAPON 8"); break;
             case 12: gr_string( item->x*scale, item->y*scale,"WEAPON 9"); break;
             case 13: gr_string( item->x*scale, item->y*scale,"WEAPON 0"); break;
             }
          }

	if (item->value==255) {
		strcpy( btext, "" );
	} else {
		switch( item->type )	{
			case BT_KEY:
				strncpy( btext, key_text[item->value], 10 ); break;
			case BT_MOUSE_BUTTON:
				strncpy( btext, item->value<=3?Text_string[mousebutton_text[item->value]]:mousebutton_textra[item->value-3], 10 ); break;
			case BT_MOUSE_AXIS:
				strncpy( btext, Text_string[mouseaxis_text[item->value]], 10 ); break;
			case BT_JOY_BUTTON:
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
				sprintf( btext, "J%d B%d", j_button[item->value].joydev, j_Get_joydev_button_number (item->value) );
#else
				if ( joybutton_text[item->value] !=-1 )
					strncpy( btext, Text_string[ joybutton_text[item->value]  ], 10 );
				else
					sprintf( btext, "BTN%d", item->value );
#endif
				break;
			case BT_JOY_AXIS:
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
				sprintf( btext, "J%d A%d", j_axis[item->value].joydev, j_Get_joydev_axis_number (item->value) );
#else
				strncpy( btext, Text_string[joyaxis_text[item->value]], 10 );
#endif
				break;
			case BT_INVERT:
				strncpy( btext, Text_string[invert_text[item->value]], 10 ); break;
		}
	}
	gr_get_string_size(btext, &w, &h, &aw  );

	if (is_current)
		gr_setcolor( BM_XRGB(21,0,24) );
	else
		gr_setcolor( BM_XRGB(16,0,19) );
	gr_urect( (item->w1+item->x)*scale, item->y*scale-1, (item->w1+item->x+item->w2)*scale, item->y*scale+h );
	
	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

	x = (item->w1+item->x)*scale+((item->w2*scale-w)/2);

	gr_string( x, item->y*scale, btext );
}


static int looper=0;

void kc_drawquestion( kc_item *item )
{
	int c, x, w, h, aw;
	
	gr_get_string_size("?", &w, &h, &aw  );

	c = BM_XRGB(21,0,24);

	gr_setcolor( gr_fade_table[fades[looper]*256+c] );
	looper++;
	if (looper>63) looper=0;

	gr_urect( (item->w1+item->x)*scale, item->y*scale-1, (item->w1+item->x+item->w2)*scale, item->y*scale+h );
	
	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );

	x = (item->w1+item->x)*scale+((item->w2*scale-w)/2);

	gr_string( x, item->y*scale, "?" );

        gr_update();
}

void kc_change_key( kc_item * item )
{
	int i,n,f,k;
	ubyte keycode;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_PRESS_NEW_KEY );
	
	game_flush_inputs();
	keycode=255;
	k=255;
	while( (k!=KEY_ESC) && (keycode==255) )	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
//added/changed on 9/2/98 by Matt Mueller
                d_delay(10);
//end change -MM
		kc_drawquestion( item );
	
		for (i=0; i<256; i++ )	{
			if (keyd_pressed[i] && (strlen(key_text[i])>0))	{
				f = 0;
				for (n=0; n<sizeof(system_keys); n++ )
					if ( system_keys[n] == i )
						f=1;
				if (!f)	
					keycode=i;
			}
		}
	}

	if (k!=KEY_ESC)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_KEY) && (All_items[i].value==keycode) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = keycode;
	}
	kc_drawitem( item, 1 );
	gr_set_fontcolor( BM_XRGB(28,28,28), BM_XRGB(0,0,0) );

	nm_restore_background( 0, INFO_Y, GWIDTH-10, grd_curcanv->cv_font->ft_h );

	game_flush_inputs();

}

void kc_change_joybutton( kc_item * item )
{
	int n,i,k;
	ubyte code;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_PRESS_NEW_JBUTTON );
	
	game_flush_inputs();
	code=255;
	k=255;
        while( (k!=KEY_ESC) && (code==255))     {
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
//added/changed on 9/2/98 by Matt Mueller
                d_delay(10);
//end change -MM

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

//added/changed 9/6/98 Matt Mueller + 9/19/98 Owen Evans-> #endif
#ifdef __LINUX__
		for (i = 0; i < j_num_buttons; i++) {
#else
		if (Config_control_type==CONTROL_THRUSTMASTER_FCS)	{

			int axis[JOY_NUM_AXES];
			joystick_read_raw_axis( JOY_ALL_AXIS, axis );
			kconfig_read_fcs( axis[3] );
			if ( joy_get_button_state(7) ) code = 7;
			if ( joy_get_button_state(11) ) code = 11;
			if ( joy_get_button_state(15) ) code = 15;
			if ( joy_get_button_state(19) ) code = 19;
			for (i=0; i<4; i++ )	{
#endif
				if ( joy_get_button_state(i) )
					code = i;
			}
//added/changed 9/6/98 Matt Mueller -> #endif
#ifndef __LINUX__
		} else if (Config_control_type==CONTROL_FLIGHTSTICK_PRO) {
			for (i=4; i<20; i++ )	{
				if ( joy_get_button_state(i)  )	{
					code = i;
					mprintf(( 0, "JB: %d\n", code ));
				}
			}
		} else {
//added/changed 3/7/99 Owen Evans (next line)
                        for (i=0; i<MAX_BUTTONS; i++ )    {
				if ( joy_get_button_state(i) )
					code = i;
			}
		}
#endif
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_JOY_BUTTON) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = code;
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, GWIDTH-10, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();
}

void kc_change_mousebutton( kc_item * item )
{
	int n,i,b,k;
	ubyte code;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_PRESS_NEW_MBUTTON );
	
	game_flush_inputs();
	code=255;
	k=255;
	while( (k!=KEY_ESC) && (code==255))	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
//added/changed on 9/2/98 by Matt Mueller
                d_delay(10);
//end change -MM

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		b = mouse_get_btns();
		for (i=0; i<16; i++ )	{
			if ( b & (1<<i) )	
				code = i;
		}
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_MOUSE_BUTTON) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = code;
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, GWIDTH-10, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}


//the following function added by WraithX on 11/22/00 to work around the weird joystick bug... - modified my Matt Mueller to skip already allocated axes
void kc_next_joyaxis( kc_item * item )
{
	int n,i,k,max,tries;
	ubyte code = 0;
	k = 255;
	n = 0;
	i = 0;

	//I modelled this ifdef after the code in the kc_change_joyaxis method.
	//So, if somethin's not workin here, it might not be workin there either.
	#ifdef __LINUX__
		max = 32;
	#else
		max = JOY_NUM_AXES;
	#endif
	tries = 1;
	code = (item->value + 1)%max;

	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_JOY_AXIS) && (All_items[i].value==code) )		{
				if (tries>max) return; //all axes allocated already
				i=-1;   //-1 so the i++ will push back to 0
				code = (item->value + ++tries)%max; //try next axis
			}//end if
		}//end for

		item->value = code;
	}//end if

	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, GWIDTH-10, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}//method kc_next_joyaxis
//end addition by WraithX


void kc_change_joyaxis( kc_item * item )
{
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
	int axis[32];
	int old_axis[32];
#else
//added/changed 3/7/99 Owen Evans -> #endif
	int axis[JOY_NUM_AXES];
	int old_axis[JOY_NUM_AXES];
//        int temp_min[JOY_NUM_AXES];
//        int temp_center[JOY_NUM_AXES];
//        int temp_max[JOY_NUM_AXES];
#endif
	int n,i,k;
	ubyte code;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_MOVE_NEW_JOY_AXIS );
	
	game_flush_inputs();
	code=255;
	k=255;

	joystick_read_raw_axis( JOY_ALL_AXIS, old_axis );

        while( (k!=KEY_ESC) && (code==255))     {
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
//added/changed on 9/2/98 by Matt Mueller
                d_delay(10);
//end change -MM

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		joystick_read_raw_axis( JOY_ALL_AXIS, axis );
		
//added/changed 9/6/98 Matt Mueller + 9/19/98 Owen Evans -> #endif
#ifdef __LINUX__
		for (i = 0; i < j_num_axes; i++)
                 {
                    if (abs (axis[i] - old_axis[i]) > ((j_axis[i].max_val - j_axis[i].min_val) / 32))
                     {
#else
//added/changed 3/17/99 Owen Evans
//added/edited on 9/6/99 by Victor Rachels for better config
//-unneeded-           joy_get_cal_vals(temp_min, temp_center, temp_max);
                for (i=0; i<JOY_NUM_AXES; i++ )
                 {
                   axis[i] = joy_get_scaled_reading(axis[i],i);
                    if(axis[i])    //-was- if (abs(axis[i] - old_axis[i]) > ((temp_max[i] - temp_min[i]) / 32))
//end this section addition/edit - VR
                     {
#endif
                       code = i;
                     }
                   old_axis[i] = axis[i];
                 }
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_JOY_AXIS) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}

		item->value = code;					 
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, GWIDTH-10, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}

void kc_change_mouseaxis( kc_item * item )
{
	int i,n,k;
	ubyte code;
	int dx,dy;

	gr_set_fontcolor( BM_XRGB(28,28,28), -1 );
	
	gr_string( 0x8000, INFO_Y, TXT_MOVE_NEW_MSE_AXIS );
	
	game_flush_inputs();
	code=255;
	k=255;

	mouse_get_delta( &dx, &dy );

	while( (k!=KEY_ESC) && (code==255))	{				
		#ifdef NETWORK
		if ((Game_mode & GM_MULTI) && (Function_mode == FMODE_GAME) && (!Endlevel_sequence))
			multi_menu_poll();
		#endif
//		if ( Game_mode & GM_MULTI )
//			GameLoop( 0, 0 );				// Continue
		k = key_inkey();
//added/changed on 9/2/98 by Matt Mueller
                d_delay(10);
//end change -MM

		if (k == KEY_PRINT_SCREEN)
			save_screen_shot(0);

		kc_drawquestion( item );

		mouse_get_delta( &dx, &dy );
		if ( abs(dx)>20 ) code = 0;
		if ( abs(dy)>20 )	code = 1;
	}
	if (code!=255)	{
		for (i=0; i<Num_items; i++ )	{
			n = item - All_items;
			if ( (i!=n) && (All_items[i].type==BT_MOUSE_AXIS) && (All_items[i].value==code) )		{
				All_items[i].value = 255;
				kc_drawitem( &All_items[i], 0 );
			}
		}
		item->value = code;
	}
	kc_drawitem( item, 1 );
	nm_restore_background( 0, INFO_Y, GWIDTH-10, grd_curcanv->cv_font->ft_h );
	game_flush_inputs();

}


void kc_change_invert( kc_item * item )
{
	game_flush_inputs();

	if (item->value)
		item->value = 0;
	else 
		item->value = 1;

	kc_drawitem( item, 1 );

}

#include "screens.h"

void kconfig(int n, char * title)
{
 int i;

  set_screen_mode( SCREEN_MENU );

  kc_set_controls();

   switch(n)
    {
     case 0:kconfig_sub( kc_keyboard,NUM_ALL_KEY_CONTROLS,  title); break;
     case 1:kconfig_sub( kc_joystick,NUM_ALL_OTHER_CONTROLS,title); break;
     case 2:kconfig_sub( kc_mouse,   NUM_OTHER_CONTROLS,    title); break;
     //added on 2/4/99 by Victor Rachels for new keys menu
     case 3:kconfig_sub( kc_d1x,     NUM_D1X_CONTROLS,      title); break;
     //end this section addition - VR
     default:
		Int3();
		return;
    }

  reset_cockpit();                //force cockpit redraw next time

  // Update save values...
	
   for (i=0; i<NUM_ALL_KEY_CONTROLS; i++ ) 
    kconfig_settings[0][i] = kc_keyboard[i].value;

   if ( (Config_control_type>0) && (Config_control_type<5))
    {
       for (i=0; i<NUM_ALL_OTHER_CONTROLS; i++ ) 
         kconfig_settings[Config_control_type][i] = kc_joystick[i].value;
    }
   else if (Config_control_type>4)
    {
       for (i=0; i<NUM_OTHER_CONTROLS; i++ ) 
        kconfig_settings[Config_control_type][i] = kc_mouse[i].value;
    }

   for (i=0; i<NUM_D1X_CONTROLS; i++)
    kconfig_d1x_settings[i] = kc_d1x[i].value;
}

//added/changed 9/6/98 Matt Mueller -> #endif
#ifndef __LINUX__
void kconfig_read_fcs( int raw_axis )
{
	int raw_button, button, axis_min[JOY_NUM_AXES], axis_center[JOY_NUM_AXES], axis_max[JOY_NUM_AXES];

	if (Config_control_type!=CONTROL_THRUSTMASTER_FCS) return;

	joy_get_cal_vals(axis_min, axis_center, axis_max);

	if ( axis_max[3] > 1 )
		raw_button = (raw_axis*100)/axis_max[3];
	else
		raw_button = 0;

	if ( raw_button > 88 )
		button = 0;
	else if ( raw_button > 63 )
		button = 7;
	else if ( raw_button > 39 )
		button = 11;
	else if ( raw_button > 15 )
		button = 15;
	else	
		button = 19;

	kconfig_set_fcs_button( 19, button );
	kconfig_set_fcs_button( 15, button );
	kconfig_set_fcs_button( 11, button );
	kconfig_set_fcs_button( 7, button );
}
		

void kconfig_set_fcs_button( int btn, int button )
{
	int state,time_down,upcount,downcount;
	state = time_down = upcount = downcount = 0;

	if ( joy_get_button_state(btn) ) {
		if ( btn==button )	{
			state = 1;
			time_down = FrameTime;
		} else {
			upcount=1;
		}
	} else {
		if ( btn==button )	{
			state = 1;
			time_down = FrameTime;
			downcount=1;
		} else {
			upcount=1;
		}
	}				
			
	joy_set_btn_values( btn, state, time_down, downcount, upcount );
					
}
#endif

#define	PH_SCALE	8
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
#define	JOYSTICK_READ_TIME	(F1_0/20)		//	Read joystick at 20 Hz.
#else
#define	JOYSTICK_READ_TIME	(F1_0/10)		//	Read joystick at 10 Hz.
#endif
fix	LastReadTime = 0;

//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
fix	joy_axis[32];
#else
fix	joy_axis[JOY_NUM_AXES];
#endif
		
ubyte 			kc_use_external_control = 0;
ubyte				kc_enable_external_control = 1;
ubyte 			kc_external_intno = 0;
control_info	*kc_external_control = NULL;
//added on 8/8/98 by Matt Mueller - sporb support
#ifdef __DJGPP__
unsigned long  kc_external_control_addr=0;
#endif
//end modified section - Matt Mueller
ubyte				*kc_external_name = NULL;
ubyte				kc_external_version = 0;

void kconfig_init_external_controls(int intno, ssize_t address)
{
	int i;
	kc_external_intno = intno;
//added/changed on 8/8/98 by Matt Mueller - sporb support
#ifdef __DJGPP__
        MALLOC(kc_external_control,control_info,1);
        kc_external_control_addr=address;
#else
	kc_external_control	= (control_info *)address;
#endif
//end modified section
	kc_use_external_control = 1;
	kc_enable_external_control  = 1;

	i = FindArg( "-xname" );
	if ( i )	
		kc_external_name = Args[i+1];
	else
		kc_external_name = "External Controller";

	i = FindArg( "-xver" );
	if ( i )
		kc_external_version = atoi(Args[i+1]);
	
	printf( "%s int: 0x%x, data: 0x%p, ver:%d\n", kc_external_name, kc_external_intno, kc_external_control, kc_external_version );

}

#ifdef __MSDOS__
void kconfig_read_external_controls()
{
	union REGS r;

	if ( !kc_enable_external_control ) return;

	if ( kc_external_version == 0 ) 
		memset( kc_external_control, 0, sizeof(control_info) );
	else if ( kc_external_version > 0 ) 	{
		memset( kc_external_control, 0, sizeof(control_info)+sizeof(vms_angvec) + 64 );
		if ( kc_external_version > 1 ) {
			// Write ship pos and angles to external controls...
			ubyte *temp_ptr = (ubyte *)kc_external_control;
			vms_vector *ship_pos;
			vms_matrix *ship_orient;
			memset( kc_external_control, 0, sizeof(control_info)+sizeof(vms_angvec) + 64 + sizeof(vms_vector)+sizeof(vms_matrix) );
			temp_ptr += sizeof(control_info)+sizeof(vms_angvec) + 64;
			ship_pos = (vms_vector *)temp_ptr;
			temp_ptr += sizeof(vms_vector);
			ship_orient = (vms_matrix *)temp_ptr;
			// Fill in ship postion...
			*ship_pos = Objects[Players[Player_num].objnum].pos;
			// Fill in ship orientation...
			*ship_orient = Objects[Players[Player_num].objnum].orient;
		}
	}

	if ( grd_curscreen->sc_mode != SM(320,200) )			// (If in automap...)
		kc_external_control->automap_state = 1;

//added on 8/8/98 by Matt Mueller - sporb support
#ifdef __DJGPP__
        dosmemput(kc_external_control,sizeof(control_info),kc_external_control_addr);
#endif
//end modified section - Matt Mueller

	memset(&r,0,sizeof(r));
	int386 ( kc_external_intno, &r, &r);		// Read external info...

//added on 8/8/98 by Matt Mueller - sporb support
#ifdef __DJGPP__
        dosmemget(kc_external_control_addr,sizeof(control_info),kc_external_control);
#endif
//end modified section - Matt Mueller
	if ( Player_num > -1 )	{
		Objects[Players[Player_num].objnum].mtype.phys_info.flags &= (~PF_TURNROLL);	// Turn off roll when turning
		Objects[Players[Player_num].objnum].mtype.phys_info.flags &= (~PF_LEVELLING);	// Turn off leveling to nearest side.
		Auto_leveling_on = 0;

		if ( kc_external_version > 0 ) {		
			vms_matrix tempm, ViewMatrix;
			vms_angvec * Kconfig_abs_movement;
			char * oem_message;
	
			Kconfig_abs_movement = (vms_angvec *)((uint)kc_external_control + sizeof(control_info));
	
			if ( Kconfig_abs_movement->p || Kconfig_abs_movement->b || Kconfig_abs_movement->h )	{
				vm_angles_2_matrix(&tempm,Kconfig_abs_movement);
				vm_matrix_x_matrix(&ViewMatrix,&Objects[Players[Player_num].objnum].orient,&tempm);
				Objects[Players[Player_num].objnum].orient = ViewMatrix;		
			}
			oem_message = (char *)((uint)Kconfig_abs_movement + sizeof(vms_angvec));
			if (oem_message[0] != '\0' )
                                hud_message(MSGC_GAME_FEEDBACK, oem_message );
		}
	}


        //added/changed on 3/12/99 by Victor Rachels for faster sporb
         if(extfaster)
          {
            externalctrlp = fixmul(kc_external_control->pitch_time,FrameTime);
            externalctrlh = fixmul(kc_external_control->heading_time,FrameTime);
            externalctrlb = fixmul(kc_external_control->bank_time,FrameTime);
          }
         else
          {
            Controls.pitch_time += fixmul(kc_external_control->pitch_time,FrameTime);
            Controls.bank_time += fixmul(kc_external_control->bank_time ,FrameTime);
            Controls.heading_time += fixmul(kc_external_control->heading_time,FrameTime);
          }
//^        Controls.pitch_time += fixmul(kc_external_control->pitch_time,FrameTime);
	Controls.vertical_thrust_time += fixmul(kc_external_control->vertical_thrust_time,FrameTime);
//^        Controls.heading_time += fixmul(kc_external_control->heading_time,FrameTime);
	Controls.sideways_thrust_time += fixmul(kc_external_control->sideways_thrust_time ,FrameTime);
//^        Controls.bank_time += fixmul(kc_external_control->bank_time ,FrameTime);
      //end this section addition/change - VR

	Controls.forward_thrust_time += fixmul(kc_external_control->forward_thrust_time ,FrameTime);
	Controls.rear_view_down_count += kc_external_control->rear_view_down_count;
	Controls.rear_view_down_state |= kc_external_control->rear_view_down_state;	
	Controls.fire_primary_down_count += kc_external_control->fire_primary_down_count;
	Controls.fire_primary_state |= kc_external_control->fire_primary_state;
	Controls.fire_secondary_state |= kc_external_control->fire_secondary_state;
	Controls.fire_secondary_down_count += kc_external_control->fire_secondary_down_count;
	Controls.fire_flare_down_count += kc_external_control->fire_flare_down_count;
	Controls.drop_bomb_down_count += kc_external_control->drop_bomb_down_count;	
	Controls.automap_down_count += kc_external_control->automap_down_count;
	Controls.automap_state |= kc_external_control->automap_state;
}
#else
void kconfig_read_external_controls() {}
#endif

//added/edited on 11/01/98 by Victor Rachels for primary/secondary
//added on 9/15/98 by Victor Rachels to finagle the weapon toggle stuff
int Allow_primary_cycle_ostate = 0;
int Allow_secondary_cycle_ostate = 0;
//end addition
//end this section edit - Victor Rachels
//added on 2/7/99 by Victor Rachels for jostick state setting
int d1x_joystick_ostate[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//end this section adition - VR
//added on 4/16/99 by Victor Rachels for vulcantoggle
int Vulcan_kostate = 0;
int Vulcan_jostate = 0;
int Vulcan_mostate = 0;
//end addition - VR

void controls_read_all()
{
	int i;
	int slide_on, bank_on;
	int dx, dy;
	int idx, idy;
	fix ctime;
	fix mouse_axis[2];
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
	int raw_joy_axis[32];
#else
	int raw_joy_axis[JOY_NUM_AXES];
#endif
	int mouse_buttons;
	fix k0, k1, k2, k3, kp;
	fix k4, k5, k6, k7, kh;
	ubyte channel_masks;
	int use_mouse, use_joystick;
	int speed_factor=1;

	if (Game_turbo_mode)
		speed_factor = 2;
	
	{
		fix temp = Controls.heading_time;
		fix temp1 = Controls.pitch_time;
		memset( &Controls, 0, sizeof(control_info) );
		Controls.heading_time = temp;
		Controls.pitch_time = temp1;
	}
	slide_on = 0;
	bank_on = 0;

	ctime = timer_get_fixed_seconds();

	//---------  Read Joystick -----------
	if ( (LastReadTime + JOYSTICK_READ_TIME > ctime) && (Config_control_type!=CONTROL_THRUSTMASTER_FCS) ) {
//added/changed 9/6/98 Matt Mueller -> #endif
#if defined(__LINUX__) || defined(__WINDOWS__)
		if ((ctime < 0) && (LastReadTime >= 0))
#else
		if ((ctime < 0) && (LastReadTime > 0))
#endif
			LastReadTime = ctime;
		use_joystick=1;
	} else if ((Config_control_type>0) && (Config_control_type<5) ) {
		LastReadTime = ctime;
		channel_masks = joystick_read_raw_axis( JOY_ALL_AXIS, raw_joy_axis );
		
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
		for (i=0; i < j_num_axes; i++ )  {
#else
//added/changed 3/7/99 Owen Evans (next line)
                for (i=0; i<JOY_NUM_AXES; i++ )    {
			if (channel_masks&(1<<i))	{
#endif
				int joy_null_value = 10;

//added/changed 9/6/98 Matt Mueller -> #endif
#ifndef __LINUX__
				if ( (i==3) && (Config_control_type==CONTROL_THRUSTMASTER_FCS) )	{
					kconfig_read_fcs( raw_joy_axis[i] );
				} else {
#endif
					raw_joy_axis[i] = joy_get_scaled_reading( raw_joy_axis[i], i );
	
					if (kc_joystick[23].value==i)		// If this is the throttle
						joy_null_value = 20;				// Then use a larger dead-zone
	
					if (raw_joy_axis[i] > joy_null_value) 
						raw_joy_axis[i] = ((raw_joy_axis[i]-joy_null_value)*128)/(128-joy_null_value);
				  	else if (raw_joy_axis[i] < -joy_null_value)
						raw_joy_axis[i] = ((raw_joy_axis[i]+joy_null_value)*128)/(128-joy_null_value);
					else
						raw_joy_axis[i] = 0;
					joy_axis[i]	= (raw_joy_axis[i]*FrameTime)/128;	
				}
//added/changed 9/6/98 Matt Mueller -> #endif
#ifndef __LINUX__
			} else {
				joy_axis[i] = 0;
			}
		}
#endif
		use_joystick=1;
	} else {
//added/changed 9/6/98 Matt Mueller -> #endif
#ifdef __LINUX__
		for (i=0; i<j_num_axes; i++ )
#else
                for (i=0; i<JOY_NUM_AXES; i++ )
#endif
			joy_axis[i] = 0;
		use_joystick=0;
	}

	if (Config_control_type==5 ) {
		//---------  Read Mouse -----------
		mouse_get_delta( &dx, &dy );
		mouse_axis[0] = (dx*FrameTime)/35;
		mouse_axis[1] = (dy*FrameTime)/25;
		mouse_buttons = mouse_get_btns();
		//mprintf(( 0, "Mouse %d,%d b:%d, 0x%x\n", mouse_axis[0], mouse_axis[1], mouse_buttons, FrameTime ));
		use_mouse=1;
	} else if (Config_control_type==6 ) {
		//---------  Read Cyberman -----------
		mouse_get_cyberman_pos(&idx,&idy );
		mouse_axis[0] = (idx*FrameTime)/128;
		mouse_axis[1] = (idy*FrameTime)/128;
		mouse_buttons = mouse_get_btns();
		use_mouse=1;
	} else {
		mouse_axis[0] = 0;
		mouse_axis[1] = 0;
		mouse_buttons = 0;
		use_mouse=0;
	}

//added on 2/4/99 by Victor Rachels for d1x keys
//--------- Read primary weapon select -------------
//the following "if" added by WraithX to stop deadies from switchin weapons, 4/14/00
if (!Player_is_dead)
{
 {
  int d1x_joystick_state[10];

    for(i=0;i<10;i++)
     d1x_joystick_state[i] = joy_get_button_state(kc_d1x[i*2+1].value);


  //----------------Weapon 1----------------
    if(key_down_count(kc_d1x[0].value) ||
       (joy_get_button_state(kc_d1x[1].value) &&
        (d1x_joystick_state[0]!=d1x_joystick_ostate[0]) ) )
     {
      int i, valu=0;
       do_weapon_select(0,0);
        for(i=MAX_PRIMARY_WEAPONS;i<MAX_PRIMARY_WEAPONS+NEWPRIMS;i++)
         if(primary_order[i]>primary_order[valu]&&player_has_weapon(i,0))
          valu = i;
       LaserPowSelected = valu;
     }
   //----------------Weapon 2----------------
    if(key_down_count(kc_d1x[2].value) ||
       (joy_get_button_state(kc_d1x[3].value) &&
        (d1x_joystick_state[1]!=d1x_joystick_ostate[1]) ) )
     do_weapon_select(1,0);
   //----------------Weapon 3----------------
    if(key_down_count(kc_d1x[4].value) ||
       (joy_get_button_state(kc_d1x[5].value) &&
        (d1x_joystick_state[2]!=d1x_joystick_ostate[2]) ) )
     do_weapon_select(2,0);
   //----------------Weapon 4----------------
    if(key_down_count(kc_d1x[6].value) ||
       (joy_get_button_state(kc_d1x[7].value) &&
        (d1x_joystick_state[3]!=d1x_joystick_ostate[3]) ) )
     do_weapon_select(3,0);
   //----------------Weapon 5----------------
    if(key_down_count(kc_d1x[8].value) ||
       (joy_get_button_state(kc_d1x[9].value) &&
        (d1x_joystick_state[4]!=d1x_joystick_ostate[4]) ) )
     do_weapon_select(4,0);
 
 //--------- Read secondary weapon select ----------
   //----------------Weapon 6----------------
    if(key_down_count(kc_d1x[10].value) ||
       (joy_get_button_state(kc_d1x[11].value) &&
        (d1x_joystick_state[5]!=d1x_joystick_ostate[5]) ) )
     do_weapon_select(0,1);
   //----------------Weapon 7----------------
    if(key_down_count(kc_d1x[12].value) ||
       (joy_get_button_state(kc_d1x[13].value) &&
        (d1x_joystick_state[6]!=d1x_joystick_ostate[6]) ) )
     do_weapon_select(1,1);
   //----------------Weapon 8----------------
    if(key_down_count(kc_d1x[14].value) ||
       (joy_get_button_state(kc_d1x[15].value) &&
        (d1x_joystick_state[7]!=d1x_joystick_ostate[7]) ) )
    do_weapon_select(2,1);
   //----------------Weapon 9----------------
    if(key_down_count(kc_d1x[16].value) ||
       (joy_get_button_state(kc_d1x[17].value) &&
        (d1x_joystick_state[8]!=d1x_joystick_ostate[8]) ) )
     do_weapon_select(3,1);
   //----------------Weapon 0----------------
    if(key_down_count(kc_d1x[18].value) ||
       (joy_get_button_state(kc_d1x[19].value) &&
        (d1x_joystick_state[9]!=d1x_joystick_ostate[9]) ) )
     do_weapon_select(4,1);
   memcpy(d1x_joystick_ostate,d1x_joystick_state,10*sizeof(int));
 }
//end this section addition - VR

//added/edited on 11/01/98 by Victor Rachels for primary/secondary
//added on 9/15/98 by Victor Rachels to add weapon cycle toggle
        //from keybaord
      {
       int Allow_primary_cycle_count=0;
       int Allow_primary_cycle_jstate=0;

//added/killed on 2/4/99 by Victor Rachels for d1x keys
         if ( kc_d1x[24].value < 255 ) Allow_primary_cycle_count += key_down_count(kc_d1x[24].value);
         if ( (use_joystick)&&(kc_d1x[25].value < 255) ) Allow_primary_cycle_jstate= joy_get_button_state( kc_d1x[25].value );

//-killed-         if ( kc_keyboard[50].value < 255 ) Allow_primary_cycle_count += key_down_count(kc_keyboard[50].value);
//-killed-         if ( kc_keyboard[51].value < 255 ) Allow_primary_cycle_count += key_down_count(kc_keyboard[51].value);
//-killed-         if ( (use_joystick)&&(kc_joystick[29].value < 255) ) Allow_primary_cycle_jstate= joy_get_button_state( kc_joystick[29].value );
//end this section change - VR

         if (Allow_primary_cycle_count || Allow_primary_cycle_jstate!=Allow_primary_cycle_ostate)
          {
           if((Allow_primary_cycle_jstate!=Allow_primary_cycle_ostate)&&(Allow_primary_cycle_jstate==0))
            Allow_primary_cycle_ostate = Allow_primary_cycle_jstate;
           else
            {
             Allow_primary_cycle = !Allow_primary_cycle;
              if(!Allow_primary_cycle)
               hud_message(MSGC_GAME_FEEDBACK, "Primary autoselect Off");
              else
               hud_message(MSGC_GAME_FEEDBACK, "Primary autoselect On");
             Allow_primary_cycle_count = 0;
             Allow_primary_cycle_ostate = Allow_primary_cycle_jstate;
            }
          }
      }
//end addition - Victor Rachels

      {
       int Allow_secondary_cycle_count=0;
       int Allow_secondary_cycle_jstate=0;

//added/killed on 2/4/99 by Victor Rachels for d1x keys
         if ( kc_d1x[26].value < 255 ) Allow_secondary_cycle_count += key_down_count(kc_d1x[26].value);
         if ( (use_joystick)&&(kc_d1x[27].value < 255) ) Allow_secondary_cycle_jstate= joy_get_button_state( kc_d1x[27].value );

//-killed-         if ( kc_keyboard[52].value < 255 ) Allow_secondary_cycle_count += key_down_count(kc_keyboard[52].value);
//-killed-         if ( kc_keyboard[53].value < 255 ) Allow_secondary_cycle_count += key_down_count(kc_keyboard[53].value);
//-killed-         if ( (use_joystick)&&(kc_joystick[30].value < 255) ) Allow_secondary_cycle_jstate= joy_get_button_state( kc_joystick[30].value );
//end this section change - VR

         if (Allow_secondary_cycle_count || Allow_secondary_cycle_jstate!=Allow_secondary_cycle_ostate)
          {
           if((Allow_secondary_cycle_jstate!=Allow_secondary_cycle_ostate)&&(Allow_secondary_cycle_jstate==0))
            Allow_secondary_cycle_ostate = Allow_secondary_cycle_jstate;
           else
            {
             Allow_secondary_cycle = !Allow_secondary_cycle;
              if(!Allow_secondary_cycle)
               hud_message(MSGC_GAME_FEEDBACK, "Secondary autoselect Off");
              else
               hud_message(MSGC_GAME_FEEDBACK, "Secondary autoselect On");
             Allow_secondary_cycle_count = 0;
             Allow_secondary_cycle_ostate = Allow_secondary_cycle_jstate;
            }
          }
      }
//end this section addition/edit - Victor Rachels

//added on 8/6/98 by Victor Rachels to add cycle primary/secondary
//killed on 8/7/98 by Victor Rachels due to compatability problems.
//brought back on 8/21/98 by Victor Rachels cuz I think I fixed it
  //Read primary cycle

///added/killed on 2/4/99 by Victor Rachels for d1x keys
        if ( kc_d1x[20].value < 255 ) Controls.cycle_primary_down_count += key_down_count(kc_d1x[20].value);
        if ( (use_joystick)&&(kc_d1x[21].value < 255) ) Controls.cycle_primary_state= joy_get_button_state( kc_d1x[21].value );


//-killed-        if ( kc_keyboard[46].value < 255 ) Controls.cycle_primary_down_count += key_down_count(kc_keyboard[46].value);
//-killed-        if ( kc_keyboard[47].value < 255 ) Controls.cycle_primary_down_count += key_down_count(kc_keyboard[47].value);
//-killed-        if ( (use_joystick)&&(kc_joystick[27].value < 255 ) ) Controls.cycle_primary_state = joy_get_button_state( kc_joystick[27].value );

  //Read secondary cycle

        if ( kc_d1x[22].value < 255 ) Controls.cycle_secondary_down_count += key_down_count(kc_d1x[22].value);
        if ( (use_joystick)&&(kc_d1x[23].value < 255) ) Controls.cycle_secondary_state= joy_get_button_state( kc_d1x[23].value );


//-killed-        if ( kc_keyboard[48].value < 255 ) Controls.cycle_secondary_down_count += key_down_count(kc_keyboard[48].value);
//-killed-        if ( kc_keyboard[49].value < 255 ) Controls.cycle_secondary_down_count += key_down_count(kc_keyboard[49].value);
//-killed-        if ( (use_joystick)&&(kc_joystick[28].value < 255 ) ) Controls.cycle_secondary_state = joy_get_button_state( kc_joystick[28].value );
//end this section addition/kill - VR
//end edit - Victor Rachels
}//end "if (!Player_is_dead)" - WraithX

//------------- Read slide_on -------------
	
	// From keyboard...
	if ( kc_keyboard[8].value < 255 ) slide_on |= keyd_pressed[ kc_keyboard[8].value ];
	if ( kc_keyboard[9].value < 255 ) slide_on |= keyd_pressed[ kc_keyboard[9].value ];
	// From joystick...
	if ((use_joystick)&&(kc_joystick[5].value<255)) slide_on |= joy_get_button_state( kc_joystick[5].value );
	// From mouse...
	if ((use_mouse)&&(kc_mouse[5].value<255)) slide_on |= mouse_buttons & (1<<kc_mouse[5].value);

//------------- Read bank_on ---------------

	// From keyboard...
	if ( kc_keyboard[18].value < 255 ) bank_on |= keyd_pressed[ kc_keyboard[18].value ];
	if ( kc_keyboard[19].value < 255 ) bank_on |= keyd_pressed[ kc_keyboard[19].value ];
	// From joystick...
	if ( (use_joystick)&&(kc_joystick[10].value < 255 )) bank_on |= joy_get_button_state( kc_joystick[10].value );
	// From mouse...
	if ( (use_mouse)&&(kc_mouse[10].value < 255 )) bank_on |= mouse_buttons & (1<<kc_mouse[10].value);

//------------ Read pitch_time -----------
	if ( !slide_on )	{
		// mprintf((0, "pitch: %7.3f %7.3f: %7.3f\n", f2fl(k4), f2fl(k6), f2fl(Controls.heading_time)));
		kp = 0;
		k0 = speed_factor*key_down_time( kc_keyboard[0].value )/2;	// Divide by two since we want pitch to go slower
		k1 = speed_factor*key_down_time( kc_keyboard[1].value )/2;
		k2 = speed_factor*key_down_time( kc_keyboard[2].value )/2;
		k3 = speed_factor*key_down_time( kc_keyboard[3].value )/2;

		// From keyboard...
		if ( kc_keyboard[0].value < 255 ) kp += k0/PH_SCALE;
		if ( kc_keyboard[1].value < 255 ) kp += k1/PH_SCALE;
		if ( kc_keyboard[2].value < 255 ) kp -= k2/PH_SCALE;
		if ( kc_keyboard[3].value < 255 ) kp -= k3/PH_SCALE;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			kp += mouse_button_down_time(MB_PITCH_FORWARD)/(PH_SCALE*2);
			kp -= mouse_button_down_time(MB_PITCH_BACKWARD)/(PH_SCALE*2);
		}
	
		if (kp == 0)
			Controls.pitch_time = 0;
		else if (kp > 0) {
			if (Controls.pitch_time < 0)
				Controls.pitch_time = 0;
		} else // kp < 0
			if (Controls.pitch_time > 0)
				Controls.pitch_time = 0;
		Controls.pitch_time += kp;
	
		// From joystick...
		if ( (use_joystick)&&(kc_joystick[13].value < 255 ))	{
			if ( !kc_joystick[14].value )		// If not inverted...
				Controls.pitch_time -= (joy_axis[kc_joystick[13].value]*Config_joystick_sensitivity)/8;
			else
				Controls.pitch_time += (joy_axis[kc_joystick[13].value]*Config_joystick_sensitivity)/8;
		}
	
		// From mouse...
		//mprintf(( 0, "UM: %d, PV: %d\n", use_mouse, kc_mouse[13].value ));
		if ( (use_mouse)&&(kc_mouse[13].value < 255) )	{
			if ( !kc_mouse[14].value )		// If not inverted...
				Controls.pitch_time -= (mouse_axis[kc_mouse[13].value]*Config_joystick_sensitivity)/4;
			else
				Controls.pitch_time += (mouse_axis[kc_mouse[13].value]*Config_joystick_sensitivity)/4;
		}
	} else {
		Controls.pitch_time = 0;
	}

//the following "if" added by WraithX, 4/14/00
//done so that dead players can't move
if (!Player_is_dead)
{
//----------- Read vertical_thrust_time -----------------

	if ( slide_on )	{
		k0 = speed_factor*key_down_time( kc_keyboard[0].value );
		k1 = speed_factor*key_down_time( kc_keyboard[1].value );
		k2 = speed_factor*key_down_time( kc_keyboard[2].value );
		k3 = speed_factor*key_down_time( kc_keyboard[3].value );

		// From keyboard...
		if ( kc_keyboard[0].value < 255 ) Controls.vertical_thrust_time += k0;
		if ( kc_keyboard[1].value < 255 ) Controls.vertical_thrust_time += k1;
		if ( kc_keyboard[2].value < 255 ) Controls.vertical_thrust_time -= k2;
		if ( kc_keyboard[3].value < 255 ) Controls.vertical_thrust_time -= k3;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			Controls.vertical_thrust_time -= mouse_button_down_time(MB_PITCH_FORWARD);
			Controls.vertical_thrust_time += mouse_button_down_time(MB_PITCH_BACKWARD);
		}
	
		// From joystick...
		if ((use_joystick)&&( kc_joystick[13].value < 255 ))	{
			if ( !kc_joystick[14].value )		// If not inverted...
				Controls.vertical_thrust_time += joy_axis[kc_joystick[13].value];
			else
				Controls.vertical_thrust_time -= joy_axis[kc_joystick[13].value];
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[13].value < 255 ))	{
			if ( !kc_mouse[14].value )		// If not inverted...
				Controls.vertical_thrust_time -= mouse_axis[kc_mouse[13].value];
			else
				Controls.vertical_thrust_time += mouse_axis[kc_mouse[13].value];
		}
	}

	// From keyboard...
	if ( kc_keyboard[14].value < 255 ) Controls.vertical_thrust_time += speed_factor*key_down_time( kc_keyboard[14].value );
	if ( kc_keyboard[15].value < 255 ) Controls.vertical_thrust_time += speed_factor*key_down_time( kc_keyboard[15].value );
	if ( kc_keyboard[16].value < 255 ) Controls.vertical_thrust_time -= speed_factor*key_down_time( kc_keyboard[16].value );
	if ( kc_keyboard[17].value < 255 ) Controls.vertical_thrust_time -= speed_factor*key_down_time( kc_keyboard[17].value );
	
	// From joystick...
	if ((use_joystick)&&( kc_joystick[19].value < 255 ))	{
		if ( !kc_joystick[20].value )		// If not inverted...
			Controls.vertical_thrust_time += joy_axis[kc_joystick[19].value];
		else
			Controls.vertical_thrust_time -= joy_axis[kc_joystick[19].value];
	}

	// From joystick buttons
	if ( (use_joystick)&&(kc_joystick[8].value < 255 )) Controls.vertical_thrust_time += joy_get_button_down_time( kc_joystick[8].value );
	if ( (use_joystick)&&(kc_joystick[9].value < 255 )) Controls.vertical_thrust_time -= joy_get_button_down_time( kc_joystick[9].value );

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[8].value < 255 )) Controls.vertical_thrust_time += mouse_button_down_time( kc_mouse[8].value );
	if ( (use_mouse)&&(kc_mouse[9].value < 255 )) Controls.vertical_thrust_time -= mouse_button_down_time( kc_mouse[9].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[19].value < 255 ))	{
		if ( !kc_mouse[20].value )		// If not inverted...
			Controls.vertical_thrust_time += mouse_axis[kc_mouse[19].value];
		else
			Controls.vertical_thrust_time -= mouse_axis[kc_mouse[19].value];
	}

	// From Cyberman...
	if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
		Controls.vertical_thrust_time += mouse_button_down_time(MB_Z_UP)/2;
		Controls.vertical_thrust_time -= mouse_button_down_time(MB_Z_DOWN)/2;
	}
}//end "if" added by WraithX

//---------- Read heading_time -----------

	if (!slide_on && !bank_on)	{
		//mprintf((0, "heading: %7.3f %7.3f: %7.3f\n", f2fl(k4), f2fl(k6), f2fl(Controls.heading_time)));
		kh = 0;
		k4 = speed_factor*key_down_time( kc_keyboard[4].value );
		k5 = speed_factor*key_down_time( kc_keyboard[5].value );
		k6 = speed_factor*key_down_time( kc_keyboard[6].value );
		k7 = speed_factor*key_down_time( kc_keyboard[7].value );

		// From keyboard...
		if ( kc_keyboard[4].value < 255 ) kh -= k4/PH_SCALE;
		if ( kc_keyboard[5].value < 255 ) kh -= k5/PH_SCALE;
		if ( kc_keyboard[6].value < 255 ) kh += k6/PH_SCALE;
		if ( kc_keyboard[7].value < 255 ) kh += k7/PH_SCALE;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			kh -= mouse_button_down_time(MB_HEAD_LEFT)/PH_SCALE;
			kh += mouse_button_down_time(MB_HEAD_RIGHT)/PH_SCALE;
		}
	
		if (kh == 0)
			Controls.heading_time = 0;
		else if (kh > 0) {
			if (Controls.heading_time < 0)
				Controls.heading_time = 0;
		} else // kh < 0
			if (Controls.heading_time > 0)
				Controls.heading_time = 0;
		Controls.heading_time += kh;

		// From joystick...
		if ( (use_joystick)&&(kc_joystick[15].value < 255 ))	{
			if ( !kc_joystick[16].value )		// If not inverted...
				Controls.heading_time += (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
			else
				Controls.heading_time -= (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[15].value < 255 ))	{
			if ( !kc_mouse[16].value )		// If not inverted...
				Controls.heading_time += (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/4;
			else
				Controls.heading_time -= (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/4;
		}
	} else {
		Controls.heading_time = 0;
	}

//the following "if" added by WraithX, 4/14/00
//done so that dead players can't move
if (!Player_is_dead)
{
//----------- Read sideways_thrust_time -----------------

	if ( slide_on )	{
		k0 = speed_factor*key_down_time( kc_keyboard[4].value );
		k1 = speed_factor*key_down_time( kc_keyboard[5].value );
		k2 = speed_factor*key_down_time( kc_keyboard[6].value );
		k3 = speed_factor*key_down_time( kc_keyboard[7].value );

		// From keyboard...
		if ( kc_keyboard[4].value < 255 ) Controls.sideways_thrust_time -= k0;
		if ( kc_keyboard[5].value < 255 ) Controls.sideways_thrust_time -= k1;
		if ( kc_keyboard[6].value < 255 ) Controls.sideways_thrust_time += k2;
		if ( kc_keyboard[7].value < 255 ) Controls.sideways_thrust_time += k3;
	
		// From joystick...
		if ( (use_joystick)&&(kc_joystick[15].value < 255 ))	{
			if ( !kc_joystick[16].value )		// If not inverted...
				Controls.sideways_thrust_time += joy_axis[kc_joystick[15].value];
			else
				Controls.sideways_thrust_time -= joy_axis[kc_joystick[15].value];
		}
		
		// From cyberman
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			Controls.sideways_thrust_time -= mouse_button_down_time(MB_HEAD_LEFT);
			Controls.sideways_thrust_time += mouse_button_down_time(MB_HEAD_RIGHT);
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[15].value < 255 ))	{
			if ( !kc_mouse[16].value )		// If not inverted...
				Controls.sideways_thrust_time += mouse_axis[kc_mouse[15].value];
			else
				Controls.sideways_thrust_time -= mouse_axis[kc_mouse[15].value];
		}
	}

	// From keyboard...
	if ( kc_keyboard[10].value < 255 ) Controls.sideways_thrust_time -= speed_factor*key_down_time( kc_keyboard[10].value );
	if ( kc_keyboard[11].value < 255 ) Controls.sideways_thrust_time -= speed_factor*key_down_time( kc_keyboard[11].value );
	if ( kc_keyboard[12].value < 255 ) Controls.sideways_thrust_time += speed_factor*key_down_time( kc_keyboard[12].value );
	if ( kc_keyboard[13].value < 255 ) Controls.sideways_thrust_time += speed_factor*key_down_time( kc_keyboard[13].value );
	
	// From joystick...
	if ( (use_joystick)&&(kc_joystick[17].value < 255 ))	{
		if ( !kc_joystick[18].value )		// If not inverted...
			Controls.sideways_thrust_time -= joy_axis[kc_joystick[17].value];
		else
			Controls.sideways_thrust_time += joy_axis[kc_joystick[17].value];
	}

	// From joystick buttons
	if ( (use_joystick)&&(kc_joystick[6].value < 255 )) Controls.sideways_thrust_time -= joy_get_button_down_time( kc_joystick[6].value );
	if ( (use_joystick)&&(kc_joystick[7].value < 255 )) Controls.sideways_thrust_time += joy_get_button_down_time( kc_joystick[7].value );

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[6].value < 255 )) Controls.sideways_thrust_time -= mouse_button_down_time( kc_mouse[6].value );
	if ( (use_mouse)&&(kc_mouse[7].value < 255 )) Controls.sideways_thrust_time += mouse_button_down_time( kc_mouse[7].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[17].value < 255 ))	{
		if ( !kc_mouse[18].value )		// If not inverted...
			Controls.sideways_thrust_time += mouse_axis[kc_mouse[17].value];
		else
			Controls.sideways_thrust_time -= mouse_axis[kc_mouse[17].value];
	}
}//end "if" added by WraithX

//----------- Read bank_time -----------------

	if ( bank_on )	{
		k0 = speed_factor*key_down_time( kc_keyboard[4].value );
		k1 = speed_factor*key_down_time( kc_keyboard[5].value );
		k2 = speed_factor*key_down_time( kc_keyboard[6].value );
		k3 = speed_factor*key_down_time( kc_keyboard[7].value );

		// From keyboard...
		if ( kc_keyboard[4].value < 255 ) Controls.bank_time += k0;
		if ( kc_keyboard[5].value < 255 ) Controls.bank_time += k1;
		if ( kc_keyboard[6].value < 255 ) Controls.bank_time -= k2;
		if ( kc_keyboard[7].value < 255 ) Controls.bank_time -= k3;

		// From Cyberman...
		if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
			Controls.bank_time -= mouse_button_down_time(MB_HEAD_LEFT);
			Controls.bank_time += mouse_button_down_time(MB_HEAD_RIGHT);
		}

		// From joystick...
		if ( (use_joystick)&&(kc_joystick[15].value < 255) )	{
			if ( !kc_joystick[16].value )		// If not inverted...
				Controls.bank_time -= (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
			else
				Controls.bank_time += (joy_axis[kc_joystick[15].value]*Config_joystick_sensitivity)/8;
		}
	
		// From mouse...
		if ( (use_mouse)&&(kc_mouse[15].value < 255 ))	{
			if ( !kc_mouse[16].value )		// If not inverted...
				Controls.bank_time += (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/4;
			else
				Controls.bank_time -= (mouse_axis[kc_mouse[15].value]*Config_joystick_sensitivity)/4;
		}
	}

	// From keyboard...
	if ( kc_keyboard[20].value < 255 ) Controls.bank_time += speed_factor*key_down_time( kc_keyboard[20].value );
	if ( kc_keyboard[21].value < 255 ) Controls.bank_time += speed_factor*key_down_time( kc_keyboard[21].value );
	if ( kc_keyboard[22].value < 255 ) Controls.bank_time -= speed_factor*key_down_time( kc_keyboard[22].value );
	if ( kc_keyboard[23].value < 255 ) Controls.bank_time -= speed_factor*key_down_time( kc_keyboard[23].value );

	// From joystick...
	if ( (use_joystick)&&(kc_joystick[21].value < 255) )	{
		if ( !kc_joystick[22].value )		// If not inverted...
			Controls.bank_time -= joy_axis[kc_joystick[21].value];
		else
			Controls.bank_time += joy_axis[kc_joystick[21].value];
	}

	// From joystick buttons
	if ( (use_joystick)&&(kc_joystick[11].value < 255 )) Controls.bank_time += joy_get_button_down_time( kc_joystick[11].value );
	if ( (use_joystick)&&(kc_joystick[12].value < 255 )) Controls.bank_time -= joy_get_button_down_time( kc_joystick[12].value );

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[11].value < 255 )) Controls.bank_time += mouse_button_down_time( kc_mouse[11].value );
	if ( (use_mouse)&&(kc_mouse[12].value < 255 )) Controls.bank_time -= mouse_button_down_time( kc_mouse[12].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[21].value < 255 ))	{
		if ( !kc_mouse[22].value )		// If not inverted...
			Controls.bank_time += mouse_axis[kc_mouse[21].value];
		else
			Controls.bank_time -= mouse_axis[kc_mouse[21].value];
	}

	// From Cyberman
	if ((use_mouse)&&(Config_control_type==CONTROL_CYBERMAN))	{
		Controls.bank_time += mouse_button_down_time(MB_BANK_LEFT);
		Controls.bank_time -= mouse_button_down_time(MB_BANK_RIGHT);
	}

//the following "if" added by WraithX, 4/14/00
//done so that dead players can't move
if (!Player_is_dead)
{
//----------- Read forward_thrust_time -------------

	// From keyboard...
	if ( kc_keyboard[30].value < 255 ) Controls.forward_thrust_time += speed_factor*key_down_time( kc_keyboard[30].value );
	if ( kc_keyboard[31].value < 255 ) Controls.forward_thrust_time += speed_factor*key_down_time( kc_keyboard[31].value );
	if ( kc_keyboard[32].value < 255 ) Controls.forward_thrust_time -= speed_factor*key_down_time( kc_keyboard[32].value );
	if ( kc_keyboard[33].value < 255 ) Controls.forward_thrust_time -= speed_factor*key_down_time( kc_keyboard[33].value );

	// From joystick...
	if ( (use_joystick)&&(kc_joystick[23].value < 255 ))	{
		if ( !kc_joystick[24].value )		// If not inverted...
			Controls.forward_thrust_time -= joy_axis[kc_joystick[23].value];
		else
			Controls.forward_thrust_time += joy_axis[kc_joystick[23].value];
	}

	// From joystick buttons
	if ( (use_joystick)&&(kc_joystick[2].value < 255 )) Controls.forward_thrust_time += joy_get_button_down_time( kc_joystick[2].value );
	if ( (use_joystick)&&(kc_joystick[3].value < 255 )) Controls.forward_thrust_time -= joy_get_button_down_time( kc_joystick[3].value );

	// From mouse...
	if ( (use_mouse)&&(kc_mouse[23].value < 255 ))	{
		if ( !kc_mouse[24].value )		// If not inverted...
			Controls.forward_thrust_time -= mouse_axis[kc_mouse[23].value];
		else
			Controls.forward_thrust_time += mouse_axis[kc_mouse[23].value];
	}

	// From mouse buttons
	if ( (use_mouse)&&(kc_mouse[2].value < 255 )) Controls.forward_thrust_time += mouse_button_down_time( kc_mouse[2].value );
	if ( (use_mouse)&&(kc_mouse[3].value < 255 )) Controls.forward_thrust_time -= mouse_button_down_time( kc_mouse[3].value );

//----------- Read fire_primary_down_count
        if (kc_keyboard[24].value < 255 ) Controls.fire_primary_down_count += key_down_count(kc_keyboard[24].value);
        if (kc_keyboard[25].value < 255 ) Controls.fire_primary_down_count += key_down_count(kc_keyboard[25].value);
        if ((use_joystick)&&(kc_joystick[0].value < 255 )) Controls.fire_primary_down_count += joy_get_button_down_cnt(kc_joystick[0].value);
        if ((use_mouse)&&(kc_mouse[0].value < 255 )) Controls.fire_primary_down_count += mouse_button_down_count(kc_mouse[0].value);

       #ifdef NETWORK
        if(use_alt_vulcanfire)
         {
            if(Primary_weapon != VULCAN_INDEX)
             {
               Vulcan_jostate = 0;
               Vulcan_kostate = 0;
               Vulcan_mostate = 0;
               do_vulcan_fire(0);
             }
            else
             {
              int Vulcan_jstate=0;
              int Vulcan_kstate=0;
              int Vulcan_mstate=0;
                Vulcan_kstate = (keyd_pressed[kc_keyboard[24].value]||keyd_pressed[kc_keyboard[25].value]);
                Vulcan_jstate = joy_get_button_state( kc_joystick[0].value);
                Vulcan_mstate = mouse_button_state( kc_mouse[0].value);

                if (Vulcan_kstate!=Vulcan_kostate || Vulcan_jstate!=Vulcan_jostate || Vulcan_mstate!=Vulcan_mostate)
                 {
                   do_vulcan_fire(Vulcan_kstate||Vulcan_jstate||Vulcan_mstate);
                   Vulcan_kostate = Vulcan_kstate;
                   Vulcan_jostate = Vulcan_jstate;
                   Vulcan_mostate = Vulcan_mstate;
                 }
             }
         }
       #endif

//----------- Read fire_primary_state
	if (kc_keyboard[24].value < 255 ) Controls.fire_primary_state |= keyd_pressed[kc_keyboard[24].value];
	if (kc_keyboard[25].value < 255 ) Controls.fire_primary_state |= keyd_pressed[kc_keyboard[25].value];
	if ((use_joystick)&&(kc_joystick[0].value < 255 )) Controls.fire_primary_state |= joy_get_button_state(kc_joystick[0].value);
	if ((use_mouse)&&(kc_mouse[0].value < 255) ) Controls.fire_primary_state |= mouse_button_state(kc_mouse[0].value);

//----------- Read fire_secondary_down_count
	if (kc_keyboard[26].value < 255 ) Controls.fire_secondary_down_count += key_down_count(kc_keyboard[26].value);
	if (kc_keyboard[27].value < 255 ) Controls.fire_secondary_down_count += key_down_count(kc_keyboard[27].value);
	if ((use_joystick)&&(kc_joystick[1].value < 255 )) Controls.fire_secondary_down_count += joy_get_button_down_cnt(kc_joystick[1].value);
	if ((use_mouse)&&(kc_mouse[1].value < 255 )) Controls.fire_secondary_down_count += mouse_button_down_count(kc_mouse[1].value);

//----------- Read fire_secondary_state
	if (kc_keyboard[26].value < 255 ) Controls.fire_secondary_state |= keyd_pressed[kc_keyboard[26].value];
	if (kc_keyboard[27].value < 255 ) Controls.fire_secondary_state |= keyd_pressed[kc_keyboard[27].value];
	if ((use_joystick)&&(kc_joystick[1].value < 255 )) Controls.fire_secondary_state |= joy_get_button_state(kc_joystick[1].value);
	if ((use_mouse)&&(kc_mouse[1].value < 255) ) Controls.fire_secondary_state |= mouse_button_state(kc_mouse[1].value);

//----------- Read fire_flare_down_count
	if (kc_keyboard[28].value < 255 ) Controls.fire_flare_down_count += key_down_count(kc_keyboard[28].value);
	if (kc_keyboard[29].value < 255 ) Controls.fire_flare_down_count += key_down_count(kc_keyboard[29].value);
	if ((use_joystick)&&(kc_joystick[4].value < 255 )) Controls.fire_flare_down_count += joy_get_button_down_cnt(kc_joystick[4].value);
	if ((use_mouse)&&(kc_mouse[4].value < 255 )) Controls.fire_flare_down_count += mouse_button_down_count(kc_mouse[4].value);

//----------- Read drop_bomb_down_count
	if (kc_keyboard[34].value < 255 ) Controls.drop_bomb_down_count += key_down_count(kc_keyboard[34].value);
	if (kc_keyboard[35].value < 255 ) Controls.drop_bomb_down_count += key_down_count(kc_keyboard[35].value);
	if ((use_joystick)&&(kc_joystick[26].value < 255 )) Controls.drop_bomb_down_count += joy_get_button_down_cnt(kc_joystick[26].value);
	if ((use_mouse)&&(kc_mouse[26].value < 255 )) Controls.drop_bomb_down_count += mouse_button_down_count(kc_mouse[26].value);

//----------- Read rear_view_down_count
	if (kc_keyboard[36].value < 255 ) Controls.rear_view_down_count += key_down_count(kc_keyboard[36].value);
	if (kc_keyboard[37].value < 255 ) Controls.rear_view_down_count += key_down_count(kc_keyboard[37].value);
	if ((use_joystick)&&(kc_joystick[25].value < 255 )) Controls.rear_view_down_count += joy_get_button_down_cnt(kc_joystick[25].value);
	if ((use_mouse)&&(kc_mouse[25].value < 255 )) Controls.rear_view_down_count += mouse_button_down_count(kc_mouse[25].value);

//----------- Read rear_view_down_state
	if (kc_keyboard[36].value < 255 ) Controls.rear_view_down_state |= keyd_pressed[kc_keyboard[36].value];
	if (kc_keyboard[37].value < 255 ) Controls.rear_view_down_state |= keyd_pressed[kc_keyboard[37].value];
	if ((use_joystick)&&(kc_joystick[25].value < 255 )) Controls.rear_view_down_state |= joy_get_button_state(kc_joystick[25].value);
	if ((use_mouse)&&(kc_mouse[25].value < 255 )) Controls.rear_view_down_state |= mouse_button_state(kc_mouse[25].value);

}//end "if" added by WraithX

//----------- Read automap_down_count
	if (kc_keyboard[44].value < 255 ) Controls.automap_down_count += key_down_count(kc_keyboard[44].value);
	if (kc_keyboard[45].value < 255 ) Controls.automap_down_count += key_down_count(kc_keyboard[45].value);

//----------- Read automap_state
	if (kc_keyboard[44].value < 255 ) Controls.automap_state |= keyd_pressed[kc_keyboard[44].value];
	if (kc_keyboard[45].value < 255 ) Controls.automap_state |= keyd_pressed[kc_keyboard[45].value];

//----------- Read stupid-cruise-control-type of throttle.
	{
		if ( kc_keyboard[38].value < 255 ) Cruise_speed += fixdiv(speed_factor*key_down_time(kc_keyboard[38].value)*5,FrameTime);
		if ( kc_keyboard[39].value < 255 ) Cruise_speed += fixdiv(speed_factor*key_down_time(kc_keyboard[39].value)*5,FrameTime);
		if ( kc_keyboard[40].value < 255 ) Cruise_speed -= fixdiv(speed_factor*key_down_time(kc_keyboard[40].value)*5,FrameTime);
		if ( kc_keyboard[41].value < 255 ) Cruise_speed -= fixdiv(speed_factor*key_down_time(kc_keyboard[41].value)*5,FrameTime);
		if ( (kc_keyboard[42].value < 255) && (key_down_count(kc_keyboard[42].value)) )
			Cruise_speed = 0;
		if ( (kc_keyboard[43].value < 255) && (key_down_count(kc_keyboard[43].value)) )
			Cruise_speed = 0;
	
		if (Cruise_speed > i2f(100) ) Cruise_speed = i2f(100);
		if (Cruise_speed < 0 ) Cruise_speed = 0;
	
		if (Controls.forward_thrust_time==0)
			Controls.forward_thrust_time = fixmul(Cruise_speed,FrameTime)/100;
	}

	// Read external controls
	if (kc_use_external_control)
		kconfig_read_external_controls();

//----------- Clamp values between -FrameTime and FrameTime
	if (FrameTime > F1_0 )
		mprintf( (1, "Bogus frame time of %.2f seconds\n", f2fl(FrameTime) ));

	if (Controls.pitch_time > FrameTime/2 ) Controls.pitch_time = FrameTime/2;
	if (Controls.vertical_thrust_time > FrameTime ) Controls.vertical_thrust_time = FrameTime;
	if (Controls.heading_time > FrameTime ) Controls.heading_time = FrameTime;
	if (Controls.sideways_thrust_time > FrameTime ) Controls.sideways_thrust_time = FrameTime;
	if (Controls.bank_time > FrameTime ) Controls.bank_time = FrameTime;
	if (Controls.forward_thrust_time > FrameTime ) Controls.forward_thrust_time = FrameTime;
//	if (Controls.afterburner_time > FrameTime ) Controls.afterburner_time = FrameTime;

	if (Controls.pitch_time < -FrameTime/2 ) Controls.pitch_time = -FrameTime/2;
	if (Controls.vertical_thrust_time < -FrameTime ) Controls.vertical_thrust_time = -FrameTime;
	if (Controls.heading_time < -FrameTime ) Controls.heading_time = -FrameTime;
	if (Controls.sideways_thrust_time < -FrameTime ) Controls.sideways_thrust_time = -FrameTime;
	if (Controls.bank_time < -FrameTime ) Controls.bank_time = -FrameTime;
	if (Controls.forward_thrust_time < -FrameTime ) Controls.forward_thrust_time = -FrameTime;
//	if (Controls.afterburner_time < -FrameTime ) Controls.afterburner_time = -FrameTime;


//--------- Don't do anything if in debug mode
	#ifndef NDEBUG
	if ( keyd_pressed[KEY_DELETE] )	{
		memset( &Controls, 0, sizeof(control_info) );
	}
	#endif
}

void reset_cruise(void)
{
	Cruise_speed=0;
}


void kc_set_controls()
{
 int i;

   for (i=0; i<NUM_ALL_KEY_CONTROLS; i++ ) 
    kc_keyboard[i].value = kconfig_settings[0][i];

   if ( (Config_control_type>0) && (Config_control_type<5))
    {
       for (i=0; i<NUM_ALL_OTHER_CONTROLS; i++ )
        {
          kc_joystick[i].value = kconfig_settings[Config_control_type][i];
           if (kc_joystick[i].type == BT_INVERT )
            {
               if (kc_joystick[i].value!=1)
                kc_joystick[i].value    = 0;
              kconfig_settings[Config_control_type][i] = kc_joystick[i].value;
            }
        }
    }
   else if (Config_control_type>4)
    {
       for (i=0; i<NUM_OTHER_CONTROLS; i++ )
        {
          kc_mouse[i].value = kconfig_settings[Config_control_type][i];
           if (kc_mouse[i].type == BT_INVERT )
            {
               if (kc_mouse[i].value!=1)
                kc_mouse[i].value = 0;
              kconfig_settings[Config_control_type][i] = kc_mouse[i].value;
            }
        }
    }

   for (i=0; i<NUM_D1X_CONTROLS; i++ )
    kc_d1x[i].value = kconfig_d1x_settings[i];
}
