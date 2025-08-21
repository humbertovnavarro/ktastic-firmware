extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace LuaModule {
    static int luaDelay(lua_state *L);
    static int luaSubProcess(lua_state *L);
}