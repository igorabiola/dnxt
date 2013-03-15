-------------------------------------------------------------------------------
-- Módulo Servidor
-------------------------------------------------------------------------------

local dalua = require "dalua"
local lnxt  = require "lnxt"
local lusb  = require "lusb"
local luabt = require "luabt"
local env = _G

module "dnxt"

local ltimer = nil
local alua = dalua.alua
local sensorCBMap = {}
local commands = {}

local nxt = nil

--Lista dos robos
local robots = {}

--Lista de nomes do robos
local robotNames = {}
--Lista de timers
local timers = {}

local offline = false

function getType()
	return "server"
end


-------------------------------------------------------------------------------
-- Conecta ao lego nxt. 
-- @param mode modo de conexão ( usb  ou bt )
-- @param name identficador do robo.
-- @param mac opcional, identificador mac do lego nxt
function nxtConnect( mode, name, mac )
	env.print "conectando com o nxt"
	local nxt = nil
	if not offline then
		local  nxtdev = nil
		local err = nil
		if mode == "usb" then
		    --require "lusb" 
			nxtdev, err  = lusb.find_dev( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct )
			env.print( lnxt.usbconf.iVendor , lnxt.usbconf.iProduct, lusb, nxtdev)
		else
		    	--require "luabt" 
		  	nxtdev, err  = luabt.connect(mac)
		end
		if  nxtdev == nil  then
			env.print(nxtDev ,err)
			quit()
			return
		end
		nxt,err = lnxt.new( nxtdev )
		if  nxt == nil then
			env.print(err)
			quit()
			return
		end
		--OK
		
		env.print( "nxt = " , nxt)
		nxt:KeepAlive()
		init_usonic(nxt)
	else
		nxt = name.."_teste offline"
	end
	robots[name] = nxt
	env.table.insert(robotNames, name)
	return
end


-------------------------------------------------------------------------------
-- Cadastra função para ser chamada remotamente. 
-- @param name nome pelo qual a função será chamada.
-- @param command (function) a função.
function nxtSetCommand( name, command )
	commands[name] = command
end





-----------------------------------------------------------------------------------------------------------------------
-- Entra zona de exclução mútua. 
-- @param mutexList lista de objetos de exclução mútua.
-- @param mutexIdx id do objeto de exclução mútua, deve ser uma chave da lista mutexList.
-- @param func (function) função a ser chamada quando conseguir entrar na zona de exclução mútua.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot (object) robo.
-- @param ... outros parametros para serem repasados a func.
local function enterMutex( mutexList, mutexIdx, func,robotID , robot , ... )
	env.print("enterMutex", mutexList[mutexIdx], func, robot )
	if mutexList[mutexIdx] then 
		env.print("enterMutex-mutex loop", mutexList[mutexIdx], mutexIdx, func, robot )
		dalua.mutex.enter( mutexList[mutexIdx], enterMutex, mutexList, (mutexIdx + 1) , func ,robotID,  robot, ...)
	else
		env.print("enterMutex-mutex call", mutexList[mutexIdx], func, robot )
		func(robotID, robot, mutexList, ...)
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Executa um comando previamente cadastrado.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param name nome do comando a ser executado.
-- @param mutexList lista de objetos de exclução mútua.
-- @param ... outros parametros para serem repasados a func.
function executeCommand( robotID,name, mutexList , ... )
	env.print("executeCommand", robotID, name, mutexList, ...)
	local function callCmd( func, robotName,robot , ... )
		if env.type(mutexList) == "table"  then
			env.print("pre enterMutex", robotID, name, mutexList, ...)
			enterMutex( mutexList, 1, func, robotName,robot, ... )
		else
			func(robotName, robot,nil, ...)
		end
	end
	if robotID == "ALL" then
		for k, v in env.pairs(robots) do
			callCmd( commands[name],k, v, ...)
		end
	else
		if robots[robotID] then
			callCmd( commands[name],robotID, robots[robotID] , ...)
		end
	end
end

function quit()
	env.print("Terminando Aplicacao")
	--dalua.exit()
	os.exit()
