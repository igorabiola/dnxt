/**
 * @file lclass.c
 *
 * @brief <b>Classes for lua API implementation</b>
 *
 * @author Victor Fusco
 *
 */

#define LCLASS_OWN_
    #include "lclass.h"
#define LCLASS_OWN_

/**************************************************************************
 * Creates a new class with given methods
 * Methods whose names start with __ are passed directly to the metatable.
 **************************************************************************/

void lclass_createclass( lua_State *L , const char * classname , const luaL_reg *funcs ) 
{
    luaL_newmetatable(L, classname); 
    lua_pushstring(L, "__index");    
    lua_newtable(L);                 
    
    lua_pushstring(L, "idclass");    
    lua_pushstring(L, classname);    
    lua_rawset(L, -3);               

    for (; funcs->name; funcs++) 
    {    
        lua_pushstring(L, funcs->name);
        lua_pushcfunction(L, funcs->func);
        lua_rawset(L, funcs->name[0] == '_' ? -5: -3);
    }

    lua_rawset(L, -3);               
    lua_pop(L, 1);
}

/**************************************************************************
 * Set object class
 **************************************************************************/
void lclass_setclass(lua_State *L, const char *classname, int index ) 
{
    luaL_getmetatable( L , classname );
    if ( index < 0 )
        index--;
    lua_setmetatable( L , index );
}

/**************************************************************************
 * Return userdata 
 **************************************************************************/
void *lclass_checkclass( lua_State *L , const char *classname, int index ) 
{
    void *udata = luaL_checkudata( L , index , classname );
    /*void *udata = lua_ptDewrap2( L , index , classname );*/

    if ( !udata ) 
    {
        luaL_argerror(L, index, "Unexpected type received");
    }

    return udata;
}

