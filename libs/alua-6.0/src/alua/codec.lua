-- $Id: codec.lua 167 2008-05-21 15:25:33Z brunoos $
--
-- All rights reserved. Part of the ALua project.
-- Detailed information regarding ALua's license can be found 
-- in the LICENSE file.
--

module("alua.codec", package.seeall)


-- Registered codecs (defined below)
local codecs

---------------------------------------------------------------------------
--                             Codec API
---------------------------------------------------------------------------

--
-- Select the codec based on the connection type.
--
function getcodec(name)
   return codecs[name]
end

--
-- Load the chunk.
--
function load(chunk)
   -- Put the inside the table for security reason
   chunk = "return {" .. chunk .. "}" 
   local f = loadstring(chunk)
   -- Without external access
   setfenv(f, {})
   local succ, val = pcall(f)
   if succ then
      return succ, val[1]
   end
   return false, val
end

--
-- Auxiliary function used to dump a Lua object.
-- This function does not serialize circular references in table,
-- it accepts only plain tables (tree).
--
function dump(obj)
   -- Verify the object type
   local tobj = type(obj)
   if tobj == "thread" or tobj == "userdata" or tobj == "function" then
      return ""
   end

   -- Recursively dump tables
   if tobj == "table" then
      local buf = "{"
      for k, v in pairs(obj) do
         local sk, sv
         local tk = type(k)
         local tv = type(v)
	 if (tk ~= "thread" and tk ~= "userdata" and tk ~= "function") and
            (tv ~= "thread" and tv ~= "userdata" and tv ~= "function") then
            buf = buf .. string.format("[%s] = %s,", dump(k), dump(v))
         end
      end
      return buf .. "}"
   elseif tobj == "string" then
      return string.format("%q", obj)
   else
      -- Number and booleans
      return tostring(obj)
   end
end

---------------------------------------------------------------------------
--                             Register the Codes
---------------------------------------------------------------------------

--
-- Since some codecs could use aliases for the auxiliaries functions above, 
-- we register the codecs here. (See 'stream' codec)
--
require("alua.codec.stream")
require("alua.codec.message")

codecs = {
   ["mempair"]     = alua.codec.message,
   ["mailbox"]     = alua.codec.message,
   ["mailbox:out"] = alua.codec.message,
   ["tcp:client"]  = alua.codec.stream,
}
