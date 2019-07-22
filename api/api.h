//
// Created by root on 19-7-22.
//
#ifndef API_H_
#define API_H_

#include <lua.hpp>

#ifdef __cplusplus
extern "C" {
#endif

LUAMOD_API int luaopen_api(lua_State *l);

static int readKey(lua_State *l);
static int readVarInt(lua_State *l);
static int readLengthDelimited(lua_State *l);

static int writeKey(lua_State *l);
static int writeVarInt(lua_State *l);
static int writeLengthDelimited(lua_State *l);

static int tMalloc(lua_State *l);
static int tFree(lua_State *l);

int tAdd(int a, int b);

#ifdef __cplusplus
}
#endif

#endif