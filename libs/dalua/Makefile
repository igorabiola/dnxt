include ../../config

TO_TOP_SHARE:= \
	dalua.lua

install:
	$(INSTALL_DATA) $(TO_TOP_SHARE) $(INSTALL_LMOD)
	$(MKDIR) $(INSTALL_LMOD)/dalua/samples
	cd dalua; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/dalua
	cd dalua/samples; $(INSTALL_DATA) *.lua $(INSTALL_LMOD)/dalua/samples 
