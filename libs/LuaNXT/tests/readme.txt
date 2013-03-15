There are two types of test:
    * The basic ones
    * The unit test

===============================================
The basic ones can be executed like:

$ lua nxttest.lua [bt|usb] testname.lua

The basic tests are:
    motors.lua
    music.lua
    doremifa.lua
    sensors.lua
    devinfo.lua

==============================================
The unit test can be found in the unit folder
Just do:

$ lua unit/nxt.lua [bt|usb]

note that the boot command is only available
on USB connections
    
