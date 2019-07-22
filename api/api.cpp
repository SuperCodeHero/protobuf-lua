//
// Created by root on 19-7-22.
//

#include "api.h"
#include "tool.h"

#include <stdlib.h>
#include <string.h>

int luaopen_api(lua_State *l)
{
    luaL_checkversion(l);

    luaL_Reg r[] = {
            {"readKey", readKey},
            {"readVarInt", readVarInt},
            {"readLengthDelimited", readLengthDelimited},
            {"writeKey", writeKey},
            {"writeVarInt", writeVarInt},
            {"writeLengthDelimited", writeLengthDelimited},

            {"tMalloc", tMalloc},
            {"tFree", tFree},

            {NULL, NULL},
    };

    luaL_newlib(l, r);

    return 1;
}

int readKey(lua_State *l)
{
    unsigned char *p = (unsigned char *)lua_touserdata(l, 1);

    unsigned char key = *p++;
    int tag = key >> 3;
    int wire_type = key & 0xF8;

    lua_pushlightuserdata(l, (void *)p);
    lua_pushinteger(l, key);
    lua_pushinteger(l, wire_type);

    return 3;
}

int readVarInt(lua_State *l)
{
    const char *p = (char *)lua_touserdata(l, 1);

    uint64_t  v = 0;
    p = parseVarint64(p, &v);

    lua_pushlightuserdata(l, (void *)p);
    lua_pushinteger(l, v);

    return 2;
}

int readLengthDelimited(lua_State *l)
{
    const char *p = (char *)lua_touserdata(l, 1);

    uint64_t len = 0;
    p = parseVarint64(p, &len);

    char *buf = (char *)malloc(len + 1);
    memcpy(buf, p, len);
    buf[len] = '\0';

    lua_pushlightuserdata(l, (void *)p);
    lua_pushlstring(l, buf, len);
    free(buf);

    return 2;
}

int writeKey(lua_State *l)
{
    return 0;
}

int writeVarInt(lua_State *l)
{
    return 0;
}

int writeLengthDelimited(lua_State *l)
{
    return 0;
}

int tMalloc(lua_State *l)
{
    size_t len;
    const char *p = (const char *)lua_tolstring(l, 1, &len);

    char *buf = (char *)malloc(len + 1);
    memcpy(buf, p, len);

    lua_pushlightuserdata(l, (void *)buf);

    return 1;
}

int tFree(lua_State *l)
{
    void *p = lua_touserdata(l, 1);
    free(p);

    return 0;
}

int tAdd(int a, int b)
{
    return a + b;
}