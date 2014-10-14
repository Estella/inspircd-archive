#include "users.h"
#include "channels.h"
#include "globals.h"
#include "modules.h"

// Class ModuleFoobar inherits from Module
// and shows the world when one is created/destroyed.

class ModuleFoobar : public Module
{
 public:
	ModuleFoobar()
	{
		debug("*** Example module loaded ***");
	}
	
	virtual ~ModuleFoobar()
	{
		debug("*** Example module unloaded ***");
	}
	
	virtual void OnUserConnect(userrec* user)
	{
		debug("Foobar: user connected: %s",user->nick);
	}

	virtual void OnUserQuit(userrec* user)
	{
		debug("Foobar: user quitting: %s",user->nick);
	}
	
	virtual void OnUserJoin(userrec* user, chanrec* channel)
	{
		debug("Foobar: user %s joined %s",user->nick,channel->name);
	}

	virtual void OnUserPart(userrec* user, chanrec* channel)
	{
		debug("Foobar: user %s parted %s",user->nick,channel->name);
	}

};


//
// The ModuleFoobarFactory class inherits from ModuleFactory
// and creates a ModuleFoobar object when requested.
//

class ModuleFoobarFactory : public ModuleFactory
{
 public:
	ModuleFoobarFactory()
	{
	}
	
	~ModuleFoobarFactory()
	{
	}
	
	virtual Module * CreateModule()
	{
		return new ModuleFoobar;
	}
	
};


//
// The "C" linkage factory0() function creates the ModuleFoobarFactory
// class for this library
//

extern "C" void * init_module( void )
{
	return new ModuleFoobarFactory;
}

