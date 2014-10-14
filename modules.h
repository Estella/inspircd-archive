/*

$Log: modules.h,v $
Revision 1.6  2003/01/13 22:30:50  brain
Added Admin class (holds /admin info for modules)
Added methods to Server class


*/


#ifndef __PLUGIN_H
#define __PLUGIN_H

#include "dynamic.h"

// This #define allows us to call a method in all
// loaded modules in a readable simple way, e.g.:
// 'FOREACH_MOD OnConnect(user);'

#define FOREACH_MOD for (int i = 0; i <= MODCOUNT; i++) modules[i]->

// class Version holds the version information of a Module, returned
// by Module::GetVersion (thanks RD)

class Version
{
 public:
	 const int Major, Minor, Revision, Build;
	 Version(int major, int minor, int revision, int build);
};

class Admin
{
 public:
	 const string Name, Email, Nick;
	 Admin(string name,string email,string nick);
};

//
// Module is an abstract class so that developers can inherit from it
//

class Module
{
 public:
	Module();
	virtual ~Module();
	virtual Version GetVersion();
	virtual void OnUserConnect(userrec* user);
	virtual void OnUserQuit(userrec* user);
	virtual void OnUserJoin(userrec* user, chanrec* channel);
	virtual void OnUserPart(userrec* user, chanrec* channel);
};


class Server
{
 public:
	 // constructor and destructor
	 Server();
	 virtual ~Server();

	 // data output methods
	 virtual void SendOpers(string s);
	 virtual void Debug(string s);
	 virtual void Send(int Socket, string s);
	 virtual void SendServ(int Socket, string s);
	 virtual void SendFrom(int Socket, userrec* User, string s);
	 virtual void SendTo(userrec* Source, userrec* Dest, string s);
	 virtual void SendChannel(userrec* User, chanrec* Channel, string s,bool IncludeSender);
	 virtual bool CommonChannels(userrec* u1, userrec* u2);
	 virtual void SendCommon(userrec* User, string text,bool IncludeSender);
	 virtual void SendWallops(userrec* User, string text);

	 // data query methods
	 virtual bool IsNick(string nick);
	 virtual userrec* FindNick(string nick);
	 virtual chanrec* FindChannel(string channel);
	 virtual string ChanMode(userrec* User, chanrec* Chan);
	 virtual string GetServerName();
	 virtual string GetNetworkName();
	 virtual Admin GetAdmin();
	 
};

//
// The is an example factory for plug ins. 
//
// This example factory only announces when it is created/destroyed and
// has the single abstract method CreateModule() which returns a type 
// of plug in.
//
// In the real world, you may have multiple different classes in each
// shared library that are made to work together.  All these classes
// must be created by the Factory class.
//
// You may find it useful to have the objects that you create with
// the factory class be given a pointer to the factory class so
// they can create their own objects that they need, using the same
// factory class.  Compiler support of covariant return types is 
// real useful here.
//


class ModuleFactory
{
 public:
	ModuleFactory() { }
	virtual ~ModuleFactory() { }
	virtual Module * CreateModule() = 0;
};

#endif
