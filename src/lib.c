#include <math.h>

#include "lua.h"
#include "lauxlib.h"

//#include "../codigo-pato/include/codp.h"

static int math_sin(lua_State *L) {
    lua_pushnumber(L, sin(luaL_checknumber(L, 1)));
    return 1;
}

static const luaL_Reg codplib[] = {
    {"sin", math_sin},
    {NULL, NULL}
};

int luaopen_codp(lua_State *L) {
    luaL_newlib(L, codplib);
    return 1;
}
