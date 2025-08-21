extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace LuaModule {
    static int luaOnMeshPacketReceive(lua_state *L);
    static int luaOnMeshPacketSend(lua_state *L);
    static int luaSendMeshPacket(lua_state *L);
}