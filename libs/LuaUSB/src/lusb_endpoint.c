/**
 * @file lusb_endpoint.c
 *
 * @brief <b>USB endpoint functions implementation</b>
 *
 * A few functions to return endpoint attributes
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h"

#define LUSB_ENDPOINT_OWN
#include "lusb.h"
#undef LUSB_ENDPOINT_OWN

/**************************************************************************
 * Static functions
 **************************************************************************/

/** 
 * @brief <b>Push Endpoint Address into the lua stack</b>
 * 
 * @par Lua Signature:
 *      endpoint_descriptor:bEndpointAddress()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Alway one here.
 */
static int bEndpointAddress( lua_State *L )
{
    struct usb_endpoint_descriptor * endp = lusb_getusbendp(L , 1);
    lua_pushinteger( L , endp->bEndpointAddress );
    return 1;
}

/** 
 * @brief <b>Push Endpoint bmAttributes into the lua stack</b>
 * 
 * @par Lua Signature:
 *      endpoint_descriptor:bmAttributes()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Alway one here.
 */
static int bmAttributes( lua_State *L )
{
    struct usb_endpoint_descriptor * endp = lusb_getusbendp(L , 1);
    lua_pushinteger( L , endp->bmAttributes );
    return 1;
}

/** 
 * @brief <b>Push Endpoint Max Packet Size into the lua stack</b>
 * 
 * @par Lua Signature:
 *      endpoint_descriptor:wMaxPacketSize()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Alway one here.
 */
static int wMaxPacketSize( lua_State *L )
{
    struct usb_endpoint_descriptor * endp = lusb_getusbendp(L , 1);
    lua_pushinteger( L , endp->wMaxPacketSize );
    return 1;
}

/** 
 * @brief <b>Push Endpoint Interval into the lua stack</b>
 * 
 * @par Lua Signature:
 *      endpoint_descriptor:bInterval()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Alway one here.
 */
static int bInterval( lua_State *L )
{
    struct usb_endpoint_descriptor * endp = lusb_getusbendp(L , 1);
    lua_pushinteger( L , endp->bInterval );
    return 1;
}

/** 
 * @brief <b>Push Endpoint Rerfresh into the lua stack</b>
 * 
 * @par Lua Signature:
 *      endpoint_descriptor:bRefresh()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Alway one here.
 */
static int bRefresh( lua_State *L )
{
    struct usb_endpoint_descriptor * endp = lusb_getusbendp(L , 1);
    lua_pushinteger( L , endp->bRefresh );
    return 1;
}

/** 
 * @brief <b>Push Endpoint SynchAddress into the lua stack</b>
 * 
 * @par Lua Signature:
 *      endpoint_descriptor:bSynchAddress()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Alway one here.
 */
static int bSynchAddress( lua_State *L )
{
    struct usb_endpoint_descriptor * endp = lusb_getusbendp(L , 1);
    lua_pushinteger( L , endp->bSynchAddress );
    return 1;
}

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg endpoint_funcs[] =
{
    { "bEndpointAddress" , bEndpointAddress  },
    { "bmAttributes"     , bmAttributes      },
    { "wMaxPacketSize"   , wMaxPacketSize    },
    { "bInterval"        , bInterval         },
    { "bRefresh"         , bRefresh          },
    { "bSynchAddress"    , bSynchAddress     },
    { NULL               , NULL              }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
void lusb_pushendpoint(lua_State *L , struct usb_endpoint_descriptor * endp )
{
    lua_ptWrapper( L , endp );
    lclass_setclass( L , USBENDP , -1  );
    return ;
}

/* See description on header file lusb.h */
struct usb_endpoint_descriptor * lusb_getusbendp( lua_State * L , int i)
{
    return (struct usb_endpoint_descriptor *) lclass_ptDewrap( L , USBCONF , 1 ) ;
}

/* See description on header file lusb.h */
int lusb_endpoint_open( lua_State * L )
{
    lclass_createclass(L , USBENDP , endpoint_funcs );
    return 0;
}

