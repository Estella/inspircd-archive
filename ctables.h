/*       +------------------------------------+
 *       | Inspire Internet Relay Chat Daemon |
 *       +------------------------------------+
 *
 *  Inspire is copyright (C) 2002-2003 ChatSpike-Dev.
 *                       E-mail:
 *                <brain@chatspike.net>
 *           	  <Craig@chatspike.net>
 *     
 * Written by Craig Edwards, Craig McLure, and others.
 * This program is free but copyrighted software; see
 *            the file COPYING for details.
 *
 * ---------------------------------------------------
 
 $Log: ctables.h,v $
 Revision 1.2  2003/01/09 21:09:50  brain
 added '/stats M' command

 Revision 1.1  2003/01/07 01:02:14  brain

 definitions for command table types


 * ---------------------------------------------------
 */
#include "inspircd_config.h"
#include "inspircd.h"

#ifndef __CTABLES_H__
#define __CTABLES_H__

typedef void (handlerfunc) (char**, int, struct userrec*);

/* a structure that defines a command */

struct command_t {
	char command[MAXBUF]; /* command name */
	handlerfunc *handler_function; /* handler function as in typedef */
	char flags_needed; /* user flags needed to execute the command or 0 */
	int min_params; /* minimum number of parameters command takes */
	long use_count; /* used by /stats m */
	long total_bytes; /* used by /stats m */
};

#endif

