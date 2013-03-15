-------------------------------------------------------------------------------
-- LuaNXT Bluetooth Functions
-- @release 0.2
-------------------------------------------------------------------------------


module("lnxt.bluetooth", package.seeall )

-------------------------------------------------------------------------------
-- Executes a Nxt command through the Bluetooth connection
-- @param self NXT device connection
-- @param msg protocol msg that contains the command
-- @param ret boolean that defines if the command has a return
-- @return if ret == true returns response message
function exec_cmd ( self, msg , ret )
    print("cmd: ",string.byte(msg,1,#msg))
    self.socket:write( lnxt.core.putBTHeader( msg ) )

    if ret then
        local s = lnxt.core.stripBTHeader(self.socket:read(2))
        local err = "Error getting device return string"
        if s == nil then
            print(err)
        else
            print( string.byte(s,1, #s) )
        end
        return s,err
    end
end


