-------------------------------------------------------------------------------
-- Módulo Auxiliar
-------------------------------------------------------------------------------


local dnxt = require "dnxt"
local lnxt  = require "lnxt"
local dalua = require "dalua"
local env = _G
module "dnxtTripod"
offline = false

-----------------------------------------------------------------------------------------------------------------------
-- Move o robô baseado nos valores de x, y.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
-- @param x componence x do movimento, deve varias entre -128 e 128.
-- @param y componence y do movimento, deve varias entre -128 e 128.
-- @param tacho_limit limite de rotações, 0 para ilimitado.
function move(robotID , nxt, mutexList , x, y, tacho_limit )
	z = z or 0
	env.print( "move", x, y, z)
	local posx =   -(( ( x-128 )/128 )*100 ) - (  ((y-128)/128)*100 )
	local posy =   -(((x-128)/128)*100) + (  ((y-128)/128)*100 )

	if not offline then
		dalua.send(dalua.self(),"dnxtTripod.callRobot",robotID, "dnxtTripod._testIdle","SetOutputState", "PORT_B", posx  , "MOTORON", "MOTOR_SPEED" , 0 , "RUNNING", tacho_limit)
		dalua.send(dalua.self(), "dnxtTripod.callRobot" ,robotID,"dnxtTripod._testIdle","SetOutputState", "PORT_C", posy , "MOTORON", "MOTOR_SPEED" , 0 , "RUNNING", tacho_limit)
	end
end


function moveAngle(robotID , nxt, mutexList , x, y, z )
	local z = z or 0
	env.print( "moveAngle")
	local posx =   -( y*75 + ( x*75 )  )
	local posy =   -( y*75 - ( x*75 ) )
	env.print( "moveAngle", posx, posy)

	if not offline then
		
		nxt:SetOutputState( "PORT_B", posx   , "MOTORON", "MOTOR_SPEED" , 0 , "RUNNING", z )
		nxt:SetOutputState( "PORT_C", posy , "MOTORON", "MOTOR_SPEED" , 0 , "RUNNING", z )
	end
end


-----------------------------------------------------------------------------------------------------------------------
-- Move o robô para frente.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
function forward(robotID, robot, mutexList )
	env.print ("forward", robotID, robot, mutexList )
	if not offline then
		robot:SetOutputState( "PORT_B",  80 , "MOTORON_REGULATED", "MOTOR_SYNC" , 0 , "RUNNING", 50 )
    		robot:SetOutputState( "PORT_C",  80 , "MOTORON_REGULATED", "MOTOR_SYNC" , 0 , "RUNNING", 50 )
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Move o robô para trás.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
function back(robotID,robot, mutexList )
	env.print ("back",robotID,robot, mutexList  )
	if not offline then
		robot:SetOutputState( "PORT_B",  -70 , "MOTORON_REGULATED", "MOTOR_SYNC" , 0 , "RUNNING", 50 )
    		robot:SetOutputState( "PORT_C",  -70 , "MOTORON_REGULATED", "MOTOR_SYNC" , 0 , "RUNNING", 50  )
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Para o robô.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
function stop(robotID,robot, mutexList)
	env.print ("stop", robot )
	if not offline then
	    robot:ResetMotorPosition( "PORT_B" , true )
            robot:ResetMotorPosition( "PORT_C" , true )
            robot:SetOutputState( "PORT_B",  0 , "MOTORON", "MOTOR_SPEED" , 0 , "IDLE", 0 )
            robot:SetOutputState( "PORT_C",  0 , "MOTORON", "MOTOR_SPEED" , 0 , "IDLE", 0 )
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Rotaciona o robô para direita.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
-- @param degrees ângulo de rotação.
function rotateRight(robotID, robot, mutexList, degrees  )
	env.print ("right",robotID, robot, degrees )
	if not offline then

		robot:SetOutputState( "PORT_B", -90 , "MOTORON_REGULATED", "MOTOR_SPEED" , -100 , "RUNNING", degrees )
		robot:SetOutputState( "PORT_C", 90 , "MOTORON_REGULATED", "MOTOR_SPEED" , 100 , "RUNNING", degrees )
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Rotaciona o robô para esquerda.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
-- @param degrees ângulo de rotação.
function rotateLeft(robotID, robot, mutexList , degrees)
	env.print ("left",robotID,  robot, degrees )
	if not offline then
		robot:SetOutputState( "PORT_B", 90 , "MOTORON_REGULATED", "MOTOR_SPEED" , 100 , "RUNNING", degrees )
		robot:SetOutputState( "PORT_C", -90 , "MOTORON_REGULATED", "MOTOR_SPEED" , -100 , "RUNNING", degrees )
	end
end


