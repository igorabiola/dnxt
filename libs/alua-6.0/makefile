include ../../config



all clean:
	cd unix; $(MAKE) $@


TO_TOP_SHARE:= \
	alua.lua

TO_ALUA_SHARE:=\
	alua

linux: 
	cd unix; $(MAKE) $@

install: all
	cd unix; $(MAKE) $@
	cd src; $(INSTALL_DATA) $(TO_TOP_SHARE) $(INSTALL_LMOD)
	cd src; $(MKDIR) $(INSTALL_LMOD)/alua $(INSTALL_LMOD)/alua/channel $(INSTALL_LMOD)/alua/codec $(INSTALL_LMOD)/alua/daemon $(INSTALL_LMOD)/alua/util
	cd src/alua; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/alua
	cd src/alua/channel; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/alua/channel
	cd src/alua/codec; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/alua/codec
	cd src/alua/daemon; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/alua/daemon
	cd src/alua/util; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/alua/util

