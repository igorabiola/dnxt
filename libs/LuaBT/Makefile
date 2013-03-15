include ../../config

INSTALL_FILES=luabt.so

all:
	cd src && $(MAKE)

clean:
	cd src && $(MAKE) clean

install: all
	cd src && $(MKDIR) -p $(INSTALL_CMOD)
	cd src && $(INSTALL_EXEC) $(INSTALL_FILES) $(INSTALL_CMOD)

doc:
	cd src && $(DOXYGEN) Doxyfile

cdoc:
	$(RM) -rf docs/html docs/latex 
