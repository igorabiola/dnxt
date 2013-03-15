# makefile for USB library for Lua

include ../config
# no need to change anything below here

MYLIB= lusb

SRC=  lusb.c       \
      lusb_bus.c   \
      lclass.c     \
      lusb_config.c   \
      lusb_endpoint.c   \
      lusb_interface.c   \
      lusb_dev.c   \
      lusb_dev_handle.c   \
      lusb_print.c 

HEADERS= lusb.h  \
	 lclass.h     

OBJS= lusb.o       \
      lusb_bus.o   \
      lusb_config.o   \
      lusb_endpoint.o   \
      lusb_interface.o   \
      lusb_dev.o   \
      lusb_dev_handle.o   \
      lclass.o     \
      lusb_print.o 

TARGET= $(MYLIB).so

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) -lusb -o $@ -shared $(OBJS)

$(OBJS): $(SRC) $(HEADERS)

doc:
	$(DOXYGEN) Doxyfile

cdoc:
	$(RM) -rf ../docs/html

clean:
	$(RM) -f $(TARGET) $(OBJS) $T core core.* a.out

