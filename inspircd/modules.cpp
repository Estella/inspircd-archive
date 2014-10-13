
#include <typeinfo>
#include <iostream.h>
#include "globals.h"
#include "modules.h"

//
// Announce to the world that the Module base
// class has been created or destroyed
//

Module::Module() { }
Module::~Module() { }
void Module::OnUserConnect(userrec* user) { }
void Module::OnUserQuit(userrec* user) { }
void Module::OnUserJoin(userrec* user, chanrec* channel) { }
void Module::OnUserPart(userrec* user, chanrec* channel) { }

