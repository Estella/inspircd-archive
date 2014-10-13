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
#define MAXBUF 1024
/* max sockets we can open */
#define MAXSOCKS 64

/* prototypes */
int InspIRCd(void);
int InitConfig(void);
void Error(int status);
void send_error(char *s);
