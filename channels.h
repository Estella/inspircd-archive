#include "inspircd_config.h" 
 
#ifndef __CHANNELS_H__ 
#define __CHANNELS_H__ 
 
/* this struct doesn't need a userlist member because we can figure this out 
 * by enumerating the user array */ 
 
struct chanrec { 
	char name[CHANMAX]; /* channel name */ 
	char chanmodes[MAXMODES];     /* modes related to channel ONLY, e.g. +n and +t */ 
	char topic[MAXBUF]; 
	time_t created; 
	time_t topicset; 
	char setby[MAXBUF]; 
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
 
