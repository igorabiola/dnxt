/**
 * @file lclass.h
 *
 * @brief <b>API for using "classes" in lua</b>
 *
 * @author Victor Fusco
 *
 */
#ifndef LCLASS_H
#define LCLASS_H

#include "lua.h"
#include "lauxlib.h"

#ifdef LCLASS_OWN_
    #define LCLASS_API
#else 
    #define LCLASS_API extern
#endif /* LCLASS_OWN_ */

#ifndef lua_ptWrapper
/** 
 * @brief <b>Wrap a pointer with the userdata</b>
 * 
 * @param L Current lua state 
 * @param u Usedata (struct pointer)
 * 
 */
#define lua_ptWrapper( L , u )       (*(void**)( lua_newuserdata( L , sizeof(void *) )) = (u))
/** 
 * @brief <b>Dewrap a pointer on the user data</b>
 * 
 * @param L Current lua state 
 * @param i index 
 * 
 * @return Userdata
 */
#define lua_ptDewrapper( L , i )     (*(void**)( lua_touserdata( L , i )))
/** 
 * @brief <b>Check Class</b>
 * 
 * @param L Current lua state 
 * @param s Class id string
 * @param i index
 * 
 * @return Userdata 
 */
#define lclass_ptDewrap( L , s , i ) (*(void**)( lclass_checkclass( L , s , i )))
#endif /* lua_ptWrapper */


/** @brief <b>Creates a new lua "class"</b>
 *
 *  This function creates a new lua metatable with the name given by classname parameter.
 *  Than sets it`s idclass and register the methods found in the luaL_reg funcs array.  
 * 
 * @param L Current lua state 
 * @param classname C string with the name of the class
 * @param funcs a luaL_reg struct with class methods
 */
LCLASS_API void lclass_createclass ( lua_State *L , const char *classname , const luaL_reg * funcs );

/** @brief <b>Sets the object metable with pre-defined table</b>
 *
 *  This function sets the metatable classname on the table at stack index  
 * 
 * @param L Current lua state 
 * @param classname C string with the name of the class
 * @param index Stack index 
 */
LCLASS_API void lclass_setclass ( lua_State *L , const char *classname , int index );

/** @brief <b>Check if the object is a instance of the given classname</b>
 *
 *  This function check if the object is a instance of the given classname.
 *  This check is based on the idclass information.
 *
 * @param L 
 * @param classname 
 * @param index 
 */
LCLASS_API void * lclass_checkclass ( lua_State *L , const char *classname , int index );

#endif /* LCLASS_H */