end

-----------------------------------------------------------------------------------------------------------------------
-- Inicia o loop do servidor.
-- @param addr endereço ip do servidor.
-- @param port porta do servidor.
function initServer(addr, port)
	--dalua.debug = true
	--dalua.app.debug = true
	--dalua.mutex.debug = true
	registerDefaultCommands()
	dalua.events.monitor("dalua_init", init)
	dalua.events.monitor("dalua_app_init", appinit)
	dalua.events.monitor("dalua_app_join", onJoin)
	dalua.events.monitor("dalua_app_create", onCreate)
	dalua.init(addr, port)
	dalua.loop()
end


local function createRobotMutex( idx, name, app )
	dalua.mutex.create(name, {dalua.self()})
end

local function addToRobotMutex( idx, name, proc )
	env.print("addToRobotMutex", idx, name, proc)
	dalua.mutex.add( name, proc )
end


function onCreate( event, status, app )
	env.table.foreach( robotNames, createRobotMutex )
end

function appinit()
	env.print "appinit"
	dalua.app.create("nxt")
end

function init()
	dalua.app.init()
end


function onJoin(event, status, app, id)
	if status == "error" then -- on error, 'id' is the error message
			env.print("Failed to join application '"..app.."': "..id)
	elseif id == dalua.self() then -- on success, 'id' is the process id
		env.print("Joined application "..app)
		
	else -- someone else joined the application
		env.print(id.." joined nxt app")
		for k,v in env.pairs( robotNames) do addToRobotMutex(k,v,id ) end
		dalua.send(id, "dnxtClient.registerServer", robotNames)
		
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Inicia o sensor ultrasonico do robo.
-- @param robot robo.
function init_usonic(robot)
    robot:SetInputMode( "PORT_4" , "LOWSPEED_9V" , "RAWMODE" )
    lnxt.sleep(300)
    local _ = robot:LsRead("PORT_4") -- Clean last stuff
    robot:LsWrite( "PORT_4",env.string.char(  0x02 , 0x41, 0x02), 0,false )
end
--[[
function get_distance( robot )
    local start = env.os.time()
    local delay = 50
    robot:LsWrite( "PORT_4",env.string.char( 0x02 , 0x42) , 1 , false)
    lnxt.sleep(delay)
    local value ,err, aux =  robot:LsGetStatus( "PORT_4")
    if not value then return false, err end 
    local count = 0
    while value < 1 and count < 5 do
	robot:LsWrite( "PORT_4",env.string.char(0x02 , 0x42), 1 , false) 
        lnxt.sleep(delay)
        value ,err, aux =  robot:LsGetStatus( "PORT_4")
	count = count + 1 
    end
    if count >= 10 then return false, "timeout" end
    local time = env.os.time() - start
    env.print("get_distance enlapsed:", time)
    return robot:LsRead("PORT_4")
end
--]]

-----------------------------------------------------------------------------------------------------------------------
-- le dados do sensor de ultrasom e calcula distancia de obstaculo.
-- @param robot robo.
function get_distance( robot )
    local start = env.os.time()
    robot:LsWrite( "PORT_4",env.string.char( 0x02 , 0x42) , 1 , false)
    local value ,err, aux =  robot:LsRead("PORT_4")
    env.print( value ,err, aux )
    if value then 
	local time = env.os.time() - start
    	env.print("get_distance enlapsed:", time)
	return value 
    end
    local count = 0
    while not value  and count < 5 do
        value ,err, aux =  robot:LsRead("PORT_4")
	env.print( value ,err, aux )
	count = count + 1 
    end
    if count >= 10 then return false, "timeout:"..err end
    local time = env.os.time() - start
    env.print("get_distance enlapsed:", time)
    return value, err--robot:LsRead("PORT_4")
end



