#include "inspircd_config.h" 
#include "channels.h" 
 
#ifndef __USERS_H__ 
#define __USERS_H__ 
 
#define STATUS_OP     4 
#define STATUS_HOP    2 
#define STATUS_VOICE  1 
#define STATUS_NORMAL 0 
 
#define XADD      = 1 
#define XSUBTRACT = 2 
 
struct userrec { 
	char nick[NICKMAX];    /* nickname, null if no NICK yet */ 
	unsigned long ip;      /* ipv4 IP address */ 
	char ident[MAXBUF];    /* ident */ 
	char host[MAXBUF];     /* hostname */ 
	char dhost[MAXBUF];    /* displayed hostname (VHOST) */ 
	char fullname[MAXBUF]; /* user full name */ 
	int fd;		       /* file descriptor (socket number) */ 
	long modes;	       /* user modes and other bits and bobs, NO CHANNEL MODES! */ 
	char inbuf[MAXBUF];    /* input buffer (recvQ) */ 
	char outbuf[MAXBUF];   /* output buffer (sendQ) */ 
	time_t lastping;       /* time client was last pinged */ 
	time_t signon;         /* time client signed on */ 
	time_t idle_lastmsg;   /* last msg from client, used as idle time */ 
	time_t nping;	       /* ping timeout timer */ 
	int registered;        /* true if client has registered USER and NICK */ 
	struct ucrec chans[MAXCHANS]; /* pointers to channels user is on plus ucmodes */ 
	char server[MAXBUF]; 
	char awaymsg[MAXBUF]; 
}; 
 
 
#endif 
 
