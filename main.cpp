#include <iostream>

#include "api/tool.h"
#include "api/api.h"
#include "lua.hpp"

using namespace std;

int main() {

    lua_State *l = luaL_newstate();
    luaL_openlibs(l);

    int ret = luaL_loadfile(l, "../main.lua");
    ret = lua_pcall(l, 0, 0, 0);

    if(ret != 0)
    {
        cout << lua_tostring(l, 1) << endl;
    }

    lua_close(l);

//    cout << tAdd(1, 2) << endl;
//    cout << toHexChar('1') << endl;
//    std::cout << "Hello, World!" << std::endl;
    return 0;


}