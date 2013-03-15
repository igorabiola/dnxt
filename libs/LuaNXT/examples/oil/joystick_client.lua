OIL_FLAVOR = "ludo;base"

require("oil")                                             -- Load OiL package
require("lusb")
require("lnxt.usb") -- just to get the claim_dev function 

claim_dev = lnxt.usb.claim_dev -- hehehe

joystick_ = lusb.find_dev( 0x040B , 0x6530 )

if not joystick_ then
    print("joystick not found!")
end

print("claim joystick dev")
joystick = claim_dev( joystick_ )


oil.main(function()
	lnxt = oil.newproxy(assert(oil.readfrom("lnxt.ludo"))) -- Get proxy to object
	nxt = oil.newproxy(assert(oil.readfrom("nxt.ludo"))) -- Get proxy to object

	print( lnxt:version() )

    local open = true
    while true do
        local out, err = joystick:interrupt_read(0x81, 4, 100000)

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
end)
