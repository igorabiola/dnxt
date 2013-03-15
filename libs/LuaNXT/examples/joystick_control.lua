require("lusb")
require("lnxt")

-- example usage
function usage()
    print("lua joystick_control.lua [usb|bt]")
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
    nxtdev  = lusb.find_dev( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct )
else
    require("luabt")
    nxtdev  = luabt.connect("00:16:53:04:08:72")
end

claim_dev = lnxt.usb.claim_dev

joystick_ = lusb.find_dev( 0x040B , 0x6530 )
print("claim joystick dev")
joystick = claim_dev( joystick_ )

-- Create a new nxt object
nxt,err = lnxt.new( nxtdev )

if not nxt then
    print(err)
else
    local open = true
    while true do
        out, err = joystick:interrupt_read(0x81, 4, 100000)

        if out then
            x,y,b = string.byte( out , 1 , 3 )

            if( y == 128 ) then
                if (x == 128 ) then
                    nxt:SetOutputState( "PORT_B", 0 , "BRAKE_REGULATED", "MOTOR_SYNC" , 10 , "IDLE", 0 )
                    nxt:SetOutputState( "PORT_C", 0 , "BRAKE_REGULATED", "MOTOR_SYNC" , 10 , "IDLE", 0 )
                elseif ( x == 255 ) then 
                    nxt:SetOutputState( "PORT_B", -50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                    nxt:SetOutputState( "PORT_C", 50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                elseif ( x == 0 ) then 
                    nxt:SetOutputState( "PORT_B", 50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                    nxt:SetOutputState( "PORT_C", -50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                end
            end

            if (x == 128 ) then
                if (y == 128 ) then
                    nxt:SetOutputState( "PORT_B", 0 , "BRAKE_REGULATED", "MOTOR_SYNC" , 10 , "IDLE", 0 )
                    nxt:SetOutputState( "PORT_C", 0 , "BRAKE_REGULATED", "MOTOR_SYNC" , 10 , "IDLE", 0 )
                elseif ( y == 255 ) then 
                    nxt:SetOutputState( "PORT_B", -50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                    nxt:SetOutputState( "PORT_C", -50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                elseif ( y == 0 ) then 
                    nxt:SetOutputState( "PORT_B", 50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                    nxt:SetOutputState( "PORT_C", 50 , "MOTORON_REGULATED", "MOTOR_SPEED" , 10 , "RUNNING", 0 )
                end
            end

            if ( b ==  1 ) then
                local power = 50
                if not open then power = -50 else power = 50 end
                nxt:SetOutputState( "PORT_A", power , "MOTORON_REGULATED", "MOTOR_SPEED" , 1 , "RUNNING", 20 )
                open = not open
            end
        else
            print(err)
            break
        end
    end
end

