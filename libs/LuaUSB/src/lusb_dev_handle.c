/**
 * @file lusb_dev_handle.c
 *
 * @brief <b>Device handle functions implementation</b>
 *
 * @author Victor Fusco
 *
 */

#include "lclass.h" 

#define LUSB_DEV_HANDLE_OWN
#include "lusb.h"
#undef LUSB_DEV_HANDLE_OWN

#define LUSB_BUFFER_SIZE 1024u 

static char * LUSB_BUFFER;

/**************************************************************************
 *
 * Device Operation Functions
 *
 **************************************************************************/

/** 
 * @brief <b>Closes a USB device</b>  
 * 
 * @par Lua Signature:
 *      usb_dev_handle:close()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_close(lua_State *L)
{
    int ret;
    struct usb_dev_handle * dhandle = NULL;
    dhandle = lusb_getdevhandle( L , 1 );

    ret = usb_close(dhandle);

    if( ret != 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Sets the active configuration of a device</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:set_configuration( config_num )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_set_configuration(lua_State *L)
{
    int ret , conf;
    struct usb_dev_handle * dhandle = NULL;

    dhandle = lusb_getdevhandle( L , 1 );
    conf    = getint( L , 2 );
                            
    ret = usb_set_configuration( dhandle, conf );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Claim an interface of a device</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:claim_interface( interface_num )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_claim_interface(lua_State *L)
{
    int ret , interface;
    struct usb_dev_handle * dhandle = NULL;

    dhandle   = lusb_getdevhandle( L , 1 );
    interface = getint( L , 2 );
                            
    ret = usb_claim_interface( dhandle, interface );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Releases a previously claimed interface</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:release_interface( interface_num )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_release_interface(lua_State *L)
{
    int ret , interface;
    struct usb_dev_handle * dhandle = NULL;

    dhandle   = lusb_getdevhandle( L , 1 );
    interface = getint( L , 2 );
                            
    ret = usb_release_interface( dhandle, interface );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Sets the active alternate setting of the current interface</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:set_altinterface( interface_num )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_set_altinterface(lua_State *L)
{
    int ret , interface;
    struct usb_dev_handle * dhandle = NULL;

    dhandle   = lusb_getdevhandle( L , 1 );
    interface = getint( L , 2 );
                            
    ret = usb_set_altinterface( dhandle, interface );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Resets state for an endpoint</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:resetep( endp_num )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_resetep(lua_State *L)
{
    int ret ;
    unsigned int ep;
    struct usb_dev_handle * dhandle = NULL;

    dhandle = lusb_getdevhandle( L , 1 );
    ep      = (unsigned)getint( L , 2 );
                            
    ret = usb_resetep( dhandle, ep );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Clears any halt status on an endpoint</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:clear_halt( endpoint )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_clear_halt(lua_State *L)
{
    int ret ;
    unsigned int ep;
    struct usb_dev_handle * dhandle = NULL;

    dhandle = lusb_getdevhandle( L , 1 );
    ep      = (unsigned)getint( L , 2 );
                            
    ret = usb_clear_halt( dhandle, ep );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger(L , ret );

    return 1;
}

/** 
 * @brief <b>Resets a device</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:reset()
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_reset(lua_State *L)
{
    int ret ;
    struct usb_dev_handle * dhandle = NULL;

    dhandle = lusb_getdevhandle( L , 1 );
                            
    ret = usb_reset( dhandle );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger( L , ret );

    return 1;
}

/**************************************************************************
 *
 * Bulk Transfers
 *
 **************************************************************************/

/** 
 * @brief <b>Write data to a bulk endpoint</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:bulk_write( endpoint, data , timeout )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_bulk_write(lua_State *L)
{
    int ret= -1 , ep, timeout=0; 
    size_t size;
    const char * bytes;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    ep      = getint( L , 2 );
    bytes   = lua_tolstring( L , 3 , &size );
    timeout = getint( L , 4 );

    ret = usb_bulk_write( dhandle, ep , (char*)bytes , size, timeout);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger( L , ret);

    return 1;
}

/** 
 * @brief <b>Read data from a bulk endpoint</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:bulk_read( endpoint , size , timeout )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_bulk_read(lua_State *L)
{
    int ret= -1 , ep, timeout = 0 ; 
    struct usb_dev_handle * dhandle = NULL;
    size_t size;
    
    dhandle = lusb_getdevhandle( L , 1 );
    ep      = getint( L , 2 );
    size    = (size_t)getint( L , 3 );
    timeout = getint( L , 4 );

    size = (size > LUSB_BUFFER_SIZE) ? LUSB_BUFFER_SIZE : size;

    ret = usb_bulk_read(dhandle, ep , LUSB_BUFFER, size , timeout);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

/**************************************************************************
 *
 * Interrupt Transfers
 *
 **************************************************************************/

