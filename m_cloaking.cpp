#include <stdio.h>
#include "users.h"
#include "channels.h"
#include "globals.h"
#include "modules.h"

class ModuleCloaking : public Module
{
 private:

	 Server *Srv;
	 
 public:
	ModuleCloaking()
	{
		Srv = new Server;
	}
	
	virtual ~ModuleCloaking()
	{
		delete Srv;
	}
	
	virtual Version GetVersion()
	{
		return Version(1,0,0,0);
	}
	
	virtual void OnUserConnect(userrec* user)
	{
		if (strstr(user->dhost,"."))
		{
			string a = strstr(user->dhost,".");
			char ra[64];
			long seed,s2;
			memcpy(&seed,user->dhost,sizeof(long));
			memcpy(&s2,a.c_str(),sizeof(long));
			sprintf(ra,"%.8X",seed*s2*strlen(user->host));
			string b = Srv->GetNetworkName() + "-" + ra + a;
			debug("cloak: allocated %s",b.c_str());
			strcpy(user->dhost,b.c_str());
		}
	}

};


class ModuleCloakingFactory : public ModuleFactory
{
 public:
	ModuleCloakingFactory()
	{
	}
	
	~ModuleCloakingFactory()
	{
	}
	
	virtual Module * CreateModule()
	{
		return new ModuleCloaking;
	}
	
};


extern "C" void * init_module( void )
{
	return new ModuleCloakingFactory;
}

