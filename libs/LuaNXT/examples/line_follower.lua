require("lusb")
require("lnxt")
require("table_print")

-- example usage
function usage()
    print("lua line_follower.lua [usb|bt]")
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

-- Create a new nxt object
nxt,err = lnxt.new( nxtdev )


function linefound() 
    local value , err =  nxt:GetInputValues( "PORT_3" )
    local found = false
    if assert(value,err) then
        --print("Port: " .. value.port)
        --print("Valid: " .. value.port)
        --print("Raw: " .. value.raw)
        --print("Normalized: ".. value.normalized)
        --print("Scaled: " .. value.scaled)
        if value.scaled < 55 then found = true end 
    end
    lnxt.sleep(1000)
    print("line found? " , found)
    return found
end

function turn( degrees , counter_clockwise) 
    print("turn " ..degrees .. " degrees ", counter_clockwise )
    if counter_clockwise then
        nxt:SetOutputState( "PORT_B", -45 , "MOTORON_BRAKE_REGULATED", "MOTOR_SPEED" , 0 , "RAMPUP", degrees )
        nxt:SetOutputState( "PORT_C",  45 , "MOTORON_BRAKE_REGULATED", "MOTOR_SPEED" , 0 , "RAMPUP", degrees )
    else
        nxt:SetOutputState( "PORT_B",  45 , "MOTORON_BRAKE_REGULATED", "MOTOR_SPEED" , 0 , "RAMPUP", degrees )
        nxt:SetOutputState( "PORT_C", -45 , "MOTORON_BRAKE_REGULATED", "MOTOR_SPEED" , 0 , "RAMPUP", degrees )
    end
    local idle = false
    while not idle do
        lnxt.sleep(500)
        local ret  = nxt:GetOutputState("PORT_C")
        idle = (ret.runstate == "IDLE")

        --print("\nturn antes")
       -- table_print(ret)

        if idle then
            nxt:ResetMotorPosition( "PORT_B" , true )
            nxt:ResetMotorPosition( "PORT_C" , true )
            lnxt.sleep(300)
            nxt:SetOutputState( "PORT_B",  1 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "IDLE", 0 )
            nxt:SetOutputState( "PORT_C",  1 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "IDLE", 0 )
            --print("\nturn depois")
            --table_print(nxt:GetOutputState("PORT_C"))
        end
    end
end

function driveFoward() 
    print("Drive forward")
    nxt:SetOutputState( "PORT_B",  75 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "RUNNING", 100 )
    nxt:SetOutputState( "PORT_C",  75 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "RUNNING", 100 )
    local idle = false
    while not idle do
        lnxt.sleep(500)
        local ret = nxt:GetOutputState("PORT_C")
        idle = (ret.runstate == "IDLE")

      --  print("\nforward antes")
      --  table_print(ret)
        
        if idle then
            nxt:ResetMotorPosition( "PORT_B" , true )
            nxt:ResetMotorPosition( "PORT_C" , true )
            lnxt.sleep(300)
            nxt:SetOutputState( "PORT_B",  1 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "IDLE", 0 )
            nxt:SetOutputState( "PORT_C",  1 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "IDLE", 0 )
           -- print("\nforward depois")
          --  table_print(nxt:GetOutputState("PORT_C"))
        end
    end
end

function initialize()
    nxt:KeepAlive()
    nxt:SetInputMode( "PORT_3" , "LIGHT_ACTIVE", "PCTFULLSCALEMODE" )
    nxt:ResetMotorPosition( "PORT_B" )
    nxt:ResetMotorPosition( "PORT_C" )
    nxt:SetOutputState( "PORT_B",  1 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "IDLE", 0 )
    nxt:SetOutputState( "PORT_C",  1 , "MOTORON_BRAKE_REGULATED", "MOTOR_SYNC" , 0 , "IDLE", 0 )
end

if not nxt then
    print(err)
else
    initialize()
    while true do
        local found = false
        local sweep = 2
        
        while not found do
            sweep = sweep * 2
            if not linefound() then
                turn( sweep , false )
                sweep = sweep * 2
                if not linefound() then
                    turn( sweep , true )
                else
                    found = true
                    break
                end
            else
                found = true
                break
            end
        end

        while found do
            driveFoward()
            found = linefound()
        end
        
    end
end