/** 
 * @brief <b>Write data to an interrupt endpoint</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:interrupt_write( endpoint , data , timeout )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_interrupt_write(lua_State *L)
{
    int ret= -1 , ep, timeout=0; 
    size_t size = 0;
    const char * bytes;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    ep      = getint( L , 2 );
    bytes   = lua_tolstring( L , 3 , &size );
    timeout = getint( L , 4 );

    ret = usb_interrupt_write( dhandle, ep , (char*)bytes , size, timeout);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger( L , ret);

    return 1;
}

/** 
 * @brief <b>Read data from a interrupt endpoint</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:interrupt_read( endpoint , size , timeout )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_interrupt_read(lua_State *L)
{
    int ret= -1 , ep, timeout = 0 ; 
    struct usb_dev_handle * dhandle = NULL;
    size_t size = 0;

    dhandle = lusb_getdevhandle( L , 1 );
    ep      = getint( L , 2 );
    size    = (size_t)getint( L , 3 );
    timeout = getint( L , 4 );

    size = (size > LUSB_BUFFER_SIZE) ? LUSB_BUFFER_SIZE : size;

    ret = usb_interrupt_read(dhandle, ep , LUSB_BUFFER, size , timeout);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

/**************************************************************************
 *
 * Control Transfers
 *
 **************************************************************************/

/** 
 * @brief <b>Send a control message to a device</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:control_msg( reqtype, request , value , index , timeout )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments. Always two here.
 */
static int lusb_control_msg(lua_State *L)
{
    int ret= -1, reqtype , request, value, index, timeout;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    reqtype = getint( L , 2 );
    request = getint( L , 3 );
    value   = getint( L , 4 );
    index   = getint( L , 5 );
    timeout = getint( L , 6 );

    ret = usb_control_msg( dhandle , reqtype , request , value, 
                           index , LUSB_BUFFER , LUSB_BUFFER_SIZE , timeout );

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushinteger( L , ret );
    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 2;
}

/** 
 * @brief <b>Retrieves a string descriptor from a device</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:get_string( index , lang_id )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_get_string(lua_State *L) 
{
    int ret= -1, index , langid;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    index   = getint( L , 2 );
    langid  = getint( L , 3 );

    ret = usb_get_string(dhandle, index , langid, LUSB_BUFFER, LUSB_BUFFER_SIZE);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

/** 
 * @brief <b>Retrieves a string descriptor from a device using the first language</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:get_string_simple( index )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_get_string_simple(lua_State *L)
{
    int ret= -1, index ;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    index   = getint( L , 2 );

    ret = usb_get_string_simple(dhandle, index , LUSB_BUFFER, LUSB_BUFFER_SIZE);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

/** 
 * @brief <b>Retrieves a descriptor from a device</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:get_descriptor_by_endpoint( endpoint , index , type )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_get_descriptor_by_endpoint(lua_State *L)
{
    int ret= -1 , ep; 
    unsigned char index, type;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    ep      = getint( L , 2 );
    index   = getuchar( L , 3 );
    type    = getuchar( L , 4 );

    ret = usb_get_descriptor_by_endpoint(dhandle, ep , type , index, (void*)LUSB_BUFFER, LUSB_BUFFER_SIZE/(sizeof(void*)));

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

/** 
 * @brief <b>Retrieves a descriptor from a device's default control pipe</b>
 * 
 * @par Lua Signature:
 *      usb_dev_handle:get_descriptor( index , type )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_get_descriptor(lua_State *L)
{
    int ret= -1 ; 
    unsigned char index, type;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle = lusb_getdevhandle( L , 1 );
    index   = getuchar( L , 2 );
    type    = getuchar( L , 3 );

    ret = usb_get_descriptor(dhandle, type , index, (void*)LUSB_BUFFER, LUSB_BUFFER_SIZE/(sizeof(void*)));

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

#ifndef WIN32
/**************************************************************************
 *
 * Non Portable functions
 *
 **************************************************************************/

