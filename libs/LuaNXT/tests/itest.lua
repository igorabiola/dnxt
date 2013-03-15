require("lnxt")

-- example usage
function usage()
    print("lua itest.lua [usb|bt]")
    os.exit(0)
end

-- Check test parameters
if not arg[1] then
    usage()
end

-- Check conection mode
if arg[1] ~= "usb" and arg[1] ~= "bt" then
    usage()
end

local mode = arg[1]

-- Connection mode
if mode == "usb" then
    require("lusb")
    nxtdev  = lusb.find_dev( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct )
else
    require("luabt")
    nxtdev  = luabt.connect("00:16:53:04:08:72")
end

-- Create a new nxt object
nxt,err = lnxt.new( nxtdev )

if not nxt then
    print(err)
    os.exit(0)
end
