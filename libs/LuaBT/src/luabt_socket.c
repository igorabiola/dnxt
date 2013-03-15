/**
 * @file luabt_socket.c
 *
 * @brief <b>Socket functions implementation</b>
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h"

#define LUABT_SOCKET_OWN
#include "luabt.h"
#undef LUABT_SOCKET_OWN

/** 
 * @brief <b>Write data</b> 
 *
 * @par Lua Signature:
 *      luabt_socket:write( data )
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_socket_write( lua_State * L )
{
    int ret = -1;
    size_t size;
    struct luabt_socket_handle * handle ;
    const char * bytes;

    handle = luabt_getsocket( L , 1 );
    bytes  = lua_tolstring( L , 2 , &size );

    ret = write( handle->socket, (const void *) bytes, size );

    if( ret < 0 )
    {
        lua_pushnil(L);
        lua_pushstring( L , "write error" );
        return 2;
    }

    lua_pushinteger( L , ret);

    return 1;
}

/** 
 * @brief <b>Read Data</b> 
 *
 * @par Lua Signature:
 *      luabt_socket:read( [timeout secs] ) 
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_socket_read( lua_State * L )
{
    int ret = -1;
    struct luabt_socket_handle * handle ;
    fd_set set;
    char buffer[255];
    struct timeval tm;

    handle = luabt_getsocket( L , 1 );
    tm.tv_sec  = luaL_optint( L , 2 , 0 );
    tm.tv_usec = 0;

    FD_ZERO(&set);
    FD_SET(handle->socket, &set);

    if ( select( handle->socket + 1, &set, 0, 0, &tm ) < 0 )
    {
        lua_pushnil(L);
        lua_pushstring( L , "got nothing" );
        return 2;
    }

    ret = read( handle->socket, buffer , 255 ) ;

    if( ret < 0 )
    {
        lua_pushnil(L);
        lua_pushstring( L , "error reading" );
        return 2;
        return 2;
    }

    lua_pushlstring( L , buffer , ret);

    return 1;
}

/** 
 * @brief <b>Close the connection</b> 
 *
 * @par Lua Signature:
 *      luabt_socket:close() 
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_socket_close( lua_State * L )
{
    struct luabt_socket_handle * handle ;
    handle = luabt_getsocket( L , 1 );
    close(handle->socket);
    return 0;
}

/** 
 * @brief <b>Garbage colector metamethod</b> 
 *
 * @par Lua Signature:
 *      luabt_socket:__gc() 
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_socket_gc( lua_State * L )
{
    struct luabt_socket_handle * handle ;
    handle = luabt_getsocket( L , 1 );
    free(handle);
    return 0;
}

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg socket_funcs[] =
{
    { "close" , luabt_socket_close },  /* Done */
    { "write" , luabt_socket_write },  /* Done */
    { "read"  , luabt_socket_read  },  /* Done */
    { "__gc"  , luabt_socket_gc    },  /* Done */
    { NULL    , NULL               }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file luabt.h */
void luabt_pushsocket( lua_State * L , struct luabt_socket_handle * handle )
{
    lua_ptWrapper( L , handle );
    lclass_setclass( L , LUABTSOCKETHANDLE , -1 );
    return;
}

/* See description on header file luabt.h */
struct luabt_socket_handle * luabt_getsocket( lua_State * L , int index )
{
    return (struct luabt_socket_handle *)lclass_ptDewrap( L , LUABTSOCKETHANDLE , index );
}

/* See description on header file luabt.h */
int luabt_socket_open( lua_State * L ) 
{
    lclass_createclass( L , LUABTSOCKETHANDLE , socket_funcs );
    return 0;
}

