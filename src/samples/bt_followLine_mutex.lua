require "dnxtClient"
require "dalua"

local on = nil
function init(...)
	if not on then
		dnxtClient.executeCommand(dnxtClient.allRobots(),"startProgram","nil", "main.rxe", true )
		on = true
	end
	mutexRead()
end

function mutexRead()
	dnxtClient.executeCommand(dnxtClient.allRobots(),"readMsg",{"robot1"}, 12 , "processLight" );
end

function checkMovimentstatus(mutexList)
	dnxtClient.executeCommand(dnxtClient.allRobots(),"readMsg","nil", 10 , "endMovment" , mutexList);
end

function endMovment(inbox, msg, mutexList, mutexList2)
	if msg then
		msg = msg:sub(1, #msg-1)
		if msg == "ok" then
			
			dnxtClient.exitCR(mutexList2)
			return
		end
	end
	dalua.timer.add(dalua.self(), 1/500 , 1, "checkMovimentstatus", mutexList2)
end

local degree_cunt = 0
function processLight( inbox, msg, mutexList )
	local light = 0	
	if msg  then
		light = string.byte( msg, 1 , #msg )
	else		
		return
	end
	if  light < 40 then
		print("processDistance", "frente")
		dnxtClient.executeCommand(dnxtClient.allRobots(),"sendMsg","nil", 0, 0 )
		degree_cunt = 0
	else
		local inc = 15;		
		if degree_cunt > 180 then 
			cw = not cw
			degree_cunt = -degree_cunt
		end
		if cw then
			print("processLight", "esquerda", degree_cunt)
	        	dnxtClient.executeCommand(dnxtClient.allRobots(),"sendMsg","nil", 0, -90 );
		else
			print("processLight", "direita", degree_cunt)
	        	dnxtClient.executeCommand(dnxtClient.allRobots(),"sendMsg","nil", 0, 90 );
		end
		degree_cunt = degree_cunt + inc
	end
	checkMovimentstatus(mutexList)
end

dnxtClient.registerCallback("init", 1/5, 0)
print "iniciando cliente"
dnxtClient.initClient("127.0.0.1", 4322, "127.0.0.1", 4321)
