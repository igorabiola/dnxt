# makefile for USB library for Lua

include ../config
# no need to change anything below here

MYLIB= luabt

SRC=  luabt.c       \
      luabt_socket.c \
      lclass.c

HEADERS= luabt.h lclass.h     

OBJS= luabt.o       \
      luabt_socket.o \
      lclass.o

TARGET= $(MYLIB).so

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) -lbluetooth -o $@ -shared $(OBJS)

$(OBJS): $(SRC) $(HEADERS)

doc:
	$(DOXYGEN) Doxyfile

cdoc:
	$(RM) -rf docs/html

clean:
	$(RM) -f $(TARGET) $(OBJS) $T core core.* a.out

