require("luabt")

res = luabt.scan_devices()

if res then
    for i,device in pairs(res) do
        print("Device #"..i)
        print("   Class: " .. device.class )
        print("   Name: " .. device.name )
        print("   Address: " .. device.address )
    end
else
    print("Error")
end
