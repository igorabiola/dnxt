/**
 * @file lusb.h
 *
 * @brief <b>API for dealing with libusb types in lua</b>
 *
 * @author Victor Fusco
 *
 */
#ifndef  LUSBTYPES_H_
#define  LUSBTYPES_H_

#include <lua.h>
#include <lauxlib.h>
#include <usb.h>

#define getint        luaL_checkint
#define getuchar      (unsigned char) luaL_checknumber

/**
 * \defgroup LUSB_API LUSB
 * \defgroup LUSB_BUS_API LUSB_BUS
 * \defgroup LUSB_CONFIG_API LUSB_CONFIG
 * \defgroup LUSB_DEV_API LUSB_DEV
 * \defgroup LUSB_DEV_HANDLE_API LUSB_DEV_HANDLE
 * \defgroup LUSB_ENDPOINT_API LUSB_ENDPOINT
 * \defgroup LUSB_INTERFACE_API LUSB_INTERFACE
 */

#ifdef LUSB_OWN
#define LUSB_API
#else
#define LUSB_API extern
#endif

#ifdef LUSB_BUS_OWN
#define  LUSB_BUS_API
#else
#define  LUSB_BUS_API extern
#endif

#ifdef LUSB_CONFIG_OWN
#define  LUSB_CONFIG_API
#else
#define  LUSB_CONFIG_API extern
#endif

#ifdef LUSB_DEV_OWN
#define  LUSB_DEV_API
#else
#define  LUSB_DEV_API extern
#endif

#ifdef LUSB_DEV_HANDLE_OWN
#define  LUSB_DEV_HANDLE_API
#else
#define  LUSB_DEV_HANDLE_API extern
#endif

#ifdef LUSB_ENDPOINT_OWN
#define  LUSB_ENDPOINT_API
#else
#define  LUSB_ENDPOINT_API extern
#endif

#ifdef LUSB_INTERFACE_OWN
#define  LUSB_INTERFACE_API
#else
#define  LUSB_INTERFACE_API extern
#endif

#define USBDEV       "usb_device"               /**< metatable idclass */ 
#define USBDEVHANDLE "usb_dev_handle"           /**< metatable idclass */
#define USBBUS       "usb_bus"                  /**< metatable idclass */
#define USBCONF      "usb_conf"                 /**< metatable idclass */
#define USBENDP      "usb_endpoint_descriptor"  /**< metatable idclass */
#define USBINTF      "usb_interface"            /**< metatable idclass */
#define USBIDESC     "usb_interface_descriptor" /**< metatable idclass */

/** 
 * \ingroup LUSB_API
 *
 * @brief <b>Push the error onto the stack</b>
 * 
 * @param L Current lua state
 * 
 * @return Number of arguments 
 */
LUSB_API int lusb_pusherror( lua_State * L );

/** 
 * \ingroup LUSB_BUS_API
 *
 * @brief <b>Init the bus class metatable</b> 
 * 
 * @param L 
 * 
 * @return 
 */
LUSB_BUS_API int lusb_bus_open( lua_State * L );

/** 
 * \ingroup LUSB_BUS_API
 *
 * @brief <b>Push usb_bus reference onto the stack</b> 
 * 
 * @param L 
 * @param bus 
 */
LUSB_BUS_API void lusb_pushbus( lua_State * L, struct usb_bus *bus );

/** 
 * \ingroup LUSB_BUS_API
 *
 * @brief <b>Get a usb_bus on the stack index</b> 
 * 
 * @param L 
 * @param index 
 * 
 * @return usb_bus
 */
LUSB_BUS_API struct usb_bus *lusb_getusbbus( lua_State * L, int index );

/** 
 * \ingroup LUSB_CONFIG_API
 *
 * @brief <b>Init the usb config descriptor class metatable</b> 
 * 
 * @param L 
 * 
 * @return 
 */
LUSB_CONFIG_API int lusb_conf_open( lua_State * L );

/** 
 * \ingroup LUSB_CONFIG_API
 *
 * @brief <b>Get a usb_config_descriptor on the stack index</b> 
 * 
 * @param L 
 * @param i 
 * 
 * @return usb config descriptor
 */
LUSB_CONFIG_API struct usb_config_descriptor *lusb_getusbconf( lua_State * L, int i );

/** 
 * \ingroup LUSB_CONFIG_API
 *
 * @brief <b>Push usb_config_descriptor reference onto the stack</b> 
 * 
 * @param L 
 * @param conf 
 */
