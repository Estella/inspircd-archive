/*

$Log: inspircd.h,v $
Revision 1.4  2003/01/13 22:30:50  brain
Added Admin class (holds /admin info for modules)
Added methods to Server class


*/


#include <string>
#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/param.h>
#include <sys/types.h>
#ifndef _LINUX_C_LIB_VERSION
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#endif
#include <arpa/inet.h>

#include "inspircd_config.h"
#include "inspircd_io.h"
#include "inspircd_util.h"
#define ERROR -1
#define TRUE 1
#define FALSE 0
/* max sockets we can open */
#define MAXSOCKS 64

/* prototypes */
int InspIRCd(void);
int InitConfig(void);
void Error(int status);
void send_error(char *s);
void ReadConfig(void);
void strlower(char *n);

extern "C" void WriteOpers(char* text, ...);
extern "C" void debug(char *text, ...);
extern "C" void Write(int sock,char *text, ...);
extern "C" void WriteServ(int sock, char* text, ...);
extern "C" void WriteFrom(int sock, struct userrec *user,char* text, ...);
extern "C" void WriteTo(struct userrec *source, struct userrec *dest,char *data, ...);
extern "C" void WriteChannel(struct chanrec* Ptr, struct userrec* user, char* text, ...);
extern "C" void ChanExceptSender(struct chanrec* Ptr, struct userrec* user, char* text, ...);
extern "C" int common_channels(struct userrec *u, struct userrec *u2);
extern "C" void WriteCommon(struct userrec *u, char* text, ...);
extern "C" void WriteCommonExcept(struct userrec *u, char* text, ...);
extern "C" void WriteWallOps(struct userrec *source, char* text, ...);
extern "C" int isnick(const char *n);
extern "C" struct userrec* Find(string nick);
extern "C" struct chanrec* FindChan(const char* chan);
extern "C" char* cmode(struct userrec *user, struct chanrec *chan);
extern "C" string getservername();
extern "C" string getnetworkname();
extern "C" string getadminname();
extern "C" string getadminemail();
extern "C" string getadminnick();

