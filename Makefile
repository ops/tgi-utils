#
# Makefile for VIC-20 tgi_utils library
#

LIBRARY_BASE = tgi_utils
LIBRARY_SUFFIX = lib
LIBRARY := $(LIBRARY_BASE).$(LIBRARY_SUFFIX)

SYS = vic20

AR := ar65
AS := ca65
CC := cc65

# Additional C compiler flags and options.
CFLAGS += -g

# Additional assembler flags and options.
ASFLAGS += -g

# Set OBJECTS
LIB_OBJECTS := mg_export.o


.PHONY: clean

%: %.c
%: %.s

.c.o:
	$(CC) $(CFLAGS) -t $(SYS) $<
	$(AS) $(ASFLAGS) -t $(SYS) $(<:.c=.s)
	$(RM) $(<:.c=.s)

.s.o:
	$(AS) $(ASFLAGS) -t $(SYS) $<

$(LIBRARY): $(LIB_OBJECTS)
	$(AR) $(ARFLAGS) $@ $(LIB_OBJECTS)

clean:
	$(RM) $(LIB_OBJECTS)
	$(RM) $(LIBRARY)
	$(RM) *~
