include ../config

install:
	cd luasocket-2.0.2 && $(MAKE) install
	cd luatimer-2.0.1 && $(MAKE) install
	cd alua-6.0 && $(MAKE) linux
	cd alua-6.0 && $(MAKE) install
	cd dalua && $(MAKE) install
	cd LuaBT && $(MAKE) install
	cd LuaUSB && $(MAKE) install
	cd LuaNXT && $(MAKE) install			

clean:
	cd luasocket-2.0.2 && $(MAKE) $@
	cd luatimer-2.0.1/unix && $(MAKE) $@
	cd alua-6.0/unix && $(MAKE) $@
	cd LuaBT && $(MAKE) $@
	cd LuaUSB && $(MAKE) $@
	cd LuaNXT && $(MAKE) $@
	
