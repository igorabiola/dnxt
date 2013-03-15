OIL_FLAVOR = "ludo;base"

require "oil"                                    -- Load OiL package
require "lnxt"

-- example usage
function usage()
    print("lua nxtserver.lua [usb|bt]")
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
    require "lusb"
    nxtdev  = lusb.find_dev( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct )
else
    require("luabt")
    nxtdev  = luabt.connect("00:16:53:04:08:72")
end


-- Create a new nxt object
mynxt,err = lnxt.new( nxtdev )

if not mynxt then
    print(err)
else

    oil.main(function()

        local nxt = mynxt

        nxt = oil.newservant( nxt )                    -- Create Ludo object

        local ref = oil.tostring(nxt)                  -- Get object's reference
        if not oil.writeto("nxt.ludo", ref ) then
            print(ref)
        end

        local lnxt1 = oil.newservant( lnxt )           -- Create Ludo object

        local ref1 = oil.tostring(lnxt1)               -- Get object's reference
        if not oil.writeto("lnxt.ludo",  ref1) then
            print(ref1)
        end

        oil.run()                                      -- Start ORB main loop
    end)
end
