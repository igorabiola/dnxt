include config

FILES = dnxt.lua dnxtClient.lua dnxtTripod.lua
FILES_INSTALLDIR = $(INSTALL_LMOD)

all:install

linux: install

libs:
	cd libs && $(MAKE)

clean:
	cd libs && $(MAKE) clean

install: 
	cd libs && $(MAKE)
	cd src; $(MKDIR) -p $(FILES_INSTALLDIR)
	cd src; $(INSTALL_DATA) $(FILES) $(FILES_INSTALLDIR)

doc:
	cd src && $(DOXYGEN) Doxyfile

cdoc:
	$(RM) -rf docs/html docs/latex 
