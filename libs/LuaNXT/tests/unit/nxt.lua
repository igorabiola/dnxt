require('luaunit')
require("lnxt")

--------------------------------------
-- Test Configuration
local conn = "bt"

-----

if conn == "usb" then
    require("lusb")
    nxtdev  = lusb.find_dev( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct )
elseif conn == "bt" then
    require("luabt")
    nxtdev  = luabt.connect("00:16:53:04:08:72")
else
    print("Connection Mode not defined or invalid!")
    os.exit(0)
end

nxt,err = lnxt.new( nxtdev )

if not nxt then
    print("Could not connect to the device!")
    print(err)
    os.exit(0)
end

nxt:KeepAlive()
local info = nxt:GetDeviceInfo()
print("Setting up test for nxt device")
print("Device Name: " .. info.name )
print("Blutooth Address: " .. info.bt_addr)

TestNxt = { nxt = nxt , conn=conn }

function TestNxt:test01_GetBatteryLevel()
    local level,err = self.nxt:GetBatteryLevel()
    assert( level ~= nil , err )
    assertEquals( type(level) , "number" )
    print("Battery level: " .. level)
end

function TestNxt:test02_start_program()
    local ret,err = self.nxt:StartProgram("Demo.rxe",true)
    assert(ret, err)
    if ret then 
        ret,err = self.nxt:GetCurrentProgram()
        assert(ret,err)
        if ret then print("Current running program: ".. ret ) end
    end
    lnxt.sleep(4000)
end

function TestNxt:test03_stop_program()
    local ret,err = self.nxt:GetCurrentProgram() 
    assert(ret, err)
    if ret then 
        ret,err = self.nxt:StopProgram(true)
        assert(ret,err)
    end
end

function TestNxt:test04_invalid_program_name()
    local ret,err = self.nxt:StartProgram("Demoi.rxe",true)
    assert(not ret, "return should be nil here")
    assert(err == "Data contains out-of-range values" , "wrong error message")
end

function TestNxt:test05_play_sound()
    local ret,err = self.nxt:PlaySoundFile("! Attention.rso", false ,true)
    assert(ret,err)
end

function TestNxt:test06_play_and_stop_sound()
    local ret,err = self.nxt:PlaySoundFile("! Attention.rso", true ,true)
    assert(ret,err)
    lnxt.sleep(2000)
    if ret then
        ret,err = self.nxt:StopSoundPlayback(true)
        assert(ret, err )
    end
end

function TestNxt:test07_invalid_sound_file()
    local ret,err = self.nxt:PlaySoundFile("xxxxxxxxxxx", false ,true)
    assert(not ret, "return should be nil here")
    assert(err == "Data contains out-of-range values" , "wrong error message")
end

function TestNxt:test08_playtone()
    local ret,err = self.nxt:PlayTone( 440, 500 ,true)
    assert(ret,err)
end

function TestNxt:test09_get_and_set_output_state_A()
    local ret,err =  self.nxt:SetOutputState( "PORT_A", 50 , "BRAKE","MOTOR_SPEED" , 10 , "IDLE", 100 , true )
    if assert(ret,err) then
        ret,err = self.nxt:GetOutputState("PORT_A")
        if assert(ret,err) then
            assertEquals(ret.port     , "PORT_A" )
            assertEquals(ret.power    , 50       ) 
            assertEquals(ret.mode     , "BRAKE"  )
            assertEquals(ret.runstate , "IDLE"   )
        end
    end
end

function TestNxt:test10_get_and_set_output_state_B()
    local ret,err =  self.nxt:SetOutputState( "PORT_B", 100 , "MOTORON_REGULATED","MOTOR_SPEED" , 1 , "RUNNING", 1000 , true )
    if assert(ret,err) then
        ret,err = self.nxt:GetOutputState("PORT_B")
        if assert(ret,err) then
            assertEquals(ret.port     , "PORT_B"            )
            assertEquals(ret.power    , 100                 ) 
            assertEquals(ret.mode     , "MOTORON_REGULATED" )
            assertEquals(ret.runstate , "IDLE"              )
        end
    end
end

function TestNxt:test11_get_and_set_output_state_C()
    local ret,err =  self.nxt:SetOutputState( "PORT_C", 100 , "MOTORON_REGULATED","MOTOR_SPEED" , 1 , "RUNNING", 1000 , true )
    if assert(ret,err) then
        ret,err = self.nxt:GetOutputState("PORT_C")
        if assert(ret,err) then
            assertEquals(ret.port     , "PORT_C"            )
            assertEquals(ret.power    , 100                 ) 
            assertEquals(ret.mode     , "MOTORON_REGULATED" )
            assertEquals(ret.runstate , "IDLE"              )
        end
    end
