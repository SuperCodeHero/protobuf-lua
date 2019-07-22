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

            {"toHexStr", toHexStr},
            {"hexStrToSrc", hexStrToSrc},

            {"tMalloc", tMalloc},
            {"tFree", tFree},

            {NULL, NULL},
    };

    luaL_newlib(l, r);

    return 1;
}

int readKey(lua_State *l)
{
    const char *p = (const char *)lua_touserdata(l, 1);
    const char *end = (const char *)lua_touserdata(l, 2);

    if(p >= end)
    {
        lua_pushlightuserdata(l, (void *)p);
        lua_pushboolean(l, false);
        return 2;
    }

    unsigned char key = *p++;
    int tag = key >> 3;
    int wire_type = key & 7;

    lua_pushlightuserdata(l, (void *)p);
    lua_pushboolean(l, true);
    lua_pushinteger(l, tag);
    lua_pushinteger(l, wire_type);

    return 4;
}

int readVarInt(lua_State *l)
{
    const char *p = (char *)lua_touserdata(l, 1);
    const char *end = (const char *)lua_touserdata(l, 2);

    uint64_t len = lua_tointeger(l, 2);

    uint64_t  v = 0;
    p = parseVarint64(p, end, &v);

    lua_pushlightuserdata(l, (void *)p);
    lua_pushinteger(l, v);

    return 2;
}

int readLengthDelimited(lua_State *l)
{
    const char *p = (char *)lua_touserdata(l, 1);
    const char *end = (const char *)lua_touserdata(l, 2);

    uint64_t len = 0;
    p = parseVarint64(p, end, &len);

    char *buf = (char *)malloc(len + 1);
    memcpy(buf, p, len);

    p += len;

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
    uint32_t len;
    const char *p = (const char *)lua_tolstring(l, 1, (size_t *)&len);

    char *buf = (char *)malloc(len);
    memcpy(buf, p, len);

    lua_pushlightuserdata(l, (void *)buf);
    lua_pushlightuserdata(l, (void *)(buf + len));

    return 2;
}

int tFree(lua_State *l)
{
    void *p = lua_touserdata(l, 1);
    free(p);

    return 0;
}

int toHexStr(lua_State *l)
{
    size_t len;

    const char *p = lua_tolstring(l, 1, &len);
    char *buf = (char *)malloc(len * 2 + 1);
    toHexString(buf, p, len);

    lua_pushlstring(l, buf, len * 2);
    return 1;
}

int hexStrToSrc(lua_State *l)
{
    size_t len = 0;
    const char *p = lua_tolstring(l, 1, &len);

    char *buf = (char *)malloc(len / 2 + 1);

    for(size_t i = 0; i < len; i += 2)
    {
        char c1 = p[i];
        char c2 = p[i + 1];

        uint8_t v1 = HexCharToSrc(c1);
        uint8_t v2 = HexCharToSrc(c2);

        char res = v1 << 4 | v2;
        buf[i / 2] = res;
    }

    lua_pushlstring(l, buf, len / 2);

    return 1;
}

int tAdd(int a, int b)
{
    return a + b;
}