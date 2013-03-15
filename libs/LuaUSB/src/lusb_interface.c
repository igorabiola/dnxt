/**
 * @file lusb_interface.c
 *
 * @brief <b>USB interface functions implementation</b>
 *
 * A few functions to return usb_interface_descriptor attributes
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h"

#define LUSB_INTERFACE_OWN
#include "lusb.h"
#undef LUSB_INTERFACE_OWN

/**************************************************************************
 * Static functions
 **************************************************************************/

/** 
 * @brief <b>Push Interface Number in the lua stack</b> 
 * 
 * @par Lua Signature:
 *      interface_descriptor:bInterfaceNumber()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Always one here.
 */
static int bInterfaceNumber( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->bInterfaceNumber );
    return 1;
}  

/** 
 * @brief <b>Push Interface Alternate Setting in the lua stack</b> 
 * 
 * @par Lua Signature:
 *      interface_descriptor:bAlternateSetting()
 * 
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int bAlternateSetting( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->bAlternateSetting );
    return 1;
}  

/** 
 * @brief <b>Push Interface Number Of Endpoints in the lua stack</b> 
 *  
 * @par Lua Signature:
 *      interface_descriptor:bNumEndpoints()
 *
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int bNumEndpoints( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->bNumEndpoints );
    return 1;
}  

/** 
 * @brief <b>Push Interface Class in the lua stack</b> 
 * 
 * @par Lua Signature:
 *      interface_descriptor:bInterfaceClass()
 * 
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int bInterfaceClass( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->bInterfaceClass );
    return 1;
}  

/** 
 * @brief <b>Push Interface Subclass in the lua stack</b> 
 *  
 * @par Lua Signature:
 *      interface_descriptor:bInterfaceSubClass()
 *
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int bInterfaceSubClass( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->bInterfaceSubClass );
    return 1;
}  

/** 
 * @brief <b>Push Interface Protocol in the lua stack</b> 
 * 
 * @par Lua Signature:
 *      interface_descriptor:bInterfaceProtocol()
 * 
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int bInterfaceProtocol( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->bInterfaceProtocol );
    return 1;
}  

/** 
 * @brief <b>Push Interface in the lua stack</b> 
 * 
 * @par Lua Signature:
 *      interface_descriptor:iInterface()
 * 
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int iInterface( lua_State *L )
{
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
    lua_pushinteger( L , interface->iInterface );
    return 1;
}  

/** 
 * @brief <b>Push a table with the interface endpoints in the lua stack</b> 
 * 
 * @par Lua Signature:
 *      interface_descriptor:endpoints()
 * 
 * @param L lua state  
 * 
 * @return Number of return arguments. Always one here.
 */
static int endpoints( lua_State *L )
{
    int i = 0 ;
    struct usb_interface_descriptor * interface = lusb_getinterface(L , 1);
   
    lua_newtable(L);

    for ( i=0 ; i < interface->bNumEndpoints ; i++ ) 
    {
        lusb_pushendpoint( L , interface->endpoint+i );
        lua_rawseti( L , -2 , i );
    }
   
    return 1;
}  


/** 
 * @brief <b>Interface descriptor functions mapping to lua</b>
 */
static const luaL_reg interface_funcs[] =
{
    { "bInterfaceNumber"   ,  bInterfaceNumber   },
    { "bAlternateSetting"  ,  bAlternateSetting  },
    { "bNumEndpoints"      ,  bNumEndpoints      },
    { "bInterfaceClass"    ,  bInterfaceClass    },
    { "bInterfaceSubClass" ,  bInterfaceSubClass },
    { "bInterfaceProtocol" ,  bInterfaceProtocol },
    { "iInterface"         ,  iInterface         }, 
    { "endpoints"          ,  endpoints          },
    { NULL                 ,  NULL               }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
int lusb_interface_open( lua_State * L )
{
    lclass_createclass(L , USBIDESC , interface_funcs );
    return 0;
}

/* See description on header file lusb.h */
void lusb_pushinterface( lua_State * L , struct usb_interface_descriptor * intf )
{
    lua_ptWrapper( L , intf );
    lclass_setclass( L , USBIDESC , -1  );
    return ;
}

/* See description on header file lusb.h */
struct usb_interface_descriptor * lusb_getinterface( lua_State * L , int index )
{
    return (struct usb_interface_descriptor *) lclass_ptDewrap( L , USBIDESC , 1 ) ;
}

