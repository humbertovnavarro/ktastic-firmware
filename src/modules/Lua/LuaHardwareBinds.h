extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "Arduino.h"
#include <Wire.h>
#include "FreeRTOS.h"
#include "task.h"

namespace LuaModule {
    static int luaSerialBegin(lua_State *L);
    static int luaI2CBegin(lua_State *L);
    static int luaPin(lua_State *L);
    static int luaFS(lua_State *L);
    static void registerFunction(lua_State *L, const char* name, lua_CFunction func) {
        lua_pushcfunction(L, func);
        lua_setglobal(L, name);
    }
}