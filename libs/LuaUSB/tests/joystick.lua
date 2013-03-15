require("lusb")
print(lusb.version)

dev,err = lusb.find_dev( 0x040B , 0x6530 )

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
           dhandle:close()
           os.exit(1)
       end

       print("Succeded!")

       ret,err =  dhandle:claim_interface(0)
    end

    for i=0,1000  do
       s = dhandle:interrupt_read(0x81, 8,100000)
       print(string.byte(s , 1 , #s))
    end

    dhandle:release_interface(0)
    dhandle:close()
end