LUSB_CONFIG_API void lusb_pushusbconf( lua_State * L, struct usb_config_descriptor *conf );

/**
 * \ingroup LUSB_DEV_API
 *
 * @brief <b>Init the usb device class metatable</b> 
 * 
 * @param L 
 * 
 * @return 
 */
LUSB_DEV_API int lusb_dev_open( lua_State * L );

/** 
 * \ingroup LUSB_DEV_API
 *
 * @brief <b>Push usb_device reference onto the stack</b> 
 * 
 * @param L 
 * @param dev 
 */
LUSB_DEV_API void lusb_pushdev( lua_State * L, struct usb_device *dev );

/** 
 * \ingroup LUSB_DEV_API
 *
 * @brief <b>Get a usb_device on the stack index</b> 
 * 
 * @param L 
 * @param index 
 * 
 * @return usb device
 */
LUSB_DEV_API struct usb_device *lusb_getdev( lua_State * L, int index );

/** 
 * \ingroup LUSB_DEV_HANDLE_API
 *
 * @brief <b>Init the device handle class metatable</b> 
 * 
 * @param L 
 * 
 * @return 
 */
LUSB_DEV_HANDLE_API int lusb_devhandle_open( lua_State * L );

/** 
 * \ingroup LUSB_DEV_HANDLE_API
 *
 * @brief <b>Push usb_dev_handle reference onto the stack</b> 
 * 
 * @param L 
 * @param dhandle 
 */
LUSB_DEV_HANDLE_API void lusb_pushdevhandle( lua_State * L, struct usb_dev_handle *dhandle );

/** 
 * \ingroup LUSB_DEV_HANDLE_API
 *
 * @brief <b>Get a usb_dev_handle on the stack index</b> 
 * 
 * @param L 
 * @param i 
 * 
 * @return device handle
 */
LUSB_DEV_HANDLE_API struct usb_dev_handle *lusb_getdevhandle( lua_State * L, int i );

/** 
 * \ingroup LUSB_ENDPOINT_API
 *
 * @brief <b>Init the endpoint descriptor class metatable</b> 
 * 
 * @param L 
 * 
 * @return 
 */
LUSB_ENDPOINT_API int lusb_endpoint_open( lua_State * L );

/** 
 * \ingroup LUSB_ENDPOINT_API
 *
 * @brief <b>Push usb_endpoint_descriptor reference onto the stack</b> 
 * 
 * @param L 
 * @param endp 
 */
LUSB_ENDPOINT_API void lusb_pushendpoint( lua_State * L, struct usb_endpoint_descriptor *endp );

/** 
 * \ingroup LUSB_ENDPOINT_API
 *
 * @brief <b>Get a usb_endpoint_descriptor on the stack index</b> 
 * 
 * @param L 
 * @param i 
 * 
 * @return endpoint descriptor
 */
LUSB_ENDPOINT_API struct usb_endpoint_descriptor *lusb_getusbendp( lua_State * L, int i );

/** 
 * \ingroup LUSB_INTERFACE_API
 *
 * @brief <b>Init the usb interface descriptor class metatable</b> 
 * 
 * @param L 
 * 
 * @return 
 */
LUSB_INTERFACE_API int lusb_interface_open( lua_State * L );

/** 
 * \ingroup LUSB_INTERFACE_API
 *
 * @brief <b>Push usb_interface_descriptor reference onto the stack</b> 
 * 
 * @param L 
 * @param intf 
 */
LUSB_INTERFACE_API void lusb_pushinterface( lua_State * L, struct usb_interface_descriptor *intf );

/** 
 * \ingroup LUSB_INTERFACE_API
 *
 * @brief <b>Get a usb_interface_descriptor on the stack index</b> 
 * 
 * @param L 
 * @param index 
 * 
 * @return usb interface descriptor
 */
LUSB_INTERFACE_API struct usb_interface_descriptor *lusb_getinterface( lua_State * L, int index );

/*for debug only -- will be removed */
void print_endpoint( struct usb_endpoint_descriptor *endpoint );
void print_altsetting( struct usb_interface_descriptor *interface );
void print_interface( struct usb_interface *interface );
void print_configuration( struct usb_config_descriptor *config );
int print_device( struct usb_device *dev, int level );

#endif /* LUSBTYPES_H_ */
