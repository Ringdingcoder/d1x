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
/* $Source$
 * $Revision$
 * $Author$
 * $Date$
 *
 * main() for Inferno  
 *
 * $Log$
 * Revision 1.1  2002/07/22 09:19:34  Administrator
 * Initial revision
 *
 * Revision 1.33  2002/04/24 06:44:07  donut
 * add -renderstats command line arg to activate RENDERSTATS
 *
 * Revision 1.32  2002/04/22 20:15:35  donut
 * add anisotropic texture filtering support
 *
 * Revision 1.31  2002/04/01 01:58:17  donut
 * add -gl_trilinear OGL command line option
 *
 * Revision 1.30  2002/04/01 01:42:11  donut
 * restore inferno.c initialization of screen_compatible and use_double_buffer to 'normal' values, broken long long ago in one of the high res menu patches
 *
 * Revision 1.29  2002/04/01 01:21:57  donut
 * allow arbitrary resolutions to be specified on command line
 *
 * Revision 1.28  2002/03/21 20:49:55  donut
 * add -ip_bind_addr option
 *
 * Revision 1.27  2000/11/13 04:33:55  donut
 * add -rearviewtime argument
 *
 * Revision 1.26  2000/04/21 22:15:34  sekmu
 * ordered -? output
 *
 * Revision 1.25  2000/04/18 01:19:02  sekmu
 * Changed/fixed altsounds (mostly done)
 *
 * Revision 1.24  2000/03/06 01:42:10  donut
 * noudp_debug and nonetwork fixes
 *
 * Revision 1.23  2000/02/07 10:53:06  donut
 * documented new ip_* arguments
 *
 * Revision 1.22  2000/02/07 10:26:05  donut
 * new ipx code structure reduces some redundancy and gives all arches multi netcode ability
 *
 * Revision 1.21  2000/01/17 07:39:17  donut
 * switched to SUPPORTS_NICEFPS and added -hudlog_multi switch
 *
 * Revision 1.20  2000/01/12 09:52:23  donut
 * document -gl_refresh
 *
 * Revision 1.19  1999/12/08 01:03:51  donut
 * allow runtime selection of tmap routines
 *
 * Revision 1.18  1999/11/21 13:00:08  donut
 * Changed screen_mode format.  Now directly encodes res into a 32bit int, rather than using arbitrary values.
 *
 * Revision 1.17  1999/11/20 10:05:17  donut
 * variable size menu patch from Jan Bobrowski.  Variable menu font size support and a bunch of fixes for menus that didn't work quite right, by me (MPM).
 *
 * Revision 1.16  1999/11/15 10:43:37  sekmu
 * added -altsounds
 *
 * Revision 1.15  1999/10/20 07:34:06  donut
 * opengl rendered reticle, and better g3_draw_sphere
 *
 * Revision 1.14  1999/10/08 10:48:03  donut
 * gl_alttexmerge default now
 *
 * Revision 1.13  1999/10/08 04:26:01  donut
 * automap fix for high fps(including -niceautomap), -automap_gameres, and better -font* help
 *
 * Revision 1.12  1999/10/08 00:57:53  donut
 * documented various ogl and -font command line switches
 *
 * Revision 1.11  1999/09/30 01:46:35  donut
 * added -gl_mipmap and -gl_simple, and documented them
 *
 * Revision 1.10  1999/09/21 00:12:14  sekmu
 * remove -cockpit 4 option
 *
 * Revision 1.9  1999/09/18 07:56:03  donut
 * changed call to texmerge_init so it'll cache as much as possible (great boost on OGL, since uploading textures to the card is slow)
 *
 * Revision 1.8  1999/09/16 03:34:15  donut
 * cleaned up fullscreen toggle code to make it easy to add support to other targets later, and added -nosdlvidmodecheck
 *
 * Revision 1.7  1999/08/31 21:22:08  donut
 * added variable colorization level, and colorization for kill/join/quit messages
 *
 * Revision 1.6  1999/08/31 07:47:03  donut
 * added user configurable number of hud message lines (and moved some defines to hudmsg.h to remove redundancy in gauges.c)
 *
 * Revision 1.5  1999/08/14 15:49:51  donut
 * moved MENU_SCREEN_MODE to main/screens.h so that it can be used for the startup screen mode in inferno.c
 *
 * Revision 1.4  1999/08/05 22:53:41  sekmu
 *
 * D3D patch(es) from ADB
 *
 * Revision 1.3  1999/07/10 03:00:38  donut
 * allow -cockpit 4
 *
 * Revision 1.2  1999/06/14 23:44:12  donut
 * Orulz' svgalib/ggi/noerror patches.
 *
 * Revision 1.1.1.1  1999/06/14 22:08:00  donut
 * Import of d1x 1.37 source.
 *
 * Revision 2.36  1996/01/05  16:52:16  john
 * Improved 3d stuff.
 * 
 * Revision 2.35  1995/10/07  13:20:06  john
 * Added new modes for LCDBIOS, also added support for -JoyNice,
 * and added Shift+F1-F4 to controls various stereoscopic params.
 * 
 * Revision 2.34  1995/06/26  11:30:57  john
 * Made registration/copyright screen go away after 5 minutes.
 * 
 * Revision 2.33  1995/05/31  14:26:55  unknown
 * Fixed ugly spacing.
 * 
 * Revision 2.32  1995/05/26  16:15:28  john
 * Split SATURN into define's for requiring cd, using cd, etc.
 * Also started adding all the Rockwell stuff.
 * 
 * Revision 2.31  1995/05/11  13:30:01  john
 * Changed 3dbios detection to work like Didde Kim wanted it to.
 * 
 * Revision 2.30  1995/05/08  13:53:50  john
 * Added code to read vipport environemnt variable.
 * 
 * Revision 2.29  1995/05/08  11:26:18  john
 * Reversed eyes in 3dmax mode.
 * 
 * Revision 2.28  1995/05/08  11:24:06  john
 * Made 3dmax work like Kasan wants it to.
 * 
 * Revision 2.27  1995/04/23  16:06:25  john
 * Moved rinvul into modem/null modem menu.
 * 
 * Revision 2.26  1995/04/12  13:39:26  john
 * Fixed bug with -lowmem not working.
 * 
 * Revision 2.25  1995/04/09  14:43:00  john
 * Made Dynamic sockets not print Msockets for help.
 * 
 * Revision 2.24  1995/04/07  16:11:33  john
 * Fixed problem with VFX display when using setup.
 * 
 * Revision 2.23  1995/04/06  15:40:51  john
 * Synced VFX with setup #'s.
 * 
 * Revision 2.22  1995/04/06  12:12:53  john
 * Fixed some bugs with 3dmax.
 * 
 * Revision 2.21  1995/03/30  16:36:51  mike
 * text localization.
 * 
 * Revision 2.20  1995/03/29  15:33:52  john
 * Added code to parse descent.net file.
 * 
 * Revision 2.19  1995/03/28  20:08:21  john
 * Took away alternate server thing.
 * 
 * Revision 2.18  1995/03/27  09:43:08  john
 * Added VR Settings in config file.
 * 
 * Revision 2.17  1995/03/23  19:02:21  john
 * Added descent.net file use.
 * 
 * Revision 2.16  1995/03/23  12:25:11  john
 * Moved IPX stuff into BIOS lib.
 * 
 * Revision 2.15  1995/03/21  16:52:34  john
 * Added 320x100.
 * 
 * Revision 2.14  1995/03/21  14:40:33  john
 * Ifdef'd out the NETWORK code.
 * 
 * Revision 2.13  1995/03/16  23:13:35  john
 * Fixed bug with piggy paging in bitmap not checking for disk
 * error, hence bogifying textures if you pull the CD out.
 * 
 * Revision 2.12  1995/03/16  21:45:22  john
 * Made all paged modes have incompatible menus!
 * 
 * Revision 2.11  1995/03/15  15:19:34  john
 * Took out code that changes to exe dir.
 * 
 * Revision 2.10  1995/03/15  14:33:37  john
 * Added code to force the Descent CD-rom in the drive.
 * 
 * Revision 2.9  1995/03/15  11:41:27  john
 * Better Saturn CD-ROM support.
 * 
 * Revision 2.8  1995/03/14  18:24:46  john
 * Force Destination Saturn to use CD-ROM drive.
 * 
 * Revision 2.7  1995/03/14  16:22:35  john
 * Added cdrom alternate directory stuff.
 * 
 * Revision 2.6  1995/03/13  15:17:19  john
 * Added alternate hogfile directory.
 * 
 * Revision 2.5  1995/03/10  13:05:35  john
 * Added code so that palette is correct for VFX1 helmets.
 * 
 * Revision 2.4  1995/03/07  15:12:43  john
 * Fixed VFX,3dmax support.
 * 
 * Revision 2.3  1995/03/07  14:19:35  mike
 * More destination saturn stuff.
 * 
 * Revision 2.2  1995/03/06  16:47:34  mike
 * destination saturn
 * 
 * Revision 2.1  1995/03/06  15:24:06  john
 * New screen techniques.
 * 
 * Revision 2.0  1995/02/27  11:31:29  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.295  1995/02/23  12:02:14  john
 * Made mono  windows smaller.
 * 
 * Revision 1.294  1995/02/16  17:35:00  john
 * Added code to allow dynamic socket changing.
 * 
 * Revision 1.293  1995/02/14  19:29:29  john
 * Locked down critical error handler.
 * 
 * Revision 1.292  1995/02/14  15:29:20  john
 * Added CR-LF to last line of menu help text.
 * 
 * Revision 1.291  1995/02/14  11:39:01  john
 * Added polled/bios joystick readers.
 * 
 * Revision 1.290  1995/02/13  20:35:03  john
 * Lintized
 * 
 * Revision 1.289  1995/02/11  16:20:02  john
 * Added code to make the default mission be the one last played.
 * 
 * Revision 1.288  1995/02/11  15:54:13  rob
 * changed cinvul to rinvul.
 * 
 * Revision 1.287  1995/02/11  14:48:43  rob
 * Added max of 314 seconds to control invul. times
 * 
 * Revision 1.286  1995/02/11  12:42:01  john
 * Added new song method, with FM bank switching..
 * 
 * Revision 1.285  1995/02/11  11:36:11  rob
 * Added cinvul option.
 * 
 * Revision 1.284  1995/02/10  16:07:45  matt
 * Took 'registered' out of printed info at startup
 * 
 * Revision 1.283  1995/02/09  22:00:59  john
 * Added i-glasses tracking.
 * 
 * Revision 1.282  1995/02/02  11:11:27  john
 * Added -nocyberman switch.
 * 
 * Revision 1.281  1995/02/01  16:35:14  john
 * Linted.
 * 
 * Revision 1.280  1995/01/31  02:04:25  matt
 * Fixed up cmdline help
 * 
 * Revision 1.279  1995/01/30  16:25:55  john
 * Put back in graphical screen at program end.
 * 
 * Revision 1.278  1995/01/28  17:05:50  matt
 * Changed imbedded copyright to use comma instead of hyphen
 * 
 * Revision 1.277  1995/01/28  15:57:26  john
 * Made joystick calibration be only when wrong detected in
 * menu or joystick axis changed.
 * 
 * Revision 1.276  1995/01/25  14:37:49  john
 * Made joystick only prompt for calibration once...
 * 
 * Revision 1.275  1995/01/24  18:21:00  john
 * Added Adam's text warning.
 * 
 * Revision 1.274  1995/01/22  15:57:20  john
 * Took out code that printed warning out as game exited.
 * 
 * Revision 1.273  1995/01/22  13:31:35  matt
 * Added load of mission 0, so there's always a default mission
 * 
 * Revision 1.272  1995/01/19  17:00:41  john
 * Made save game work between levels.
 * 
 * Revision 1.271  1995/01/18  11:47:57  adam
 * changed copyright notice
 * 
 * Revision 1.270  1995/01/15  13:42:42  john
 * Moved low_mem cutoff higher.
 * 
 * Revision 1.269  1995/01/12  18:53:50  john
 * Put ifdef EDITOR around the code that checked for 
 * a 800x600 mode, because this trashed some people's
 * computers (maybe) causing the mem allocation error in
 * mouse.c that many users reported.
 * 
 * Revision 1.268  1995/01/12  11:41:42  john
 * Added external control reading.
 * 
 * Revision 1.267  1995/01/06  10:26:55  john
 * Added -nodoscheck command line switch.
 * 
 * Revision 1.266  1995/01/05  16:59:30  yuan
 * Don't show orderform in editor version.
 * 
 * Revision 1.265  1994/12/28  15:33:51  john
 * Added -slowjoy option.
 * 
 * Revision 1.264  1994/12/15  16:44:15  matt
 * Added trademark notice
 * 
 * Revision 1.263  1994/12/14  20:13:59  john
 * Reduced physical mem requments to 2 MB.
 * 
 * Revision 1.262  1994/12/14  19:06:17  john
 * Lowered physical memory requments to 2 MB.
 * 
 * Revision 1.261  1994/12/14  09:41:29  allender
 * change to drive and directory (if needed) of command line invocation
 * so descent can be started from anywhere
 * 
 * Revision 1.260  1994/12/13  19:08:59  john
 * Updated memory requirements.
 * 
 * Revision 1.259  1994/12/13  17:30:33  john
 * Made the timer rate be changed right after initializing it.
 * 
 * Revision 1.258  1994/12/13  02:46:25  matt
 * Added imbedded copyright
 * 
 * Revision 1.257  1994/12/13  02:06:46  john
 * Added code to check stack used by descent... initial
 * check showed stack used 35k/50k, so we decided it wasn't
 * worth pursuing any more.
 * 
 * Revision 1.256  1994/12/11  23:17:54  john
 * Added -nomusic.
 * Added RealFrameTime.
 * Put in a pause when sound initialization error.
 * Made controlcen countdown and framerate use RealFrameTime.
 * 
 * Revision 1.255  1994/12/10  00:56:51  matt
 * Added -nomusic to command-line help
 * 
 * Revision 1.254  1994/12/08  11:55:11  john
 * Took out low memory print.
 * 
 * Revision 1.253  1994/12/08  11:51:00  john
 * Made strcpy only copy corect number of chars,.
 * 
 * Revision 1.252  1994/12/08  00:38:29  matt
 * Cleaned up banner messages
 * 
 * Revision 1.251  1994/12/07  19:14:52  matt
 * Cleaned up command-line options and command-line help message
 * 
 * Revision 1.250  1994/12/06  19:33:28  john
 * Fixed text of message to make more sense.
 * 
 * Revision 1.249  1994/12/06  16:30:55  john
 * Neatend mem message,..
 * 
 * Revision 1.248  1994/12/06  16:17:35  john
 * Added better mem checking/printing.
 * 
 * Revision 1.247  1994/12/06  14:14:37  john
 * Added code to set low mem based on memory.
 * 
 * Revision 1.246  1994/12/05  12:29:09  allender
 * removed ifdefs around -norun option
 * 
 * Revision 1.245  1994/12/05  00:03:30  matt
 * Added -norun option to exit after writing pig
 * 
 * Revision 1.244  1994/12/04  14:47:01  john
 * MAde the intro and menu be the same song.
 * 
 * Revision 1.243  1994/12/04  14:36:42  john
 * Added menu music.
 * 
 * Revision 1.242  1994/12/02  13:50:17  yuan
 * Localization.
 * 
 * Revision 1.241  1994/12/01  17:28:30  adam
 * added end-shareware stuff
 * 
 * Revision 1.240  1994/11/30  12:10:57  adam
 * added support for PCX titles/brief screens
 * 
 * Revision 1.239  1994/11/29  15:47:33  matt
 * Moved error_init to start of game, so error message prints last
 * 
 * Revision 1.238  1994/11/29  14:19:22  jasen
 * reduced dos mem requirments.
 * 
 * Revision 1.237  1994/11/29  03:46:35  john
 * Added joystick sensitivity; Added sound channels to detail menu.  Removed -maxchannels
 * command line arg.
 * 
 * Revision 1.236  1994/11/29  02:50:18  john
 * Increased the amount a joystick has to be off before
 * asking if they want to recalibrate their joystick.
 * 
 * Revision 1.235  1994/11/29  02:01:29  john
 * Corrected some of the Descent command line help items.
 * 
 * Revision 1.234  1994/11/29  01:39:56  john
 * Fixed minor bug with vfx_light help not wrapping correctly.
 * 
 * Revision 1.233  1994/11/28  21:34:17  john
 * Reduced dos mem rqment to 70k.
 * 
 * Revision 1.232  1994/11/28  21:20:38  john
 * First version with memory checking.
 * 
 * Revision 1.231  1994/11/28  20:06:21  rob
 * Removed old serial param command line options.
 * Added -noserial and -nonetwork to help listing.
 * 
 * Revision 1.230  1994/11/27  23:15:24  matt
 * Made changes for new mprintf calling convention
 * 
 * Revision 1.229  1994/11/27  20:50:51  matt
 * Don't set mem stuff if no debug
 * 
 * Revision 1.228  1994/11/27  18:46:21  matt
 * Cleaned up command-line switches a little
 * 
 * Revision 1.227  1994/11/21  17:48:00  matt
 * Added text to specifiy whether shareware or registered version
 * 
 * Revision 1.226  1994/11/21  14:44:20  john
 * Fixed some bugs with setting volumes even when -nosound was used. Duh!
 * 
 * Revision 1.225  1994/11/21  13:53:42  matt
 * Took out dos extender copyright
 * 
 * Revision 1.224  1994/11/21  09:46:54  john
 * Added -showmeminfo parameter.
 * 
 * Revision 1.223  1994/11/20  22:12:05  mike
 * Make some stuff dependent on SHAREWARE.
 * 
 * Revision 1.222  1994/11/20  21:14:09  john
 * Changed -serial to -noserial.  MAde a 1 sec delay 
 * before leaving title screen.  Clear keyboard buffer
 * before asking for player name.
 * 
 * Revision 1.221  1994/11/19  15:20:20  mike
 * rip out unused code and data
 * 
 * Revision 1.220  1994/11/17  19:14:29  adam
 * prevented order screen from coming up when -notitles is used
 * 
 * Revision 1.219  1994/11/16  11:34:39  john
 * Added -nottitle switch.
 * 
 * Revision 1.218  1994/11/16  10:05:53  john
 * Added verbose messages.
 * 
 * Revision 1.217  1994/11/15  20:12:34  john
 * Added back in inferno and parallax screens.
 * 
 * Revision 1.216  1994/11/15  18:35:30  john
 * Added verbose setting.
 * 
 * Revision 1.215  1994/11/15  17:47:44  john
 * Added ordering info screen.
 * 
 * Revision 1.214  1994/11/15  08:57:44  john
 * Added MS-DOS version checking and -nonetwork option.
 * 
 * Revision 1.213  1994/11/15  08:34:32  john
 * Added better error messages for IPX init.
 * 
 * Revision 1.212  1994/11/14  20:14:18  john
 * Fixed some warnings.
 * 
 * Revision 1.211  1994/11/14  19:50:49  john
 * Added joystick cal values to descent.cfg.
 * 
 * Revision 1.210  1994/11/14  17:56:44  allender
 * make call to ReadConfigFile at startup
 * 
 * Revision 1.209  1994/11/14  11:41:55  john
 * Fixed bug with editor/game sequencing.
 * 
 * Revision 1.208  1994/11/13  17:05:11  john
 * Made the callsign entry be a list box and gave the ability
 * to delete players.
 * 
 * Revision 1.207  1994/11/13  15:39:22  john
 * Added critical error handler to game.  Took out -editor command line
 * option because it didn't work anymore and wasn't worth fixing.  Made scores
 * not use MINER enviroment variable on release version, and made scores
 * not print an error if there is no descent.hi.
 * 
 * Revision 1.206  1994/11/10  20:53:29  john
 * Used new sound install parameters.
 * 
 * Revision 1.205  1994/11/10  11:07:52  mike
 * Set default detail level.
 * 
 * Revision 1.204  1994/11/09  13:45:43  matt
 * Made -? work again for help
 * 
 * Revision 1.203  1994/11/09  10:55:58  matt
 * Cleaned up initialization for editor -> game transitions
 * 
 * Revision 1.202  1994/11/07  21:35:47  matt
 * Use new function iff_read_into_bitmap()
 * 
 * Revision 1.201  1994/11/05  17:22:16  john
 * Fixed lots of sequencing problems with newdemo stuff.
 * 
 * Revision 1.200  1994/11/05  14:05:44  john
 * Fixed fade transitions between all screens by making gr_palette_fade_in and out keep
 * track of whether the palette is faded in or not.  Then, wherever the code needs to fade out,
 * it just calls gr_palette_fade_out and it will fade out if it isn't already.  The same with fade_in.
 * This eliminates the need for all the flags like Menu_fade_out, game_fade_in palette, etc.
 * 
 * Revision 1.199  1994/11/04  14:36:30  allender
 * change Auto_demo meaning to mean autostart from menu only.  Use
 * FindArgs when searching for AutoDemo from command line.  also,
 * set N_Players to 1 when starting in editor mode.
 * 
 * Revision 1.198  1994/11/02  11:59:49  john
 * Moved menu out of game into inferno main loop.
 * 
 * Revision 1.197  1994/11/01  17:57:39  mike
 * -noscreens option to bypass all screens.
 * 
 * Revision 1.196  1994/10/28  15:42:34  allender
 * don't register player if Autodemo is on
 * 
 * Revision 1.195  1994/10/28  10:58:01  matt
 * Added copyright notice for DOS4GW
 * 
 * Revision 1.194  1994/10/20  21:26:48  matt
 * Took out old serial name/number code, and put up message if this
 * is a marked version.
 * 
 * Revision 1.193  1994/10/19  09:52:14  allender
 * Print out who descent.exe belongs to if descent.exe is stamped.
 * 
 * Revision 1.192  1994/10/18  16:43:05  allender
 * Added check for identifier stamp and time after which descent will
 * no longer run.
 * 
 * Revision 1.191  1994/10/17  13:07:17  john
 * Moved the descent.cfg info into the player config file.
 * 
 * Revision 1.190  1994/10/04  10:26:31  matt
 * Support new menu fade in
 * 
 * Revision 1.189  1994/10/03  22:58:46  matt
 * Changed some values of game_mode
 * 
 * Revision 1.188  1994/10/03  18:55:39  rob
 * Changed defaults for com port settings.
 * 
 * Revision 1.187  1994/10/03  13:34:47  matt
 * Added new (and hopefully better) game sequencing functions
 * 
 * Revision 1.186  1994/09/30  12:37:28  john
 * Added midi,digi volume to configuration.
 * 
 * Revision 1.185  1994/09/30  10:08:48  john
 * Changed sound stuff... made it so the reseting card doesn't hang, 
 * made volume change only if sound is installed.
 * 
 * Revision 1.184  1994/09/28  17:25:00  matt
 * Added first draft of game save/load system
 * 
 * Revision 1.183  1994/09/28  16:18:23  john
 * Added capability to play midi song.
 * 
 * Revision 1.182  1994/09/28  11:31:18  john
 * Made text output unbuffered.
 * 
 * Revision 1.181  1994/09/27  19:23:44  john
 * Added -nojoystick and -nomouse
 * 
 * Revision 1.180  1994/09/24  16:55:29  rob
 * No longer open COM port immediately upon program start.
 * No longer set Network_active is serial_active is set.
 * 
 * Revision 1.179  1994/09/24  14:16:30  mike
 * Support new game mode constants.
 * 
 * Revision 1.178  1994/09/22  17:52:31  rob
 * Added Findargs hooks for -serial, -speed, and -com.
 * 
 * Revision 1.177  1994/09/22  16:14:11  john
 * Redid intro sequecing.
 * 
 * Revision 1.176  1994/09/21  16:32:58  john
 * Made mouse and keyboard init after bm_init. Why?
 * Because it seems to work better under virtual 
 * memory.
 * 
 * Revision 1.175  1994/09/21  16:27:52  john
 * Added mouse_init
 * 
 * Revision 1.174  1994/09/20  15:14:10  matt
 * New message for new VFX switches
 * 
 * Revision 1.173  1994/09/16  16:14:27  john
 * Added acrade sequencing.
 * 
 * Revision 1.172  1994/09/16  11:49:52  john
 * Added first version of arcade joystick support;
 * Also fixed some bugs in kconfig.c, such as reading non-present
 * joysticks, which killed frame rate, and not reading key_down_time
 * when in slide mode or bank mode.
 * 
 * Revision 1.171  1994/09/15  16:11:35  john
 * Added support for VFX1 head tracking. Fixed bug with memory over-
 * write when using stereo mode.
 * 
 * Revision 1.170  1994/09/12  19:38:23  john
 * Made some stuff that prints to the DOS screen go to the
 * mono instead, since it really is debugging info.
 * 
 * Revision 1.169  1994/08/29  21:18:28  john
 * First version of new keyboard/oystick remapping stuff.
 * 
 * Revision 1.168  1994/08/26  13:02:00  john
 * Put high score system in.
 * 
 * Revision 1.167  1994/08/24  19:00:23  john
 * Changed key_down_time to return fixed seconds instead of
 * milliseconds.
 * 
 * Revision 1.166  1994/08/18  16:24:20  john
 * changed socket to channel in text.
 * 
 * Revision 1.165  1994/08/18  16:16:51  john
 * Added support for different sockets.
 * 
 * Revision 1.164  1994/08/18  10:47:53  john
 * *** empty log message ***
 * 
 * Revision 1.163  1994/08/12  09:15:54  john
 * *** empty log message ***
 * 
 * Revision 1.162  1994/08/12  03:11:19  john
 * Made network be default off; Moved network options into
 * main menu.  Made starting net game check that mines are the
 * same.
 * 
 * Revision 1.161  1994/08/10  19:57:05  john
 * Changed font stuff; Took out old menu; messed up lots of
 * other stuff like game sequencing messages, etc.
 * 
 * Revision 1.160  1994/08/05  16:30:23  john
 * Added capability to turn off network.
 * 
 * Revision 1.159  1994/08/04  19:42:51  matt
 * Moved serial number & name (and version name) from inferno.c to inferno.ini
 * 
 * Revision 1.158  1994/08/03  10:30:23  matt
 * Change cybermaxx switches, updated command-line help, and added serial number system
 * 
 * Revision 1.157  1994/07/29  18:30:10  matt
 * New parms (lack of parms, actually) for g3_init()
 * 
 * Revision 1.156  1994/07/24  00:39:25  matt
 * Added more text to TEX file; make NewGame() take a start level; made game
 * load/save menus use open/close window funcs.
 * 
 * Revision 1.155  1994/07/21  21:31:27  john
 * First cheapo version of VictorMaxx tracking.
 * 
 * Revision 1.154  1994/07/21  18:15:34  matt
 * Ripped out a bunch of unused stuff
 * 
 * Revision 1.153  1994/07/21  17:59:10  matt
 * Cleaned up initial mode game/editor code
 * 
 * Revision 1.152  1994/07/21  13:11:19  matt
 * Ripped out remants of old demo system, and added demo only system that
 * disables object movement and game options from menu.
 * 
 * Revision 1.151  1994/07/20  15:58:27  john
 * First installment of ipx stuff.
 * 
 * Revision 1.150  1994/07/15  16:04:24  matt
 * Changed comment for milestone 3 version
 * 
 * Revision 1.149  1994/07/15  13:59:24  matt
 * Fixed stupid mistake I make in the last revision
 * 
 * Revision 1.148  1994/07/15  13:20:15  matt
 * Updated comand-line help
 * 
 * Revision 1.147  1994/07/14  23:29:43  matt
 * Open two mono debug messages, one for errors & one for spew
 * 
 * Revision 1.146  1994/07/09  22:48:05  matt
 * Added localizable text
 * 
 * Revision 1.145  1994/07/02  13:49:47  matt
 * Cleaned up includes
 * 
 * Revision 1.144  1994/06/30  20:04:43  john
 * Added -joydef support.
 * 
 * Revision 1.143  1994/06/24  17:01:44  john
 * Add VFX support; Took Game Sequencing, like EndGame and stuff and
 * took it out of game.c and into gameseq.c
 * 
 */

