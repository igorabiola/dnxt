/**
 * @file lusb_dev.c
 *
 * @brief <b>Device class functions implementation</b>
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h"

#define LUSB_DEV_OWN
#include "lusb.h"
#undef LUSB_DEV_OWN

/**************************************************************************
 * Static functions
 **************************************************************************/

/** 
 * @brief <b>Push descriptor.bcdUSB into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bcdUSB()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bcdUSB( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bcdUSB );
    return 1;
}  

/** 
 * @brief <b>Push Device class into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bDeviceClass()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bDeviceClass( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bDeviceClass );
    return 1;
}  

/** 
 * @brief <b>Push device subclass into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bDeviceSubClass()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bDeviceSubClass( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bDeviceSubClass );
    return 1;
}  

/** 
 * @brief <b>Push device protocol into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bDeviceProtocol()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bDeviceProtocol( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bDeviceProtocol );
    return 1;
}  

/** 
 * @brief <b>Push device max packet size into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bMaxPacketSize0()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bMaxPacketSize0( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bMaxPacketSize0 );
    return 1;
}  

/** 
 * @brief <b>Push device Vendor ID into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:idVendor()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int idVendor( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.idVendor );
    return 1;
}  

/** 
 * @brief <b>Push device Product ID into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:idProduct()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int idProduct( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.idProduct );
    return 1;
}  

/** 
 * @brief <b>Push device bcdDevice into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bcdDevice()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bcdDevice( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bcdDevice );
    return 1;
}  

/** 
 * @brief <b>Push device Manufacturer into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:iManufacturer()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int iManufacturer( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.iManufacturer );
    return 1;
}  

/** 
 * @brief <b>Push device Product into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:iProduct()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int iProduct( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.iProduct );
    return 1;
}  

/** 
 * @brief <b>Push device Serial Number into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:iSerialNumber()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int iSerialNumber( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.iSerialNumber );
    return 1;
}  

/** 
 * @brief <b>Push device Number of configurations into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:bNumConfigurations()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int bNumConfigurations( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushinteger( L , dev->descriptor.bNumConfigurations );
    return 1;
}  

/** 
 * @brief <b>Push device filename into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:filename()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int filename( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lua_pushstring( L , dev->filename );
    return 1;
}  

/** 
 * @brief <b>Push device configuration into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:config()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int config( lua_State *L )
{
    struct usb_device * dev = lusb_getdev(L , 1);
    lusb_pushusbconf( L , dev->config );
    return 1;
}  

/** 
 * @brief <b>Opens a USB device</b>
 * 
 * @par Lua Signature:
 *      usb_device:open()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int open(lua_State *L)
{
    struct usb_dev_handle * dhandle = NULL;
    struct usb_device * device = lusb_getdev(L , 1);

    dhandle = usb_open(device);

    if ( dhandle == NULL )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }
    else
    {
        lusb_pushdevhandle(L,dhandle);
    }

    return 1;
}

/** 
 * @brief <b>Push next device into the lua stack</b>
 * 
 * @par Lua Signature:
 *      usb_device:next()
 * 
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int dev_next(lua_State *L)
{
    struct usb_device * dev;
    struct usb_device * devnext;

    dev = lusb_getdev( L ,1 ) ;
    devnext = dev->next  ;

    if(( dev == NULL ) || ( devnext == NULL ) )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }
    
    lusb_pushdev( L , devnext );

    return 1;
}

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg dev_funcs[] =
{
    { "config"             ,  config             },
    { "open"               ,  open               },
    { "filename"           ,  filename           },
    { "bcdUSB"             ,  bcdUSB             },
    { "bDeviceClass"       ,  bDeviceClass       },
    { "bDeviceSubClass"    ,  bDeviceSubClass    },
    { "bDeviceProtocol"    ,  bDeviceProtocol    },
    { "bMaxPacketSize0"    ,  bMaxPacketSize0    },
    { "idVendor"           ,  idVendor           },
    { "idProduct"          ,  idProduct          },
    { "bcdDevice"          ,  bcdDevice          },
    { "iManufacturer"      ,  iManufacturer      },
    { "iProduct"           ,  iProduct           },
    { "iSerialNumber"      ,  iSerialNumber      }, 
    { "bNumConfigurations" ,  bNumConfigurations },
    { "next"               ,  dev_next           },  /* Done */ 
    { NULL                 ,  NULL               }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
int lusb_dev_open( lua_State * L )
{
    lclass_createclass(L , USBDEV , dev_funcs );
    return 0;
}

/* See description on header file lusb.h */
void lusb_pushdev( lua_State * L , struct usb_device * dev )
{
    lua_ptWrapper( L , dev );
    lclass_setclass( L , USBDEV , -1  );
    return ;
}

/* See description on header file lusb.h */
struct usb_device * lusb_getdev( lua_State * L , int index )
{
    return (struct usb_device *) lclass_ptDewrap( L , USBDEV , 1 );
}

