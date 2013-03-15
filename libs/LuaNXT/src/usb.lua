-------------------------------------------------------------------------------
-- LuaNXT USB Functions
-- @release 0.2
-------------------------------------------------------------------------------


module( "lnxt.usb", package.seeall )

-------------------------------------------------------------------------------
-- Executes a Nxt command through the USB connection
-- @param self NXT device connection
-- @param msg protocol msg that contains the command
-- @param ret boolean that defines if the command has a return
function exec_cmd ( self, msg , ret )
    --print("cmd: ",string.byte(msg,1,#msg))
    self.dhandle:bulk_write( lnxt.usbconf.OUT_ENDP , msg , lnxt.usbconf.TIMEOUT )
    
    if ret then
        local s , err = self.dhandle:bulk_read(lnxt.usbconf.IN_ENDP, 30000, lnxt.usbconf.TIMEOUT)
        if s == nil then
            print("Error getting device return string")
            print(err)
        else
           -- print( string.byte(s,1, #s) )
        end
        return s,err
    end
end

-------------------------------------------------------------------------------
-- Claim usb device 
-- @param dev USB Device
function claim_dev(dev)
    if dev == nil then 
        print("Device not found!") 
        os.exit();
    else
        dhandle,err = dev:open()
        if not dhandle then  print(err) ; os.exit(0) end

        print( dhandle:get_string_simple(1)  )

		if (os.getenv("OS") == "Windows_NT") then
			print (dhandle:set_configuration(1))
		end
		
        ret,err =  dhandle:claim_interface(0)
		if (os.getenv("OS") ~= "Windows_NT") then
	        while  not ret do
	           print( err .. "\ntrying do detach kernel driver")
	           ret,err = dhandle:detach_kernel_driver_np(0)

	           if not ret then
	               print(err .. "\nFailed to detach kernel driver.\n Exiting")
	               dhandle:close()
	               os.exit(1)
	           end

	           print("Succeded!")

	           ret,err =  dhandle:claim_interface(0)
	        end
		else
			if not ret then  print(err) ; os.exit(0) end
		end
--]]
        return dhandle
    end
end

