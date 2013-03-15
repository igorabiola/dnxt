/**
 * @file luabt.h
 *
 * @brief <b>API for dealing with bluetooth types in lua</b>
 *
 * @author Victor Fusco
 *
 */
#ifndef  LUABT_H_
#define  LUABT_H_

#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>

#include <lua.h>
#include <lauxlib.h>

#define getint        luaL_checkint
#define getuchar      (unsigned char) luaL_checknumber

/**
 * \defgroup LUABT_API LUABT
 * \defgroup LUABT_SOCKET_API LUABT_SOCKET
 */

#ifdef LUABT_OWN
#define LUABT_API
#else
#define LUABT_API extern
#endif

#ifdef LUABT_SOCKET_OWN
#define LUABT_SOCKET_API
#else
#define LUABT_SOCKET_API extern
#endif

#define LUABTSOCKETHANDLE "luabt_socket_handle" /**< metatable idclass */ 

struct luabt_socket_handle 
{
    int socket;
};

/** 
 * \ingroup LUABT_SOCKET_API 
 *
 * @brief <b>Push luabt socket handle onto the stack</b>
 * 
 * @param L 
 * @param handle 
 * 
 * @return 
 */
LUABT_SOCKET_API void luabt_pushsocket( lua_State * L , struct luabt_socket_handle * handle );

/** 
 * \ingroup LUABT_SOCKET_API 
 *
 * @brief <b>Get luabt socket handle</b>
 * 
 * @param L 
 * @param index 
 * 
 * @return 
 */
LUABT_SOCKET_API struct luabt_socket_handle * luabt_getsocket( lua_State * L , int index );

/** 
 * \ingroup LUABT_SOCKET_API 
 *
 * @brief <b>Init luabt socket metatable</b>
 * 
 * @param L 
 * 
 * @return 0
 */
LUABT_SOCKET_API int luabt_socket_open( lua_State * L );

#endif
