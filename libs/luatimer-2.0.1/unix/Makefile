include ../../../config

#----------------------
# Inform the location to intall the C module
CPATH=$(INSTALL_CMOD)

# Edit the line below to inform the Lua headers directory, if necessary
LUAINC=-I$(LUA_INC)

# For Mac OS X: set the system version
MACOSX_VERSION=10.4


#----------------------
# Do not edit this part

OBJS=luatimer.o
CMOD=luatimer.so

BSD_CFLAGS=-O2 -fpic
BSD_LDFLAGS=-O -shared -fpic

LNX_CFLAGS=-O2 -fpic
LNX_LDFLAGS=-O -fpic -shared

MAC_ENV=env MACOSX_DEPLOYMENT_TARGET=$(MACOSX_VERSION)
MAC_CFLAGS=-O2 -fno-common
MAC_LDFLAGS=-bundle -undefined dynamic_lookup

#CC=gcc
#LD=$(MYENV) gcc
#CFLAGS=$(LUAINC) $(MYCFLAGS)
#LDFLAGS=$(MYLDFLAGS)

.PHONY: all clean install none linux bsd macosx

all: none

none:
	@echo "Usage: make <platform>"
	@echo "  * linux"
	@echo "  * bsd"
	@echo "  * macosx"

install:
	cp $(CMOD) $(CPATH)

linux:
	@echo "Build for Linux"
	@echo "---------------"
	@make $(CMOD) MYCFLAGS="$(LNX_CFLAGS)" LDFLAGS="$(LNX_LDFLAGS)"

bsd:
	@echo "Build for BSD"
	@echo "-------------"
	@make $(CMOD) MYCFLAGS="$(BSD_CFLAGS)" LDFLAGS="$(BSD_LDFLAGS)"

macosx:
	@echo "Build for Mac OS X $(MACOSX_VERSION)"
	@echo "------------------------"
	@make $(CMOD) MYCFLAGS="$(MAC_CFLAGS)" LDFLAGS="$(MAC_LDFLAGS)" MYENV="$(MAC_ENV)"


$(CMOD): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f *.o *.so