#ifdef RCS
static char rcsid[] = "$Id$";
#endif

#ifdef __GNUC__
static char copyright[] = "DESCENT   COPYRIGHT (C) 1994,1995 PARALLAX SOFTWARE CORPORATION";
static char *__reference[2]={copyright,(char *)__reference};
#endif


#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#ifdef __MSDOS__
#include <time.h>
#endif
//added on 1/11/99 by DPH for win32
#ifdef __WINDOWS__
#include "winhdr.h"
#endif
//end this section addition - dph
//added on 12/14/98 by Matt Mueller - override res in d1x.ini with command line args
#include <limits.h>
//end addition -MM
#if defined(_MSC_VER) && defined(_DEBUG)
#include <crtdbg.h>
#endif


#include "gr.h"
#include "3d.h"
#include "inferno.h"
#include "error.h"
#include "game.h"
#include "segment.h"		//for Side_to_verts
#include "u_mem.h"
#include "texmerge.h"
#include "menu.h"
#include "digi.h"
#include "args.h"
#include "titles.h"
#include "text.h"
#include "ipx.h"
#include "newdemo.h"
#include "network.h"
#include "modem.h"
#include "gamefont.h"
#include "kconfig.h"
#include "newmenu.h"
#include "desc_id.h"
#include "config.h"
#include "joydefs.h"
#include "multi.h"
#include "songs.h"
#include "cfile.h"
#include "gameseq.h"
#include "timer.h"
#include "joy.h"
#include "key.h"
#include "mono.h"
#include "palette.h"
#include "bm.h"
#include "screens.h"
#include "arch.h"
#include "hudmsg.h"
#include "playsave.h"
#include "d_io.h"

