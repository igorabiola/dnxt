require("table_print")

print( "Configuration:" )
print( "\tPORT_1: Sound Sensor" )
print( "\tPORT_2: Touch Sensor" )
print( "\tPORT_3: Light Sensor" )
print( "\tPORT_4: Ultrasonic Sensor" )

function init()
    nxt:KeepAlive()
    nxt:SetInputMode( "PORT_1" , "SOUND_DB"    , "RAWMODE" )
    nxt:SetInputMode( "PORT_2" , "SWITCH"      , "BOOLEANMODE" )
    nxt:SetInputMode( "PORT_3" , "LIGHT_ACTIVE", "PCTFULLSCALEMODE" )
    nxt:SetInputMode( "PORT_4" , "LOWSPEED_9V" , "RAWMODE" )
end

function GetInput( port ) 
    local value , err =  nxt:GetInputValues( port )
    if assert(value,err) then
        print("Getting input values from sensor on port: " .. port)
        table.print(value)
    end
end

function init_usonic()
    nxt:SetInputMode( "PORT_4" , "LOWSPEED_9V" , "RAWMODE" )
    lnxt.sleep(300)
    local _ = nxt:LsRead("PORT_4") -- Clean last stuff
    print( "LsWrite1", nxt:LsWrite( "PORT_4",string.char(  0x02 , 0x41, 0x02), 0,true ) ) 
end

function get_distance()
    nxt:LsWrite( "PORT_4",string.char( 0x02 , 0x42) , 1 , false)
    lnxt.sleep(10)
    local value ,err, aux =  nxt:LsGetStatus( "PORT_4")
    assert(value,err)
    while value < 1 do
	nxt:LsWrite( "PORT_4",string.char(0x02 , 0x42), 1 , false) 
        lnxt.sleep(10)
        value ,err, aux =  nxt:LsGetStatus( "PORT_4") 
    end
    return nxt:LsRead("PORT_4")
end

ports   = { "PORT_1","PORT_2", "PORT_3"}

--init()
--[[
for _,port in pairs(ports) do
    print( "Starting port:" .. port )
    for i=1,6 do
        GetInput(port)
        lnxt.sleep(3000)
    end
end

--]]
--
--lnxt.sleep(600)
init_usonic()
--lnxt.sleep(100)
for i=1,100 do
    local data =  get_distance()
    print("Distance: ",  string.byte(data,1,#data))
    lnxt.sleep(10)
end
--]]



