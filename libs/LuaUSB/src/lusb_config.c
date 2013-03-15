/**
 * @file lusb_config.c
 *
 * @brief <b>Config descriptor functions implementation</b>
 *
 * A few functions to return usb_config_descriptor attributes
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h"

#define LUSB_CONFIG_OWN
#include "lusb.h"
#undef LUSB_CONFIG_OWN

/**************************************************************************
 * Static functions
 **************************************************************************/

/** 
 * @brief <b>Push wTotalLength onto the lua stack</b>
 * 
 * @par Lua Signature:
 *     usb_config:wTotalLength() 
 *
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int wTotalLength( lua_State *L )
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    lua_pushinteger( L , config->wTotalLength );
    return 1;
}

/** 
 * @brief <b>Push bNumInterfaces onto the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_config:bNumInterfaces() 
 *  
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bNumInterfaces( lua_State *L )
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    lua_pushinteger( L , config->bNumInterfaces );
    return 1;
}

/** 
 * @brief <b>Push bConfigurationValue onto the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_config:bConfigurationValue() 
 *  
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bConfigurationValue( lua_State *L )
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    lua_pushinteger( L , config->bConfigurationValue );
    return 1;
}

/** 
 * @brief <b>Push iConfiguration onto the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_config:iConfiguration() 
 *  
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int iConfiguration( lua_State *L )
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    lua_pushinteger( L , config->iConfiguration );
    return 1;
}

/** 
 * @brief <b>Push bmAttributes onto the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_config:bmAttributes() 
 *  
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bmAttributes( lua_State *L )
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    lua_pushinteger( L , config->bmAttributes );
    return 1;
}

/** 
 * @brief <b>Push MaxPower onto the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_config:MaxPower() 
 *  
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int MaxPower( lua_State *L )
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    lua_pushinteger( L , config->MaxPower );
    return 1;
}

/** 
 * @brief <b>Push interfaces onto the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_config:interfaces() 
 *  
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int interfaces(lua_State *L)
{
    struct usb_config_descriptor * config = lusb_getusbconf(L , 1);
    int i =0 , j=0;

    if( config == NULL ) 
    {
        lua_pushnil(L);
        lusb_pusherror(L);
        return 1;
    }
    
    lua_newtable(L);
    for ( i=0 ; i < config->bNumInterfaces ; i++ ) 
    {
        lua_newtable(L);
        for ( j=0; j < (config->interface+i)->num_altsetting ; j++ ) 
        {
            lusb_pushinterface( L , (config->interface+i)->altsetting+j );
            lua_rawseti( L , -2 , j );
        }
        lua_rawseti( L , -2 , i );
    }

    return 1;
}

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg config_funcs[] =
{
    { "wTotalLength"        , wTotalLength        },
    { "bNumInterfaces"      , bNumInterfaces      },
    { "bConfigurationValue" , bConfigurationValue },
    { "iConfiguration"      , iConfiguration      },
    { "bmAttributes"        , bmAttributes        },
    { "MaxPower"            , MaxPower            },
    { "interfaces"          , interfaces          },
    { NULL                  , NULL                }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
void lusb_pushusbconf(lua_State *L , struct usb_config_descriptor * conf )
{
    lua_ptWrapper( L , conf );
    lclass_setclass( L , USBCONF , -1  );
    return ;
}

/* See description on header file lusb.h */
struct usb_config_descriptor * lusb_getusbconf( lua_State * L , int i)
{
    return (struct usb_config_descriptor *) lclass_ptDewrap( L , USBCONF , 1 ) ;
}

/* See description on header file lusb.h */
int lusb_conf_open( lua_State * L )
{
    lclass_createclass(L , USBCONF , config_funcs );
    return 0;
}
