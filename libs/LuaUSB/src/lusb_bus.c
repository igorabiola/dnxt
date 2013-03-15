/**
 * @file lusb_bus.c
 *
 * @brief <b>USB bus functions implementation</b>
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h" 

#define LUSB_BUS_OWN
#include "lusb.h"
#undef LUSB_BUS_OWN

/**************************************************************************
 * Static functions
 **************************************************************************/

/** 
 * @brief <b>Push usb bus location into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_bus:location()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Always one here.
 */
static int lusb_location( lua_State *L )
{
    struct usb_bus * bus = lusb_getusbbus( L , 1 );
    lua_pushinteger( L , bus->location );
    return 1;
}

/** 
 * @brief <b>Push bus dirname into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_bus:dirname()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int lusb_dirname( lua_State *L )
{
    struct usb_bus * bus = lusb_getusbbus( L , 1 );
    lua_pushstring( L , bus->dirname );
    return 1;
}

/** 
 * @brief <b>Not Implemented</b>
 * 
 * @par Lua Signature:
 *      not implemented
 * 
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int lusb_find_by_class( lua_State *L )
{
    return 0;
}

/** 
 * @brief <b>Push a tables with he usb devices into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_bus:devices()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int lusb_devices(lua_State *L)
{
    struct usb_bus * bus;
    struct usb_device * dev;
    int i =1;

    bus = lusb_getusbbus( L ,1 ) ;
    dev = bus->devices;
 

    if(( bus == NULL ) || ( dev == NULL ))
    {
        lua_pushnil(L);
        lusb_pusherror(L);
        return 2;
    }
    
    lua_newtable(L);

    while( dev ) 
    {
        lusb_pushdev( L , dev );
        lua_rawseti( L , -2 , i );
        i++;
        dev = dev->next;
    }

    return 1;
}

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg bus_funcs[] =
{
    { "devices"       , lusb_devices       },  /* Done */ 
    { "dirname"       , lusb_dirname       },   
    { "location"      , lusb_location      },   
    { "find_by_class" , lusb_find_by_class },   
    { NULL            , NULL               }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
void lusb_pushbus(lua_State *L , struct usb_bus * bus )
{
    lua_ptWrapper( L , bus );
    lclass_setclass( L , USBBUS , -1  );
    return ;
}

/* See description on header file lusb.h */
struct usb_bus * lusb_getusbbus( lua_State * L , int i)
{
    return (struct usb_bus *) lclass_ptDewrap( L , USBBUS , 1 ) ;
}

/* See description on header file lusb.h */
int lusb_bus_open( lua_State * L )
{
    lclass_createclass(L , USBBUS , bus_funcs );
    return 0;
}


