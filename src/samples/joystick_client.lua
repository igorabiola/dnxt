require "dnxtClient"
require "dalua"
require "lusb"

local on = nil
function setup(...)
	print "init"
--[
	if not on then
		initJoystick()
		on = true
		print "fim initJoystick"
	end
	getJoystickStatus()
--]]
end

function initJoystick()
	-- 0x045e:0x00e1
	print ("initJoystick")
	dev,err = lusb.find_dev( 0x044f , 0xb106 )
	print "joystick obtido"
	if dev == nil then 
	    print(err) 
	else
	    dhandle,err = dev:open()
	    if not dhandle then  print(err) ; os.exit() end

	    print( dhandle:get_string_simple(1)  )
	    print( dhandle:get_string_simple(2)  )
	

	    ret,err =  dhandle:claim_interface(0)
	    while  not ret do
	       print( err .. "\ntrying do detach kernel driver")
	       ret,err = dhandle:detach_kernel_driver_np(0)

	       if not ret then
		   print(err .. "\nFailed to detach kernel driver.\n Exiting")
		   --dhandle:close()
		   --os.exit(1)
	       end

	       print("Succeded!")

	       ret,err =  dhandle:claim_interface(0)
	    end
	end
end

function procJoystick()
	print "procJoystick"
	s, err = dhandle:interrupt_read(0x81, 21,10)
	--s, err = dhandle:bulk_read(0x81, 21,5)
	--print "depois de dhandle:interrupt_read"
	if err == nil then
		a, b, c, xi, yi, zi = string.byte(s , 1 , #s)
	else
		if err ~= "No error" then	
			print("err =",err)
		end
		
	end
	return a, b, c, xi, yi, zi, err
end

function getJoystickStatus()
	a, b, c, xi, yi, zi, err = procJoystick()
	sendMoveOrder(yi, xi, zi)
end

function sendMoveOrder( x, y, z )
	print("sendMoveOrder", x, y)
	dnxtClient.executeCommand(dnxtClient.allRobots(),"move","nil", x, y, 60 );
end



dnxtClient.registerCallback("setup", 1/3, 100)
print "iniciando cliente"
dnxtClient.initClient("127.0.0.1", 4322, "127.0.0.1", 4321)
