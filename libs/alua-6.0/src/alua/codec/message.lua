-- $Id: message.lua 164 2008-05-20 11:02:57Z brunoos $
--
-- All rights reserved. Part of the ALua project.
-- Detailed information regarding ALua's license can be found 
-- in the LICENSE file.
--

module("alua.codec.message", package.seeall)

--
-- Send a internal message.
--
function sendmsg(conn, msg)
   conn:send(msg)
end

--
-- Receive a new internal message.
--
function receivemsg(conn)
   return conn:receive()
end
