extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "LuaHardwareBinds.h"

namespace LuaModule {
    void luaExec(const char* script);
}