//added on 9/30/98 by Matt Mueller for selectable automap modes
#include "automap.h"
//end addition -MM

//added on 11/01/98 by Matt Mueller
#include "hudlog.h"
//end addition -MM
//added on 11/15/98 by Victor Racels to ease cd stuff
#include "cdplay.h"
//end this section addition - VR

//added on 2/3/99 by Victor Rachels to add readbans
#include "ban.h"
//end this section addition - VR

//added 02/07/99 Matt Mueller - for -hud command line
#include "gauges.h"
//end addition -MM

//added 2/9/99 by Victor Rachels for pingstats
#include "pingstat.h"
//end this section addition - VR

//added 3/12/99 by Victor Rachels for faster sporb turning
#include "physics.h"
//end this section addition - VR

//added 6/15/99 by Owen Evans to fix compile warnings
#include "strutil.h"
//end section -OE

//added 11/13/99 by Victor Rachels for alternate sounds
#include "altsound.h"
//end this section addition - VR

#include "../texmap/scanline.h" //for select_tmap -MM

#include "d_delay.h" //for SUPPORTS_NICEFPS

#ifdef __MSDOS__
#include <conio.h>
#else
#define getch() getchar()
#endif

#ifdef EDITOR
#include "editor/editor.h"
#include "editor/kdefs.h"
#endif

