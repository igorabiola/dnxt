/**
 * @file luabt.c
 *
 * @brief <b>Core functions implementation</b>
 *
 * @author Victor Fusco
 *
 */


#include "lclass.h"

#define LUABT_OWN
#include "luabt.h"
#undef LUABT_OWN

#define MYNAME		"luabt"
#define MYVERSION	"Bluetooth for " LUA_VERSION " / Aug 2007"

/** 
 * @brief <b>Get device information</b>
 *
 * @par Lua Signature:
 *      luabt.dev_info( dev_id ) 
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_dev_info( lua_State * L )
{
    struct hci_dev_info di; 
    char addr[18];
    int dev_id;
    int sock;

    dev_id = (int)luaL_optnumber( L , 1, -1 );
    /*dev_id = hci_get_route(NULL);*/

    if( dev_id < 0 ) 
    {
        lua_pushnil(L);
        lua_pushstring( L , "Device not available" );
        return 2;
    }

    sock = hci_open_dev(dev_id);

    if(sock < 0) 
    {
        lua_pushnil(L);
        lua_pushstring( L , "HCI open device failed" );
        return 2;
    }

    di.dev_id = dev_id ; 

    if (ioctl(sock, HCIGETDEVINFO, (void *) &di))
    {
        lua_pushnil( L );
        lua_pushstring( L , "HCI get dev info error" );
        return 2;
    }

    ba2str(&di.bdaddr, addr);

    lua_newtable( L );

    lua_pushstring( L , "name"     );
    lua_pushstring( L , di.name    );
    lua_rawset( L , -3 );

    lua_pushstring( L , "address"  );
    lua_pushstring( L , addr );
    lua_rawset( L , -3 );

    return 1;
}

/** 
 * @brief  <b>Scan for devices</b>
 *
 * @par Lua Signature:
 *      luabt.scan_devices( [local_addr] )  
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_scan_devices( lua_State * L )
{
    int sock = -1;
    char addr[19];
    char name[248];
    const char *local_addr;
    inquiry_info *info = NULL; 
    int len = 8; 
    int dev_id;
    int num_rsp = 0 ;
    int i;
    char class[9];

    bdaddr_t baddr;

    local_addr = luaL_optstring( L , 1 , NULL );

    if( local_addr != NULL )
    {
        str2ba(local_addr, &baddr);
        dev_id = hci_get_route(&baddr);
    }
    else 
    {
        dev_id = hci_get_route(NULL);
    }

    if( dev_id < 0 ) 
    {
        lua_pushnil(L);
        lua_pushstring( L , "Device not available" );
        return 2;
    }


    num_rsp = hci_inquiry(dev_id, len, num_rsp, NULL, &info, IREQ_CACHE_FLUSH );
    
    if( num_rsp <= 0 ) 
    {
        hci_close_dev(sock);
        lua_pushnil(L);
        lua_pushstring( L , "HCI inquiry failed" );
        return 2;
    }

    sock = hci_open_dev(dev_id);

    if(sock < 0) 
    {
        lua_pushnil(L);
        lua_pushstring( L , "HCI open device failed" );
        return 2;
    }

    lua_newtable( L );
    for(i = 0; i < num_rsp; i++) {
        
        lua_newtable( L );

        /* set address field */
        ba2str(&(info+i)->bdaddr, addr);
        lua_pushstring( L, "address" );
        lua_pushstring( L , addr );
        lua_rawset( L , -3 );

        /* set name field */
        lua_pushstring( L, "name" );
        if(hci_read_remote_name(sock, &(info+i)->bdaddr, sizeof(name), name, 0) < 0) 
        {
            lua_pushstring( L, "[unknown]" );
        }
        else
        {
            lua_pushstring( L, name );
        }
        lua_rawset( L , -3 );

        /* set class field */
        lua_pushstring( L, "class" );
        sprintf( class , "0x%2.2x%2.2x%2.2x", (info+i)->dev_class[2], (info+i)->dev_class[1], (info+i)->dev_class[0]);
        lua_pushstring( L , class );
        lua_rawset( L , -3 );

        lua_rawseti( L , -2 , i );
    }

    hci_close_dev(sock);
    return 1;
}


/** 
 * @brief  <b>Connect to a device</b>
 *
 * @par Lua Signature:
 *      luabt.connect( device_addr )  
 * 
 * @param L 
 * 
 * @return 
 */
static int luabt_connect( lua_State * L )
{
    struct sockaddr_rc addr = { 0 };
    int sock, status;
    const char * remote_addr;
    struct luabt_socket_handle * handle;

    remote_addr = luaL_optstring( L , 1, NULL );
    if ( remote_addr == NULL )
    {
        lua_pushnil( L );
        lua_pushstring( L , "Invalid Address" );
        return 2;
    }

    str2ba( remote_addr , &addr.rc_bdaddr );

    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = ( uint8_t ) luaL_optnumber( L, 2 , 1 ); /* default channel 1 */
    
    sock = socket( AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM );

    status = connect( sock, ( struct sockaddr * ) &addr, sizeof( addr ) );

    if ( status < 0 )
    {
        lua_pushnil( L );
        lua_pushstring( L , "rfcomm connection failed" );
        return 2;
    }

#if 0    
    rv = fcntl( sock, F_SETFL, O_NONBLOCK );

    if ( rv == 0 )
    {
        printf( "nonblock set\n" );
    }
    else
    {
        printf( "nonblock failed: " );
    }
#endif

    handle = (struct luabt_socket_handle *) malloc(sizeof(struct luabt_socket_handle));

    if ( handle == NULL )
    {
        lua_pushnil( L );
        lua_pushstring( L , "out of memory" );
        return 2;
    }

    handle->socket = sock;

    luabt_pushsocket( L , handle );

    return 1;
}

/** 
 * @brief <b>functions mapping to lua</b>
 */
static const luaL_reg funcs[] =
{
    { "scan_devices" , luabt_scan_devices },  /* Done */
    { "dev_info"     , luabt_dev_info     },  /* Done */
    { "connect"      , luabt_connect      },  /* Done */
    { NULL           , NULL               }
};


/** 
 * @brief <b>class mapping to lua</b>
 */
static const luaL_reg classes[] =
{
    { LUABTSOCKETHANDLE , luabt_socket_open        },
    { NULL              , NULL                     }
};

/** 
 * @brief <b>Initialize luabt class metatables</b> 
 * 
 * @param L 
 * 
 * @return 0 
 */
static int luabt_start( lua_State * L )
{
    unsigned int i;

    for( i = 0 ; classes[i].name ; i++ )
    {
        classes[i].func(L);
    }

    return 0;
}

/**************************************************************************
 * Exported functions
 **************************************************************************/

/* See description on header file lusb.h */
LUALIB_API int luaopen_luabt (lua_State *L)
{
    luaL_register( L , MYNAME, funcs );
    lua_pushliteral( L , "version" );
    lua_pushliteral( L , MYVERSION );
    lua_settable( L , -3 );

    luabt_start( L );

    return 1;
}
