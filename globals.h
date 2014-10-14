/*

$Log: globals.h,v $
Revision 1.3  2003/01/13 22:30:50  brain
Added Admin class (holds /admin info for modules)
Added methods to Server class


*/


#ifndef __WORLD_H
#define __WORLD_H

// include the common header files

#undef __CHANNELS_H__
#undef __USERS_H__
#include <typeinfo>
#include <iostream.h>
#include <string>

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

#endif