#include "vers_id.h"

#ifdef QUICKSTART
#include "playsave.h"
#endif
#ifdef SCRIPT
#include "script.h"
#endif

void check_joystick_calibration();
void show_order_form();

static const char desc_id_checksum_str[] = DESC_ID_CHKSUM;
char desc_id_exit_num = 0;

int Function_mode=FMODE_MENU;		//game or editor?
int Screen_mode=-1;					//game screen or editor screen?

int descent_critical_error = 0;
unsigned int descent_critical_deverror = 0;
unsigned int descent_critical_errcode = 0;

u_int32_t menu_screen_mode=SM(320,200); // mode used for menus -- jb
int menu_use_game_res=1;

#ifdef EDITOR
int Inferno_is_800x600_available = 0;
#endif

int init_graphics()
{
#ifdef __MSDOS__
	int result;
	result=gr_check_mode(SM(320,200));

#ifdef EDITOR
	if ( result==0 )	
		result=gr_check_mode(SM(800,600));
#endif

	switch( result )	{
		case  0:		//Mode set OK
#ifdef EDITOR
						Inferno_is_800x600_available = 1;
#endif
						break;
		case  1:		//No VGA adapter installed
						printf("%s\n", TXT_REQUIRES_VGA );
						return 1;
		case 10:		//Error allocating selector for A0000h
						printf( "%s\n",TXT_ERROR_SELECTOR );
						return 1;
		case 11:		//Not a valid mode support by gr.lib
						printf( "%s\n", TXT_ERROR_GRAPHICS );
						return 1;
#ifdef EDITOR
		case  3:		//Monitor doesn't support that VESA mode.
		case  4:		//Video card doesn't support that VESA mode.

						printf( "Your VESA driver or video hardware doesn't support 800x600 256-color mode.\n" );
						break;
		case  5:		//No VESA driver found.
						printf( "No VESA driver detected.\n" );
						break;
		case  2:		//Program doesn't support this VESA granularity
		case  6:		//Bad Status after VESA call/
		case  7:		//Not enough DOS memory to call VESA functions.
                case  8:                //Error using DPMI.
		case  9:		//Error setting logical line width.
		default:
						printf( "Error %d using 800x600 256-color VESA mode.\n", result );
						break;
#endif
	}

	#ifdef EDITOR
	if (!Inferno_is_800x600_available)	{
		printf( "The editor will not be available, press any key to start game...\n" );
		Function_mode = FMODE_MENU;
		getch();
	}
	#endif
#endif
	return 0;
}

