#ifndef __PLUGIN_H
#define __PLUGIN_H

#include "dynamic.h"

// This #define allows us to call a method in all
// loaded modules in a readable simple way, e.g.:
// 'FOREACH_MOD OnConnect(user);'

#define FOREACH_MOD for (int i = 0; i <= MODCOUNT; i++) modules[i]->

//
// Module is an abstract class so that developers can inherit from it
//

class Module
{
 public:
	Module();
	virtual ~Module();
	virtual void OnUserConnect(userrec* user);
	virtual void OnUserQuit(userrec* user);
	virtual void OnUserJoin(userrec* user, chanrec* channel);
	virtual void OnUserPart(userrec* user, chanrec* channel);
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