function sendSensorData( clientID ,robotID, port, callback, lowspeed )
	env.print( "sendSensorData",  clientID ,robotID, port, callback)
	if robotID == "ALL" then
		for k,nxt in env.pairs( robots ) do
			if not offline then
				local value, err
				if not lowspeed then 
					value, err = nxt:GetInputValues( port )
				else
					value, err = get_distance( nxt )
				end
				dalua.send( clientID, callback, k, port, value, err )
			else			
				dalua.send( clientID, callback, k, port , "offline mode data", nil )
			end
		end 	
	else
		local nxt = robots[robotID]
		
		if nxt then	
			if not offline then 
				local value, err
				if not lowspeed then 
					value, err = nxt:GetInputValues( port )
				else
					value, err = get_distance( nxt )
				end
				dalua.send( clientID, callback, robotID, port , value, err )
			else
				dalua.send( clientID, callback, robotID, port , "offline mode data", nil )
			end
		end
	end
end


function registerSensorCallback( clientID, robotID, port, frequency, callback, lowspeed )
	env.print" registerSensorCallback "
	local timer = dalua.timer.add(dalua.self(), frequency , 0, "dnxt.sendSensorData",  clientID, robotID, port ,callback, lowspeed )
	timers[ clientID..robotID..port ] = timer
end


function removeSensorCallback( clientID, robotID, port )
	env.print("removeSensorCallback", clientID, robotID, port)
	local key = clientID..robotID..port
	env.print("key=", key, "timers[key]=", timers[key])
	dalua.timer.remove(timers[key])
	timers[key] = nil
end

-----------------------------------------------------------------------------------------------------------------------
-- Libera as regiões críticas.
-- @param mutexList vetor de nomes regiões crítica
function exitCR( mutexList )
	for k,v in env.pairs( mutexList ) do 
		env.print("saindo do mutex", k, v)
		dalua.mutex.leave(v) 
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- cria uma região crítica.
-- @param name nome região crítica
function createMutex( name )
	dalua.mutex.create(name, dalua.app.processes("nxt"))
end



function registerDefaultCommands()
	nxtSetCommand("sendMsg", sendMsg)
	nxtSetCommand("readMsg", readMsg)
	nxtSetCommand("startProgram", startProgram)
	nxtSetCommand("stopProgram", stopProgram)
	nxtSetCommand("exitCR", exitCR)
end

-----------------------------------------------------------------------------------------------------------------------
-- Envia uma mensagem para o programa em execução no nxt.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
-- @param mailbox_index número da mailbox.
-- @param msg mensagem.
function sendMsg(robotID, robot, mutexList , mailbox_index ,msg)
	env.print ("sendMsg", robotID, robot, msg)
	local status, err = robot:MessageWrite(mailbox_index, msg, false)
	if not status then
		env.print("error:", err)	
	end 
end

-----------------------------------------------------------------------------------------------------------------------
-- Lê a próxima mensagem da fila.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
-- @param inbox número a mailbox a ser lida.
-- @param callback (function) função para processar a mensagem.
function readMsg(robotID, robot, mutexList, inbox , callback, ... )
	env.print ("readMsg", robotID, robot, callback, ...)
	inbox_num, msg = robot:MessageRead(inbox, inbox, true)
	if inbox_num then 
		dalua.send(dalua.app.processes("nxt"), callback, inbox_num ,msg, mutexList or env.type(mutexList), ...)
	else	
		env.print("readMsg", mutexList, ...)
		dalua.send(dalua.app.processes("nxt"), callback, "nil" ,"nil", mutexList or env.type(mutexList), ...)
	end
end

-----------------------------------------------------------------------------------------------------------------------
-- Inicia a execução de um programa nativo.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
-- @param mutexList lista de objetos de exclução mútua.
-- @param program nome do programa a ser iniciado.
-- @param response (boolean) esperar o inicio da execução.
function startProgram( robotID, robot, mutexList , program, response )
	env.print ("startProgam", robotID, robot, program )
	local result, err = robot:StartProgram(program, response)
	env.print("startProgam", result, err)
end

-----------------------------------------------------------------------------------------------------------------------
-- Para a execução de um programa nativo.
-- @param robotID id do robo sobre o qual a func de ser chamada.
-- @param robot objto LuaNxt.
function stopProgram( robotID, robot )
	robot:StopProgram(false);	
end

