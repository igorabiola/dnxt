include ../../config

CORELIB = core.so
FILES   = usb.lua lnxt.lua bluetooth.lua

CORE_INSTALLDIR  = $(INSTALL_CMOD)/lnxt
FILES_INSTALLDIR = $(INSTALL_LMOD)/lnxt


all:
	cd src && $(MAKE)

clean:
	cd src && $(MAKE) clean

install: all
	cd src && $(MKDIR) -p $(CORE_INSTALLDIR)
	cd src && $(MKDIR) -p $(FILES_INSTALLDIR)
	cd src && $(INSTALL_DATA) $(FILES) $(FILES_INSTALLDIR)
	cd src && $(INSTALL_EXEC) $(CORELIB) $(CORE_INSTALLDIR)

doc:
	cd src && $(DOXYGEN) Doxyfile
	cd src && luadoc -d ../docs/luadoc *.lua

cdoc:
	$(RM) -rf docs/html docs/latex docs/luadoc/*