void show_cmdline_help() {
	printf( "%s\n", TXT_COMMAND_LINE_0 );
#ifdef __MSDOS__
        printf( "  -<X>x<Y>       %s\n", "Change screen resolution. Options:");
        printf( "                    320x100;320x200;320x240;320x400;640x400;640x480;800x600;1024x768\n");
#else
        printf( "  -<X>x<Y>       %s\n", "Change screen resolution to <X> by <Y>");
#endif
	printf( "%s\n", TXT_COMMAND_LINE_5 );
	printf( "%s\n", TXT_COMMAND_LINE_6 );
	printf( "%s\n", TXT_COMMAND_LINE_7 );
	printf( "%s\n", TXT_COMMAND_LINE_8 );

	printf( "\n%s\n",TXT_PRESS_ANY_KEY3);
	getch();
	printf( "\n" );
	printf( "%s\n", TXT_COMMAND_LINE_9);
	printf( "%s\n", TXT_COMMAND_LINE_10);
	printf( "%s\n", TXT_COMMAND_LINE_11);
	printf( "%s\n", TXT_COMMAND_LINE_12);
	printf( "%s\n", TXT_COMMAND_LINE_13);
	printf( "%s\n", TXT_COMMAND_LINE_14);
	printf( "%s\n", TXT_COMMAND_LINE_15);
	printf( "%s\n", TXT_COMMAND_LINE_16);
	printf( "%s\n", TXT_COMMAND_LINE_17);
	printf( "%s\n", TXT_COMMAND_LINE_18);
	//printf( "  -DynamicSockets %s\n", TXT_SOCKET);
	#ifdef __MSDOS__
	printf( "  -NoFileCheck    %s\n", TXT_NOFILECHECK);
	#endif
	printf( "  -GamePort       %s\n", "Use Colorado Spectrum's Notebook Gameport" );
//moved ifdef on 9/30/98 by Matt Mueller for linux doesn't use double buffering ever, so this is redundant
	#ifdef __MSDOS__
	printf( "  -NoDoubleBuffer %s\n", "Use only one page of video memory" );
//end change -MM
	printf( "  -JoyNice        %s\n", "Joystick poller allows interrupts to occur" );
	#endif
	printf( "\n%s\n",TXT_PRESS_ANY_KEY3);
	getch();
	printf( "\n");
        printf( " D1X options:\n");
        printf( "  -mprofile <f>   %s\n", "Use multi game profile <f>");
        printf( "  -missiondir <d> %s\n", "Set alternate mission dir to <d>");
        printf( "  -mission <f>    %s\n", "Use mission <f> to start game");
        printf( "  -startnetgame   %s\n", "Start a network game immediately");
        printf( "  -joinnetgame    %s\n", "Skip to join menu screen");
        printf( "  -nobans         %s\n", "Don't use saved bans");
        printf( "  -savebans       %s\n", "Automatically save new bans");
        printf( "  -pingstats      %s\n", "Show pingstats on hud");
	printf( "  -noredundancy   %s\n", "Do not send messages when picking up redundant items in multi");
	printf( "  -playermessages %s\n", "View only messages from other players in multi");
        printf( "  -shortpackets   %s\n", "Set shortpackets to default as on");
        printf( "  -pps <n>        %s\n", "Set packets per second to default at <n>");
        printf( "  -ackmsg         %s\n", "Turn on packet acknowledgement debug msgs");
        printf( "  -pilot <pilot>  %s\n", "Select this pilot automatically");
	printf( "  -cockpit <n>    %s\n", "Set initial cockpit");
	printf( "                  %s\n", "0=full 2=status bar 3=full screen");

	printf( "\n%s\n",TXT_PRESS_ANY_KEY3);
	getch();
        printf( "\n\n");
//added 02/07/99 Matt Mueller
        printf( "  -hud <h>        %s\n", "Set hud mode.  0=normal 1-3=new");
//end addition -MM
	printf( "  -fps            %s\n", "Enable FPS indicator by default");
#ifdef OGL //currently only does anything on ogl build, so don't advertise othewise.
	printf( "  -renderstats    %s\n", "Enable renderstats info by default");
#endif
	printf( "  -demo <f>       %s\n", "Start playing demo <f>");
        printf( "  -maxfps <n>     %s\n", "Set maximum framerate (1-100)");
        printf( "  -notitles       %s\n", "Do not show titlescreens on startup");
        printf( "  -ini <file>     %s\n", "option file (alternate to command line)");
        printf( "  -handicap <n>   %s\n", "Start game with <n> shields. Must be < 100 for multi");
        printf( "  -hudlog         %s\n", "Start hudlog immediatly");

#ifdef SUPPORTS_NICEFPS
        printf( "  -nicefps        %s\n", "Free cpu while waiting for next frame");
        printf( "  -niceautomap    %s\n", "Free cpu while doing automap");
#endif
        printf( "  -automap<X>x<Y> %s\n", "Set automap resolution to <X> by <Y>");
        printf( "  -automap_gameres %s\n", "Set automap to use the same resolution as in game");
        printf( "  -menu<X>x<Y>    %s\n", "Set menu resolution to <X> by <Y>");
        printf( "  -menu_gameres   %s\n", "Set menus to use the same resolution as in game");
        printf( "  -rearviewtime t %s\n", "time holding rearview key to use toggle mode (default 0.25 seconds)");

	printf( "\n%s\n",TXT_PRESS_ANY_KEY3);
	getch();
        printf( "\n\n");

//added/edited on 11/01/98 by Matthew Mueller
        printf( "  -hudlog_multi   %s\n", "Start hudlog upon entering multiplayer games");
        printf( "  -hudlogdir <d>  %s\n", "Log hud messages in directory <d>");
        printf( "  -hudlogstdout   %s\n", "Log hud messages to stdout");
//end edit -MM
        printf( "  -hudlines <l>   %s\n", "Number of hud messages to show");
        printf( "  -msgcolorlevel <c> %s\n", "Level of colorization for hud messages (0-3)");

//added on 01/3/99 by Matt Mueller
        printf( "  -nocdaudio      %s\n", "disable cd audio");
//end addition -MM
        printf( "  -playlist \"...\" %s\n", "Set the cd audio playlist to tracks \"a b c ... f g\"");

        printf( "  -fastext        %s\n", "Fast external control");
        printf( "  -font320 <f>    %s\n", "font to use for res 320x* and above (default font3-1.fnt)");
        printf( "  -font640 <f>    %s\n", "font to use for res 640x* and above (default pc6x8.fnt)");
        printf( "  -font800 <f>    %s\n", "font to use for res 800x* and above");
        printf( "  -font1024 <f>    %s\n", "font to use for res 1024x* and above (default pc8x16.fnt)");
		printf( "  -tmap <t>       %s\n","select texmapper to use (c,fp,i386,pent,ppro)");
        printf( "\n\n");

	printf( "\n%s\n",TXT_PRESS_ANY_KEY3);
	getch();
        printf( " System options:\n");

#ifdef __MSDOS__
        printf( "  -joy209         %s\n", "Use alternate port 209 for joystick");
#endif
#ifdef GR_SUPPORTS_FULLSCREEN_TOGGLE 
        printf( "  -fullscreen     %s\n", "Use fullscreen mode if available");
#endif
#ifdef OGL
        printf( "  -gl_texmaxfilt <f> %s\n","set GL_TEXTURE_MAX_FILTER (see readme.d1x)");
        printf( "  -gl_texminfilt <f> %s\n","set GL_TEXTURE_MIN_FILTER (see readme.d1x)");
        printf( "  -gl_mipmap      %s\n","set gl texture filters to \"standard\" (bilinear) mipmapping");
        printf( "  -gl_trilinear   %s\n","set gl texture filters to trilinear mipmapping");
        printf( "  -gl_simple      %s\n","set gl texture filters to gl_nearest for \"original\" look. (default)");
        printf( "  -gl_anisotropy <f> %s\n","set maximum degree of anisotropy to <f>");
        printf( "  -gl_alttexmerge %s\n","use new texmerge, usually uses less ram (default)");
        printf( "  -gl_stdtexmerge %s\n","use old texmerge, uses more ram, but _might_ be a bit faster");
        printf( "  -gl_voodoo      %s\n","force fullscreen mode only");
        printf( "  -gl_16bittextures %s\n","attempt to use 16bit textures");
        printf( "  -gl_reticle <r> %s\n","use OGL reticle 0=never 1=above 320x* 2=always");
#ifdef OGL_RUNTIME_LOAD
        printf( "  -gl_library <l> %s\n","use alternate opengl library");
#endif
#ifdef __WINDOWS__
        printf( "  -gl_refresh <r> %s\n","set refresh rate (in fullscreen mode)");
#endif
#endif
#ifdef SDL_VIDEO
        printf( "  -nosdlvidmodecheck %s\n", "Some X servers don't like checking vidmode first, so just switch");
#endif
#ifdef SUPPORTS_NET_IP
        printf( "  -ip_nogetmyaddr %s\n","prevent autodetection of local ip address");
        printf( "  -ip_myaddr <a>  %s\n","use <a> as local ip address");
        printf( "  -ip_bind_addr <a> %s\n","bind to <a> instead of INADDR_ANY");
        printf( "  -ip_baseport <p> %s\n","use <p> as offset from normal port (allows multiple instances of d1x to be run on a single computer)");
#endif
#ifdef __LINUX__
//added 02/06/99 Matthew Mueller
        printf( "  -serialdevice <s> %s\n", "Set serial/modem device to <s>");
//end addition -MM
//added 03/07/99 Matthew Mueller
        printf( "  -serialread <r>   %s\n", "Set serial/modem to read from <r>");
//end addition -MM
#endif
        printf( "\n");
}