end

function TestNxt:test12_get_and_set_input_state_1()
    --local ret,err = self.nxt:
    --OBS: sensors.lua already test this
end

function TestNxt:test13_get_and_set_input_state_2()
    --local ret,err = self.nxt:
    --OBS: sensors.lua already test this
end

function TestNxt:test14_get_and_set_input_state_3()
    --local ret,err = self.nxt:
    --OBS: sensors.lua already test this
end

function TestNxt:test15_get_and_set_input_state_4()
    --local ret,err = self.nxt:
    --OBS: sensors.lua already test this
end

function TestNxt:test16_get_firmware_version()
    local ret,err = self.nxt:GetFirmwareVersion()
    assert(ret,err)
end

function TestNxt:test17_keepalive()
    local ret,err = self.nxt:KeepAlive(true)
    assert(ret,err)
    if ret then print("KeepAlive time: " .. ret) end
end

function TestNxt:test18_get_device_info()
    local ret,err = self.nxt:GetDeviceInfo( )
    assert(ret,err)
    if ret then
        if assert(ret.name, "info.name not defined!") then self.name = ret.name end
        assert(ret.bt_addr, "info.bt_adddr not defined!")
        assert(ret.signal, "info.signal not defined!")
        assert(ret.free_space, "info.free_space not defined!")
    end
end

function TestNxt:test19_set_brick_name()
    if  assert( self.name, "Previous test failed. Aborting this one." ) then
        local ret,err = self.nxt:SetBrickName("Test",true)
        if assert(ret,err) then 
            ret,err = self.nxt:GetDeviceInfo( )
            if  assert(ret,err) then
                print(string.byte(ret.name))
                assertEquals(ret.name,"Test")
                self.nxt:SetBrickName(self.name,true)
            end
        end
    end
end

function TestNxt:test20_ls_get_status()
    --local ret,err = self.nxt:
    --TODO: ultrasonic sensor is not working
end

function TestNxt:test21_ls_read()
    --local ret,err = self.nxt:
    --TODO: ultrasonic sensor is not working
end

function TestNxt:test22_ls_write()
    --local ret,err = self.nxt:
    --TODO: ultrasonic sensor is not working
end

function TestNxt:test25_MessageWrite()
    local ret,err = self.nxt:MessageWrite(1, "Test 1 2 3" , true)
    assertEquals(ret,nil)
    assertEquals(err,"Data contains out-of-range values")

    lnxt.sleep(2000)
    ret,err = self.nxt:StartProgram("Try-Touch.rtm",true)
    lnxt.sleep(3000)

    if assert(ret,err) then
        ret,err = self.nxt:MessageWrite(1, "Test 1 2 3" , true)
        assert(ret,err)
        ret,err = self.nxt:StopProgram(true)
        assert(ret,err)
    end
end

function TestNxt:test24_MessageRead()
    --local ret,err = self.nxt:
end

function TestNxt:test25_Sleep()
    local start = os.time()
    lnxt.sleep(2000)
    assert( (os.time() - start) >= 2)
end

function TestNxt:test26_ResetMotorPosition_A()
    local ret,err = self.nxt:ResetMotorPosition("PORT_A",false,true)
    assert(ret,err)
end

function TestNxt:test27_ResetMotorPosition_B()
    local ret,err = self.nxt:ResetMotorPosition("PORT_C",false,true)
    assert(ret,err)
end

function TestNxt:test28_ResetMotorPosition_C()
    local ret,err = self.nxt:ResetMotorPosition("PORT_C",false,true)
    assert(ret,err)
end

function TestNxt:test29_ResetInputScaledValues_1()
    local ret,err = self.nxt:ResetInputScaledValue("PORT_1",true)
    assert(ret,err)
end

function TestNxt:test30_ResetInputScaledValues_2()
    local ret,err = self.nxt:ResetInputScaledValue("PORT_2",true)
    assert(ret,err)
end

function TestNxt:test31_ResetInputScaledValues_3()
    local ret,err = self.nxt:ResetInputScaledValue("PORT_3",true)
    assert(ret,err)
end

function TestNxt:test32_ResetInputScaledValues_4()
    local ret,err = self.nxt:ResetInputScaledValue("PORT_4",true)
    assert(ret,err)
end

LuaUnit:run()
