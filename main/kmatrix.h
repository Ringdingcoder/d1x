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
 * Kill matrix.
 * 
 * $Log$
 * Revision 1.1  2002/07/22 09:19:34  Administrator
 * Initial revision
 *
 * Revision 1.1.1.1  1999/06/14 22:12:31  donut
 * Import of d1x 1.37 source.
 *
 * Revision 2.0  1995/02/27  11:28:51  john
 * New version 2.0, which has no anonymous unions, builds with
 * Watcom 10.0, and doesn't require parsing BITMAPS.TBL.
 * 
 * Revision 1.3  1995/02/15  14:47:39  john
 * Added code to keep track of kills during endlevel.
 * 
 * Revision 1.2  1994/12/09  16:19:46  yuan
 * kill matrix stuff.
 * 
 * Revision 1.1  1994/12/09  15:58:33  yuan
 * Initial revision
 * 
 * 
 */



#ifndef _KMATRIX_H
#define _KMATRIX_H

extern int kmatrix_kills_changed;

void kmatrix_view(int network);

#endif
 