extern fix fixed_frametime;
extern int framerate_on;

extern void vfx_set_palette_sub(ubyte *);

int Inferno_verbose = 0;

//added on 11/18/98 by Victor Rachels to add -mission and -startgame
int start_net_immediately = 0;
int start_with_mission = 0;
char *start_with_mission_name;
//end this section addition

int main(int argc,char **argv);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	main(__argc, __argv);
}

int main(int argc,char **argv)
//end this section addition - dph
{
	int i,t;
	char start_demo[13];

	error_init(NULL);

	setbuf(stdout, NULL);	// unbuffered output via printf
		
	InitArgs( argc,argv );
//end this section addition - dph

	if ( FindArg( "-verbose" ) )
		Inferno_verbose = 1;

	#ifndef NDEBUG
        if ( FindArg( "-showmeminfo" ) )
                show_mem_info = 1;              // Make memory statistics show
        #endif

	// Things to initialize before anything else
	arch_init_start();

	load_text();

//	set_exit_message("\n\n%s", TXT_THANKS);

	printf(DESCENT_VERSION "\n"
	       "This is a MODIFIED version of DESCENT which is NOT supported by Parallax or\n"
	       "Interplay. Use at your own risk!\n");
	printf("Based on: DESCENT   %s\n", VERSION_NAME);
	printf("%s\n%s\n",TXT_COPYRIGHT,TXT_TRADEMARK);

	//edited 02/07/99 Matt Mueller - added "--help"
	if (FindArg( "-?" ) || FindArg( "-help" ) || FindArg( "--help" ) || FindArg( "?" ) ) {
	//end edit -MM
		show_cmdline_help();
                set_exit_message("");
		return 0;
	}

        printf("\n%s\n", TXT_HELP);

//added on 11/13/99 by Victor Rachels for new sounds
        if ((t = FindArg( "-altsounds" )))
         {
           load_alt_sounds(Args[t+1]);
           atexit(free_alt_sounds);
         }
//end this section addition - VR

	if ((t = FindArg( "-missiondir" )))
		cfile_use_alternate_hogdir(Args[t+1]);
        else
                cfile_use_alternate_hogdir("");

	if ((t=FindArg("-tmap"))){
		select_tmap(Args[t+1]);
	}else
		select_tmap(NULL);

	//added 8/6/98 by Victor Rachels to have init cockpit
	if ((t=FindArg("-cockpit"))){
                t=atoi(Args[t+1]);
                if(t==0 || t==2 || t==3)
                 Cockpit_mode = t;
        }
        //end this section - Victor Rachels

//added 02/07/99 Matt Mueller
	if ((t=FindArg("-hud"))){
		t=atoi(Args[t+1]);
		if(t>=0 && t<GAUGE_HUD_NUMMODES)
                 Gauge_hud_mode = t;
	}
//end addition -MM
	if ((t=FindArg("-rearviewtime"))){
		float f=atof(Args[t+1]);
		Rear_view_leave_time=f*f1_0;
	}
	mprintf((0,"Rear_view_leave_time=0x%x (%f sec)\n",Rear_view_leave_time,Rear_view_leave_time/(float)f1_0));
        #ifdef NETWORK
         if (FindArg("-pingstats"))
          ping_stats_on = 1;
        #endif

	
	if ((t=FindArg("-msgcolorlevel"))){
		extern int gr_message_color_level;
		t=atoi(Args[t+1]);
		if(t>=0 && t<=3)
                gr_message_color_level = t;
	}
		 
	if ((t=FindArg("-hudlines"))){
		t=atoi(Args[t+1]);
		if(t>0 && t<=HUD_MAX_NUM)
                HUD_max_num_disp = t;
	}

        //added/edited on 11/01/98 by Matt Mueller
	//added on 10/04/98 by Matt Mueller to allow hud message logging
        if (FindArg("-hudlog_multi"))
         HUD_log_multi_autostart = 1;
        if (FindArg("-hudlogstdout"))
         HUD_log_messages = 1;
        if ((t=FindArg("-hudlogdir")))
         hud_log_setdir(Args[t+1]);
        if (FindArg("-hudlog"))
         HUD_log_autostart = 1;
	//end addition -MM
	//added 8/5/98 by Victor Rachels to add global variables to noredundancy/playermessages
        //look in hud.c for usage
        if (FindArg("-noredundancy"))
            MSG_Noredundancy = 1;
        if (FindArg("-playermessages"))
            MSG_Playermessages = 1;
        //end edit - Victor Rachels

        //added 11/9/98 by Victor Rachels to add handicapping
        if ((t = FindArg( "-handicap" )))
         {
           t = i2f(atoi(Args[t+1]));
            if(t < F1_0)
             t= F1_0;
            else if (t > F1_0*200)
             t = F1_0*200;
           handicap=t;
         }
        

        //added 8/18/98 by Victor Rachels to add maximum framerate
        //added/edited 8/18/98 by Victor Rachels to set maximum fps <= 100
        if ((t = FindArg( "-maxfps" ))) {
                t=atoi(Args[t+1]);
                 if (t>0&&t<=80)
                  maxfps=t;
        }
        //end addition - Victor Rachels

        //added on 11/18/98 by Victor Rachels to add -mission
        if((t=FindArg( "-mission" )))
         {
           start_with_mission = 1;
           sprintf(start_with_mission_name,"%s",Args[t+1]);
           removeext(start_with_mission_name,start_with_mission_name);
            if(strlen(start_with_mission_name)>8)
             start_with_mission_name[9]=0;
         }
        //end this section addition - VR
        //added on 11/18/98 by Victor Rachels to add -startgame
        #ifdef NETWORK
        if(FindArg( "-startnetgame" ))
         start_net_immediately = 1;
        if(FindArg( "-joinnetgame" ))
         start_net_immediately = 2;
        #endif
        //end this section addition - VR

        //added on 3/12/99 by Victor Rachels for faster sporb turn
        if(FindArg( "-fastext" ))
         extfaster=1;
        //end this section addition - VR

        //added on 10/15/98 by Victor Rachels to add ack debug msgs
        #ifdef NETWORK
        if(FindArg( "-ackmsg" ))
         ackdebugmsg = 1;
        #endif
        //end this section addition

        //added on 2/3/99 by Victor Rachels to read in bans
        #ifdef NETWORK
        readbans();
        #endif
        //end this section addition

#ifdef SUPPORTS_NICEFPS
        if ( FindArg( "-nicefps"))
                use_nice_fps = 1;
		if (FindArg( "-niceautomap"))
			nice_automap=1;
#endif

	if ( FindArg( "-fps" ))
		framerate_on = 1;

	if ( FindArg( "-renderstats" ))
		gr_renderstats = 1;

	if ((t = FindArg( "-demo" ))) {
		strncpy(start_demo, Args[t + 1], 12);
		start_demo[12] = 0;
		Auto_demo = 1;
	} else
		start_demo[0] = 0;

	if ( FindArg( "-autodemo" ))
		Auto_demo = 1;

	#ifndef RELEASE
	if ( FindArg( "-noscreens" ) )
		Skip_briefing_screens = 1;
	#endif

	if (Inferno_verbose) printf ("%s", TXT_VERBOSE_1);
        ReadConfigFile();

	arch_init();
        cd_init();

	if (init_graphics()) return 1;

	//------------ Init sound ---------------
	if (!FindArg( "-nosound" ))	{
		if (digi_init())	{
			#ifdef ALLEGRO
			printf( "\nFailure initializing sound: %s\n", allegro_error);
                        printf( "Make sure your soundcard is installed and not in use. \nIf the problem persists, check your allegro.cfg.\n");
			#else
			printf( "\nFailure initializing sound.\n");
			#endif
#ifndef __linux__
                        key_getch();
#endif
		}
	} else {
		if (Inferno_verbose) printf( "\n%s",TXT_SOUND_DISABLED );
	}

#ifdef NETWORK

	if (!FindArg("-noserial"))
	{
		serial_active = 1;
	}
	else 
	{
		serial_active = 0;
	}
#endif

	{
		int screen_width = 640;
		int screen_height = 480;
                int vr_mode = VR_NONE;
		int screen_compatible = 0;
		int use_double_buffer = 1;

		if (FindResArg("", &screen_width, &screen_height)) {
			if (screen_width==320 && screen_height==200){
				screen_compatible = 1;
				use_double_buffer = 0;
			}
			else if (screen_width==320 && screen_height==100){
				use_double_buffer = 0;
			}
			
			if (Inferno_verbose)
				printf( "Using %ix%i ...\n", screen_width, screen_height);
		}

		
//added ifdefs on 9/30/98 by Matt Mueller to fix high res in linux
#ifdef __MSDOS__
		if ( FindArg( "-nodoublebuffer" ) )	{
			if (Inferno_verbose) printf( "Double-buffering disabled...\n" );
#endif
			use_double_buffer = 0;
#ifdef __MSDOS__
                }
#endif
//end addition -MM

                //added 3/24/99 by Owen Evans for screen res changing
                Game_screen_mode = SM(screen_width, screen_height);
                //end added -OE
                game_init_render_buffers(Game_screen_mode, screen_width, screen_height, use_double_buffer, vr_mode, screen_compatible);
                
	}
	{
//added/edited on 12/14/98 by Matt Mueller - override res in d1x.ini with command line args
		int i, argnum=INT_MAX, w, h;

//added on 9/30/98 by Matt Mueller for selectable automap modes - edited 11/21/99 whee, more fun with defines. - edited 03/31/02 to use new FindResArg.
#define SMODE(V,VV,VG) if ( (i=FindResArg(#V, &w, &h)) && (i<argnum))  {argnum=i; VV = SM( w , h );VG=0;}
#define SMODE_GR(V,VG) if ((i=FindArg("-" #V "_gameres"))){if (i<argnum) VG=1;}
#define SMODE_PRINT(V,VV,VG) if (Inferno_verbose) { if (VG) printf( #V " using game resolution ...\n"); else printf( #V " using %ix%i ...\n",SM_W(VV),SM_H(VV) ); }
//aren't #defines great? :)
//end addition/edit -MM
#define S_MODE(V,VV,VG) argnum=INT_MAX;SMODE(V,VV,VG);SMODE_GR(V,VG);SMODE_PRINT(V,VV,VG);

		
		S_MODE(automap,automap_mode,automap_use_game_res);
		S_MODE(menu,menu_screen_mode,menu_use_game_res);
	 }
//end addition -MM
	
#ifdef NETWORK
	control_invul_time = 0;
#endif

	i = FindArg( "-xcontrol" );
	if ( i > 0 )	{
		kconfig_init_external_controls( strtol(Args[i+1], NULL, 0), strtol(Args[i+2], NULL, 0) );
	}

	if (Inferno_verbose) printf( "\n%s\n\n", TXT_INITIALIZING_GRAPHICS);
	if ((t=gr_init( SM_ORIGINAL ))!=0)
		Error(TXT_CANT_INIT_GFX,t);
	// Load the palette stuff. Returns non-zero if error.
	mprintf( (0, "Going into graphics mode..." ));
	gr_set_mode(MENU_SCREEN_MODE);
	mprintf( (0, "\nInitializing palette system..." ));
	gr_use_palette_table( "PALETTE.256" );
	mprintf( (0, "\nInitializing font system..." ));
	gamefont_init();	// must load after palette data loaded.
	songs_play_song( SONG_TITLE, 1 );

#ifndef QUICKSTART
//added/changed on 8/12/98 by Victor Rachels for registered users
#ifndef SHAREWARE
//end change - Victor Rachels
	if ( !FindArg( "-notitles" ) ) 
#endif
	{	//NOTE LINK TO ABOVE!
		show_title_screen( "iplogo1.pcx", 1 );
		show_title_screen( "logo.pcx", 1 );
	}
#endif

	show_title_screen( "descent.pcx", 2 );

#ifdef SHAREWARE
	bm_init_use_tbl();
#else
#ifdef EDITOR
	if ( !FindArg("-nobm") )
		bm_init_use_tbl();
	else
		bm_init();
#else
		bm_init();
#endif
#endif

	if ( FindArg( "-norun" ) )
		return(0);

	mprintf( (0, "\nInitializing 3d system..." ));
	g3_init();
	mprintf( (0, "\nInitializing texture caching system..." ));
	if (FindArg( "-lowmem" ))
		texmerge_init( 10 );		// if we are low on mem, only use 10 cache bitmaps
	else
		texmerge_init( 9999 );		// otherwise, use as much as possible (its still limited by the #define in texmerge.c, so it won't actually use 9999) -MM
	mprintf( (0, "\nRunning game...\n" ));
#ifdef SCRIPT
	script_init();
#endif
	set_screen_mode(SCREEN_MENU);

	init_game();
	set_detail_level_parameters(Detail_level);

	Players[Player_num].callsign[0] = '\0';
	if (!Auto_demo) 	{
		key_flush();
#ifdef QUICKSTART
		strcpy(Players[Player_num].callsign, config_last_player);
		read_player_file();
		Auto_leveling_on = Default_leveling_on;
		write_player_file();
#else
//added/changed on 10/31/98  by Victor Rachels to add -pilot and exit on esc
                if((i=FindArg("-pilot")))
                 {
                  char filename[15];
                  sprintf(filename,"%.8s.plr",Args[i+1]);
                  strlwr(filename);
                   if(!access(filename,4))
                    {
                     strcpy(Players[Player_num].callsign,Args[i+1]);
                     strupr(Players[Player_num].callsign);
                     read_player_file();
                     Auto_leveling_on = Default_leveling_on;
                     WriteConfigFile();
                    }
                   else          //pilot doesn't exist. get pilot.
                    if(!RegisterPlayer())
                     Function_mode = FMODE_EXIT;
                 }
                else
                 if(!RegisterPlayer())               //get player's name
                  Function_mode = FMODE_EXIT;
//end this section addition - Victor Rachels
#endif
	}

	gr_palette_fade_out( NULL, 32, 0 );

	//kconfig_load_all();

	Game_mode = GM_GAME_OVER;

	if (Auto_demo)	{
		newdemo_start_playback((start_demo[0] ? start_demo : "descent.dem"));
		if (Newdemo_state == ND_STATE_PLAYBACK )
			Function_mode = FMODE_GAME;
	}

#ifndef SHAREWARE
	t = build_mission_list(0);	    // This also loads mission 0.
#endif


#ifdef QUICKSTART
	Difficulty_level = Player_default_difficulty;
	Skip_briefing_screens = 1;

	{
		int default_mission = 0;
		for (i=0;i<t;i++) {
			if ( !strcasecmp( Mission_list[i].mission_name, config_last_mission ) )
				default_mission = i;
                }
		load_mission(default_mission);
	}
	Function_mode = FMODE_GAME;
	StartNewGame(1);
	game();
#endif
	while (Function_mode != FMODE_EXIT)
	{
		switch( Function_mode ) {
		case FMODE_MENU:
			if ( Auto_demo < 0 ) {
				show_title_screen( "descent.pcx", 3 ); // show w/o fade,keywait
                                RegisterPlayer();               //get player's name
				Auto_demo = 0;
			} else if ( Auto_demo )        {
				if (start_demo[0])
					newdemo_start_playback(start_demo);
				else
					newdemo_start_playback(NULL);		// Randomly pick a file
				if (Newdemo_state != ND_STATE_PLAYBACK)	
					Error("No demo files were found for autodemo mode!");
			} else {
				check_joystick_calibration();
				DoMenu();									 	
#ifdef EDITOR
				if ( Function_mode == FMODE_EDITOR )	{
					create_new_mine();
					SetPlayerFromCurseg();
				}
#endif
			}
			break;
		case FMODE_GAME:
			#ifdef EDITOR
				keyd_editor_mode = 0;
			#endif
			game();
			if ( Function_mode == FMODE_MENU )
				songs_play_song( SONG_TITLE, 1 );
			break;
		#ifdef EDITOR
		case FMODE_EDITOR:
			keyd_editor_mode = 1;
			editor();
#ifdef __WATCOMC__
			_harderr( (void *)descent_critical_error_handler );		// Reinstall game error handler
#endif
			if ( Function_mode == FMODE_GAME ) {
				Game_mode = GM_EDITOR;
				editor_reset_stuff_on_level();
				N_players = 1;
			}
			break;
		#endif
		default:
			Error("Invalid function mode %d",Function_mode);
		}
	}

	WriteConfigFile();

#ifndef ROCKWELL_CODE
        #ifdef SHAREWARE
                show_order_form();
	#endif
#endif

//killed at 7/11/99 by adb - first run all atexit()'s
//--killed #if defined(_MSC_VER) && defined(_DEBUG)
//--killed	_CrtDumpMemoryLeaks();
//--killed #endif
//end changes - adb

	return(0);		//presumably successful exit

}


