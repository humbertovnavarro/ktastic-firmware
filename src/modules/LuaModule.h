#pragma once
#include "concurrency/OSThread.h"
#include "configuration.h"
#include <Arduino.h>
#include "GenericThreadModule.h"
class LuaModule : GenericThreadModule
{
  public:
    LuaModule();
  protected:
};

extern LuaModule *luaModule;
