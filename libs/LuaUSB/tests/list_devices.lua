require("lusb")
print(lusb.version)
busses = lusb.get_busses()

for _,bus in pairs(busses) do
    devices, err = bus:devices()

    if devices == nil then print(err); os.exit() end

    for _,dev in pairs(devices) do
        lusb.print_dev(dev)
    end

end
