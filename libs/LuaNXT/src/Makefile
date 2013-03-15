# makefile for Lego NXT library for Lua

include ../config

# no need to change anything below here

MYLIB= core

SRC=  lnxt_core.c

HEADERS= lnxt_core.h 

OBJS= lnxt_core.o

TARGET= $(MYLIB).so

all:	$(TARGET)

$(TARGET):	$(OBJS)
	$(CC) -o $@ -shared $(OBJS)

$(OBJS): $(SRC) $(HEADERS)


clean:
	$(RM) -f $(TARGET) $(OBJS) $T core core.* a.out


