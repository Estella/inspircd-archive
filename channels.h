#include "inspircd_config.h"

#ifndef __CHANNELS_H__
#define __CHANNELS_H__

/* this struct doesn't need a userlist member because we can figure this out
 * by enumerating the user array */

struct chanrec {
	char name[CHANMAX]; /* channel name */
	char custom_modes[MAXMODES];     /* modes handled by modules */
	char topic[MAXBUF];
	time_t created;
	time_t topicset;
	char setby[NICKMAX];
	/* modes stuff */
	long limit;
	char key[32];
	short int topiclock;
	short int noexternal;
	short int inviteonly;
	short int moderated;
	short int secret;
	short int c_private;
};

/* used to hold a channel and a users modes on that channel, e.g. +v, +h, +o
 * needs to come AFTER struct chanrec */

#define UCMODE_OP      1
#define UCMODE_VOICE   2
#define UCMODE_HOP     4
#define UCMODE_PROTECT 8
#define UCMODE_FOUNDER 16
 
struct ucrec {
	long uc_modes; /* modes related to both user and channel, e.g. +o */
	struct chanrec *channel; /* actual channel this refers to */
};

#endif

