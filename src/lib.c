#include <math.h>

#include "lua.h"
#include "lauxlib.h"

#include "../codigo-pato/include/codp.h"

static struct instruction checkinstruction(lua_State *L, int arg);

static int newcore(lua_State *L) {
    int m = luaL_checkinteger(L, 1);
    struct core *core = (struct core *) lua_newuserdata(L, sizeof(struct core));
    codp_core_init(core, m);
    luaL_getmetatable(L, "codp.core");
    lua_setmetatable(L, -2);
    return 1;
}

static struct core *checkcore(lua_State *L, int arg) {
    void *core = luaL_checkudata(L, arg, "codp.core");
    luaL_argcheck(L, core != NULL, arg, "`codp.core' expected");
    return (struct core *)core;
}

static int coreput(lua_State *L) {
    struct core *core = checkcore(L, 1);
    addr_t addr = luaL_checkinteger(L, 2);
    struct instruction ir = checkinstruction(L, 3);
    codp_core_put(core, addr, ir);
    return 0;
}

static int coreprint(lua_State *L) {
    struct core *core = checkcore(L, 1);
    codp_core_print(core);
    return 0;
}

static enum opcode checkopcode(lua_State *L, int arg) {
    int opcode = luaL_checkinteger(L, arg);
    luaL_argcheck(L, opcode >= DAT && opcode <= SPL, arg, "`opcode' out of bounds");
    return opcode;
}

static enum modifier checkmodifier(lua_State *L, int arg) {
    int modifier = luaL_checkinteger(L, arg);
    luaL_argcheck(L, modifier >= A && modifier <= I, arg, "`modifier' out of bounds");
    return modifier;
}

static enum mode checkmode(lua_State *L, int arg) {
    int mode = luaL_checkinteger(L, arg);
    luaL_argcheck(L, mode >= IMMEDIATE && mode <= INCREMENT, arg, "`mode' out of bounds");
    return mode;
}

static struct operand checkoperand(lua_State *L) {
    struct operand operand;

    lua_pushstring(L, "mode");
    lua_gettable(L, -2);
    operand.mode = checkmode(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "number");
    lua_gettable(L, -2);
    operand.number = luaL_checkinteger(L, -1);
    lua_pop(L, 1);

    return operand;
}

static struct instruction checkinstruction(lua_State *L, int arg) {
    struct instruction instruction;

    lua_pushstring(L, "opcode");
    lua_gettable(L, arg);
    instruction.opcode = checkopcode(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "mode");
    lua_gettable(L, arg);
    instruction.modifier = checkmodifier(L, -1);
    lua_pop(L, 1);

    lua_pushstring(L, "a");
    lua_gettable(L, arg);
    instruction.a = checkoperand(L);
    lua_pop(L, 1);

    lua_pushstring(L, "b");
    lua_gettable(L, arg);
    instruction.b = checkoperand(L);
    lua_pop(L, 1);

    return instruction;
}

static int printinstruction(lua_State *L) {
    struct instruction ir = checkinstruction(L, 1);
    codp_print_instruction(&ir);
    return 0;
}

static int math_sin(lua_State *L) {
    lua_pushnumber(L, sin(luaL_checknumber(L, 1)));
    return 1;
}

static const luaL_Reg codplib[] = {
    {"sin", math_sin},
    {"newcore", newcore},
    {"printinstruction", printinstruction},
    {NULL, NULL}
};

static const struct luaL_Reg codp_core_methods[] = {
    {"put", coreput},
    {"print", coreprint},
    {NULL, NULL}
};

int luaopen_codp(lua_State *L) {
    luaL_newmetatable(L, "codp.core");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  // push the metatable
    lua_settable(L, -3);  // metatable.__index = metatable
    luaL_setfuncs(L, codp_core_methods, 0);

    luaL_newlib(L, codplib);
    return 1;
}