/** 
 * @brief <b>Get driver name bound to interface</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:get_driver_np( interface_num )
 * 
 * @param L lua state 
 * 
 * @return Number of return arguments.
 */
static int lusb_get_driver_np(lua_State *L)
{
    int ret= -1, interface ;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle   = lusb_getdevhandle( L , 1 );
    interface = getint( L , 2 );

    ret = usb_get_driver_np(dhandle, interface , LUSB_BUFFER, LUSB_BUFFER_SIZE);

    if( ret < 0 )
    {
        lua_pushnil(L);
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushlstring( L , LUSB_BUFFER, ret);

    return 1;
}

/** 
 * @brief <b>Detach kernel driver from interface</b> 
 * 
 * @par Lua Signature:
 *      usb_dev_handle:detach_kernel_driver_np( interface_num )
 * 
 * @param L lua state
 * 
 * @return Number of return arguments.
 */
static int lusb_detach_kernel_driver_np(lua_State *L)
{
    int ret= -1, interface ;
    struct usb_dev_handle * dhandle = NULL;
    
    dhandle   = lusb_getdevhandle( L , 1 );
    interface = getint( L , 2 );

    ret = usb_detach_kernel_driver_np( dhandle, interface );

    if( ret < 0 )
    {
        lua_pushboolean( L , 0 );
        (void)lusb_pusherror(L);
        return 2;
    }

    lua_pushboolean( L , 1 );

    return 1;
}
#endif

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg dev_funcs[] =
{
    { "close"                      , lusb_close                      },  /* Done */
    { "get_string"                 , lusb_get_string                 },  /* Done */
    { "get_string_simple"          , lusb_get_string_simple          },  /* Done */
    { "get_descriptor_by_endpoint" , lusb_get_descriptor_by_endpoint },  /* Done */
    { "get_descriptor"             , lusb_get_descriptor             },  /* Done */
    { "bulk_write"                 , lusb_bulk_write                 },  /* Done */
    { "bulk_read"                  , lusb_bulk_read                  },  /* Done */
    { "interrupt_write"            , lusb_interrupt_write            },  /* Done */
    { "interrupt_read"             , lusb_interrupt_read             },  /* Done */
    { "control_msg"                , lusb_control_msg                },
    { "set_configuration"          , lusb_set_configuration          },
    { "claim_interface"            , lusb_claim_interface            },
    { "release_interface"          , lusb_release_interface          },
    { "set_altinterface"           , lusb_set_altinterface           },
    { "resetep"                    , lusb_resetep                    },
    { "clear_halt"                 , lusb_clear_halt                 },
    { "reset"                      , lusb_reset                      },  /* Done */
#ifndef WIN32
    { "get_driver_np"              , lusb_get_driver_np              },
    { "detach_kernel_driver_np"    , lusb_detach_kernel_driver_np    },
#endif
    { NULL                         , NULL                            }
};

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
void lusb_pushdevhandle(lua_State *L , struct usb_dev_handle * dhandle )
{
    lua_ptWrapper( L , dhandle );
    lclass_setclass( L , USBDEVHANDLE , -1  );
    return ;
}

/* See description on header file lusb.h */
struct usb_dev_handle * lusb_getdevhandle( lua_State * L , int i)
{
    return (struct usb_dev_handle *) lclass_ptDewrap( L , USBDEVHANDLE , i ) ;
}

/* See description on header file lusb.h */
int lusb_devhandle_open( lua_State * L )
{
    LUSB_BUFFER = (char *)malloc(LUSB_BUFFER_SIZE);
    
    if (LUSB_BUFFER == NULL)
    {
        lua_pushstring( L , "Could not alocate LuaUSB Buffer\0" );
        lua_error( L );
    }

    lclass_createclass(L , USBDEVHANDLE , dev_funcs );

    return 0;
}


