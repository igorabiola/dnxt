require "dnxt"
require "dnxtTripod"


mode = arg[1] or  "usb"

dnxt.nxtSetCommand("move", dnxtTripod.move)
dnxt.nxtSetCommand("moveAngle", dnxtTripod.moveAngle)
print ("tentando conextar ao nxt via", mode)
dnxt.nxtConnect(mode, "robot1", "00:16:53:07:58:F1")
print "iniciando servidor"
dnxt.initServer("127.0.0.1", 4321)
