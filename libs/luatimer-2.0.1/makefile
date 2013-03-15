include ../../config



all clean:
	cd unix; $(MAKE) $@


TO_TOP_SHARE:= \
	luatimer.lua

linux: 
	cd unix; $(MAKE) $@

install: all
	cd unix; $(MAKE) linux
	cd lua; $(INSTALL_DATA) $(TO_TOP_SHARE) $(INSTALL_LMOD)
	
	