void check_joystick_calibration()	{
	int x1, y1, x2, y2, c;
	fix t1;

	if ( (Config_control_type!=CONTROL_JOYSTICK) &&
		  (Config_control_type!=CONTROL_FLIGHTSTICK_PRO) &&
		  (Config_control_type!=CONTROL_THRUSTMASTER_FCS) &&
		  (Config_control_type!=CONTROL_GRAVIS_GAMEPAD)
		) return;

	joy_get_pos( &x1, &y1 );

	t1 = timer_get_fixed_seconds();
	while( timer_get_fixed_seconds() < t1 + F1_0/100 )
		;

	joy_get_pos( &x2, &y2 );

	// If joystick hasn't moved...
	if ( (abs(x2-x1)<30) &&  (abs(y2-y1)<30) )	{
		if ( (abs(x1)>30) || (abs(x2)>30) ||  (abs(y1)>30) || (abs(y2)>30) )	{
			c = nm_messagebox( NULL, 2, TXT_CALIBRATE, TXT_SKIP, TXT_JOYSTICK_NOT_CEN );
			if ( c==0 )	{
				joydefs_calibrate();
			}
		}
	}

}

void show_order_form()
{
	show_title_screen(
#ifdef SHAREWARE
	"order01.pcx",
#else
	"warning.pcx",
#endif
	1);
}

void quit_request()
{
#ifdef NETWORK
	void network_abort_game();
	if(Network_status)
		network_abort_game();
#endif
	exit(0);
}
