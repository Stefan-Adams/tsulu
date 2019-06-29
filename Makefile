#
# commands
#
CC          = /usr/bin/gcc
RM          = /bin/rm -f
CP          = /bin/cp -f
IN          = /usr/bin/indent -kr -i4


#
# flags
#
#CPPFLAGS    = -D_DEBUG 
CPPFLAGS    = 
#CFLAGS      = -D_DEBUG
INCLUDES    = `/opt/libusb-0.1.4/bin/libusb-config --cflags`
LDFLAGS     = `/opt/libusb-0.1.4/bin/libusb-config --libs`
LIBRARIES   = -Wl,--rpath -Wl,/opt/libusb/lib


#
# file defs
#
TARGET_sulu  = sulu
SOURCE_sulu  = \
	main.c \
	lib_uproar.c
OBJECT_sulu  = $(SOURCE_sulu:.c=.o)
SOURCES     = $(SOURCE_sulu)


#
# targets
#
default: all

all: $(TARGET_sulu) 

clean:
	$(RM) $(TARGET_sulu)
	$(RM) *.o

indent:
	$(IN) *.h *.c
	$(RM) *.h~ *.c~

depend: $(SOURCES)
	$(CC) -MM $(CPPFLAGS) $(CFLAGS) $(INCLUDES) $(SOURCES) > makedepend
	
$(TARGET_sulu): $(OBJECT_sulu)
	$(CC) -o $(TARGET_sulu) $(OBJECT_sulu) $(LDFLAGS) $(LIBRARIES)
	$(RM) *.o


#
# rules
#
%.o: %.c
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(INCLUDES) $<


#
# makedepend 
#
# DO NOT DELETE THIS LINE -- make depend depends on it.

main.o: main.c main.h lib_uproar.h
lib_uproar.o: lib_uproar.c main.h lib_uproar.h
