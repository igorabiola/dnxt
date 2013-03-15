-------------------------------------------------------------------------------
-- Módulo Cliente
-------------------------------------------------------------------------------

local env = _G
local dalua = require "dalua"
module "dnxtClient"

--id do servidor
local serverID = nil
--
local cbs = {}
--endereço do servidor
local serverAddr = nil
--porta do servidor
local serverPort = nil

local terminals = {}

local servers = {}

timer = dalua.timer

local function send( ... )
	dalua.send(dalua.app.processes("nxt"), ...)
end

function registerServer( ids )
	env.print("registerServer")
	for k,v in env.pairs(ids) do
		env.table.insert(servers, v)
	end	
end

function getType()
	return "client"
end

function onJoin(event, status, app, id)
	if status == "error" then -- on error, 'id' is the error message
			env.print("Failed to join application '"..app.."': "..id)
	elseif id == dalua.self() then -- on success, 'id' is the process id
		env.print("Joined application "..app)
		dalua.send(dalua.self(), "dnxtClient.setup")
		env.print("Joined application end: "..app)
	else 
		dalua.send(id, "print", "Hello from "..dalua.self().."!")
	end
end

function linked()
	function applinked()
		dalua.events.ignore("dalua_app_link", applinked)
		env.print("Application Network is linked!")
		dalua.app.join("nxt")
	end
	dalua.events.ignore("dalua_link", linked)
	dalua.events.monitor("dalua_app_link", applinked)
	dalua.app.link(serverAddr, serverPort)
	env.print"linked"
	--dalua.timer.add(dalua.self(), frequency , 0, "teste")
end

function appinit()
   env.print(serverAddr, serverPort)
   dalua.events.monitor("dalua_link", linked)
   dalua.link(serverAddr, serverPort)
end

function init()
	dalua.app.init()
end

function exit()
	env.print( "exit" )
	dalua.app.leave("nxt")
	dalua.exit()
	env.print( "Terminando Client" )
end

function setup()
	env.print ("setup")
	--
	for k,v in env.ipairs(cbs) do
		env.print("registering cb ", v.frequency, v.cb, v.count, v.params)
		dalua.timer.add(dalua.self(), v.frequency , v.count, v.cb, v.params)
	end
	--]]
end

-----------------------------------------------------------------------------------------------------------------------
-- inicia loop do cliente
-- @param addr endereço do demon
-- @param port porta do demon
-- @param serverAddrParam endereço do servidor
-- @param serverPortParam porta do servidor
function initClient( addr, port, serverAddrParam, serverPortParam)
	serverAddr = serverAddrParam
	serverPort = serverPortParam
	--dalua.debug = true
	--dalua.app.debug = true
	--dalua.mutex.debug = true
	--dalua.timer.debug = true
	dalua.events.monitor("dalua_init", init)
	dalua.events.monitor("dalua_app_init", appinit)
	dalua.events.monitor("dalua_app_join", onJoin)
	dalua.init(addr, port)
	dalua.loop()
end

-----------------------------------------------------------------------------------------------------------------------
-- Registra função para ser chamada no cliente em um tempo determinado
-- @param callback (function) função a ser chamada
-- @param frequency frequencia de chamada da função em segundos.
-- @param count numero de vezes a callback deve ser chamada, zero para infinito.
-- @param ... parametros a serem pasados para a função.
function registerCallback( callback,frequency, count, ... )
	env.print ("registerCallback", callback,frequency, ...)
	env.table.insert(cbs, { cb = callback, frequency = frequency , count=count , params = ... } )
end


-----------------------------------------------------------------------------------------------------------------------
-- executa um comando no servidor.
-- @param robotID id do robo.
-- @param cmd comando a ser chamado.
-- @param mutexList lista de objetos de exclução mútua.
-- @param ... parametros a serem pasados para a função.
function executeCommand( robotID ,cmd, mutexList, ... )
	--env.print ("executeCommand", robotID,cmd, ...)
	send( "dnxt.executeCommand" ,robotID,cmd, mutexList, ...)
end

-----------------------------------------------------------------------------------------------------------------------
-- retorna id de broadcast para todos os robôs.
function allRobots()
 	return "ALL"
end

-----------------------------------------------------------------------------------------------------------------------
-- retorna a lista de servidores
function getServers()
	return servers
end

-----------------------------------------------------------------------------------------------------------------------
-- pede o valor de um sensor.
-- @param robotID id do robo.
-- @param port porta do sensor.
-- @param callback nome da função a ser chamada para retorno do valor.
function getSensorData( robotID, port, callback )
	--env.print ("getSensorData", robotID, port, callback)
	send("dnxt.sendSensorData",dalua.app.processes("nxt"), robotID, port, callback)
end

-----------------------------------------------------------------------------------------------------------------------
-- registra nos sevidores o cliente para receber o valor de um sensor.
-- @param robotID id do robo.
-- @param port porta do sensor.
-- @param frequency frequencia de chamada da função em segundos.
-- @param callback nome da função a ser chamada para retorno do valor.
-- @param lowspeed ( boolean ) indica se o sensor é de lowspeed.
function registerSensorCallback( robotID, port, frequency, callback, lowspeed )
	 send( "dnxt.registerSensorCallback",  dalua.app.processes("nxt") ,robotID, port, frequency, callback, lowspeed )
end

-----------------------------------------------------------------------------------------------------------------------
-- Remove o registro do cliente de receber o valor de um sensor.
-- @param robotID id do robo.
-- @param port porta do sensor.
function removeSensorCallback( robotID, port )
	env.print("client removeSensorCallback")
	send( "dnxt.removeSensorCallback", dalua.app.processes("nxt"), robotID, port )
end

-----------------------------------------------------------------------------------------------------------------------
-- Libera as regiões críticas.
-- @param mutexList vetor de nomes regiões críticas
function exitCR( mutexList )
	--[[	
	for k,v in env.pairs( mutexList ) do 
		env.print("saindo do mutex", k, v)
		dalua.mutex.leave(v) 
		env.print("saiu do mutex", k, v)
	end
	--]]
	send("dnxt.exitCR",mutexList)
end

function leaveCR( mutex )
	return function() 
		env.print("leaveCR", mutex)
	 	dalua.mutex.leave(mutex)
	end 
end

function wrapper(func, mutex, ...)
	env.print("wrapper", mutex)
	func(leaveCR(mutex) ,...)
	--dalua.timer.add(dalua.self(), 1 , 1, "dnxtClient.leaveCR", mutex)
	--leaveCR(mutex)
end

-----------------------------------------------------------------------------------------------------------------------
-- Chama função checando objeto de exclução mútua.
-- @param mutex objeto de exclução mútua.
-- @param func função a ser chamada.
-- @param ... parametros a serem pasados a função.
function mutexfunction( mutex, func, ...)
	env.print("mutexfunction", mutex)
	dalua.mutex.enter(mutex, wrapper, func, mutex, ...)
end

function createMutex( name )
	dalua.mutex.create(name, dalua.app.processes("nxt"))
end	


