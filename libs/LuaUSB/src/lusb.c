/**
 * @file lusb.c
 *
 * @brief <b>Core functions implementation</b>
 *
 * @author Victor Fusco
 *
 */

#define LUSB_OWN
#include "lusb.h"
#undef LUSB_OWN

#define MYNAME		"lusb"
#define MYVERSION	"libusb for " LUA_VERSION " / Mar 2007"


/**************************************************************************
 *
 * Core functions
 *
 **************************************************************************/

/** 
 * @brief <b>Initialize libusb</b>
 *
 * This function calls libusb's usb_init();
 * 
 * @par Lua Signature:
 *      lusb.init()
 *
 * @param L lua state
 * 
 * @return Number of return arguments. Always zero here. 
 */
static int lusb_init(lua_State *L)
{
    usb_init();
    return 0;
}

/** 
 * @brief <b>Enable/Disable libusb debug</b> 
 * 
 * This function calls libusb's usb_set_debug()
 *
 * @par Lua Signature:
 *      lusb.set_debug(level)
 *
 * @param L lua state
 * 
 * @return Number of return arguments. Always zero here. 
 */
static int lusb_set_debug(lua_State *L)
{
    usb_set_debug(luaL_checkint( L , 1));
    return 0;
}

/** 
 * @brief <b>Finds all USB busses on system</b>
 * 
 * @par Lua Signature:
 *      lusb.find_busses()
 *
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int lusb_find_busses(lua_State *L)
{
    int ret = usb_find_busses();
    lua_pushinteger( L , ret );
    return 1;
}

/** 
 * @brief <b>Find all devices on all USB devices</b>
 * 
 * @par Lua Signature:
 *      lusb.find_devices()
 *
 * @param L lua state
 * 
 * @return Number of return arguments. Always one here.
 */
static int lusb_find_devices(lua_State *L)
{
    int ret = usb_find_devices();
    lua_pushinteger( L , ret );
    return 1;
}

/** 
 * @brief <b>Push the list of USB busses found into the lua stack</b>
 * 
 * @par Lua Signature:
 *      lusb.get_busses()
 *
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int lusb_get_busses(lua_State *L)
{
    struct usb_bus * bus;
    int i = 1;

    bus = usb_get_busses();

    if( bus == NULL )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }
    
    lua_newtable(L);
    for (; bus; bus = bus->next) 
    {
        lusb_pushbus( L , bus );
        lua_rawseti( L , -2 , i );
        i++;
    }

    return 1;
}

/**************************************************************************
 *
 * Auxiliary functions
 *
 **************************************************************************/

/** 
 * @brief <b>Print device's information</b>
 * 
 * @par Lua Signature:
 *      lusb.print_dev( device )
 *
 * @param L lua state
 * 
 * @return Number of return arguments. 
 */
static int lusb_print_dev(lua_State *L)
{
    struct usb_device * dev;

    dev = lusb_getdev( L ,1 ) ;
    
    if( dev == NULL )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    print_device(dev,0);

    return 0;
}

/** 
 * @brief <b>Search for a specific device given a Vendor_ID and Product_ID </b>
 * 
 * @par Lua Signature:
 *      lusb.find_dev( Vendor_ID , Product_ID )
 *
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int lusb_find_dev(lua_State *L)
{
    struct usb_bus * bus;
    struct usb_bus * busses;
    int vendor = 0, product = 0; 

    busses  = usb_get_busses() ;
    vendor  = getint( L , 1 );
    product = getint( L , 2 );

    if( busses == NULL )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    for (bus = busses; bus; bus = bus->next) 
    {
        struct usb_device *dev;

        for (dev = bus->devices; dev; dev = dev->next) 
        {
            /* Check if this device is a printer */
            if ((dev->descriptor.idVendor == vendor) && (dev->descriptor.idProduct == product ))
            {
                lusb_pushdev( L , dev );
                return 1;
            }
        }
    }
    
    lua_pushnil(L);
    return 1;
}

/** 
 * @brief <b>Class metatables mapping to lua</b>
 */
static const luaL_reg classes[] =
{
    { USBBUS       , lusb_bus_open        },
    { USBCONF      , lusb_conf_open       },
    { USBENDP      , lusb_endpoint_open   },
    { USBINTF      , lusb_interface_open  },
    { USBDEV       , lusb_dev_open        },
    { USBDEVHANDLE , lusb_devhandle_open  },
    { NULL         , NULL                 }
};

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg funcs[] =
{
    { "init"                       , lusb_init                       },  /* Done */
    { "set_debug"                  , lusb_set_debug                  },  /* Done */
    { "find_busses"                , lusb_find_busses                },  /* Done */
    { "find_devices"               , lusb_find_devices               },  /* Done */
    { "find_dev"                   , lusb_find_dev                   },  /* Done */
    { "print_dev"                  , lusb_print_dev                  },  /* Done */
    { "get_busses"                 , lusb_get_busses                 },  /* Done */ 
    { NULL                         , NULL                            }
};

/** 
 * @brief <b>Initialize LuaUSB</b>
 * 
 * @param L lua state
 * 
 * @return Number of return arguments. Always zero here. 
 */
static int lusb_start ( lua_State * L )
{
    int i;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for(i = 0 ; classes[i].name ; i++ )
    {
        classes[i].func(L);
    }

    return 0;
} 


/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
int lusb_pusherror(lua_State *L)
{
    char * s = usb_strerror();
    if (s)
        lua_pushstring(L , s);
    else
        lua_pushnil(L);

    return 1 ;
}

/* See description on header file lusb.h */
LUALIB_API int luaopen_lusb (lua_State *L)
{
    luaL_register(L, MYNAME, funcs);
    lua_pushliteral(L,"version");
    lua_pushliteral(L,MYVERSION);
    lua_settable(L,-3);

    lusb_start( L );

    return 1;
}
