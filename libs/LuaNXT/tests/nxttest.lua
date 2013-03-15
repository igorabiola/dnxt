require("lnxt")

function usage()
    print("lua nxttest [usb|bt] test_case")
    os.exit(0)
end

-- Check test parameters
if not arg[1] and arg[2] then
    usage()
end

-- Check conection mode
if arg[1] ~= "usb" and arg[1] ~= "bt" then
    usage()
end

mode = arg[1]
test = arg[2]

if mode == "usb" then
    require("lusb")
    nxtdev  = lusb.find_dev( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct )
else
    require("luabt")
    nxtdev  = luabt.connect("00:16:53:07:58:F1")
end

nxt,err = lnxt.new( nxtdev )

if not nxt then
    print(err)
else
    dofile(test)
end

