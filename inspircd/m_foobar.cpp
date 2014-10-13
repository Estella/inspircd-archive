#include "users.h"
#include "channels.h"
#include "globals.h"
#include "modules.h"

// Class ModuleFoobar inherits from Module
// It just outputs simple debug strings to show its methods are working.

class ModuleFoobar : public Module
{
 private:
	 
	 // It is recommended that your class makes use of one or more Server
	 // objects. A server object is a class which contains methods which
	 // encapsulate the exports from the core of the ircd.
	 // such methods include Debug, SendChannel, etc.
 
	 Server *Srv;
 public:
	ModuleFoobar()
	{
		// The constructor just creates an instance of the server class
	
		Srv = new Server;
	}
	
	virtual ~ModuleFoobar()
	{
		// destructor deletes the instance of the server class
	
		delete Srv;
	}
	
	virtual Version GetVersion()
	{
		// this method instantiates a class of type Version, and returns
		// the modules version information using it.
	
		return Version(1,0,0,0);
	}
	
	virtual void OnUserConnect(userrec* user)
	{
		// method called when a user connects
	
		string b = user->nick;
		Srv->Debug("Foobar: User connecting: " + b);
	}

	virtual void OnUserQuit(userrec* user)
	{
		// method called when a user disconnects
	
		string b = user->nick;
		Srv->Debug("Foobar: User quitting: " + b);
	}
	
	virtual void OnUserJoin(userrec* user, chanrec* channel)
	{
		// method called when a user joins a channel
	
		string c = channel->name;
		string b = user->nick;
		Srv->Debug("Foobar: User " + b + " joined " + c);
	}

	virtual void OnUserPart(userrec* user, chanrec* channel)
	{
		// method called when a user parts a channel
	
		string c = channel->name;
		string b = user->nick;
		Srv->Debug("Foobar: User " + b + " parted " + c);
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

