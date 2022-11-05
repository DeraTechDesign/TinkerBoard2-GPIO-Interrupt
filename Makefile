ifneq ($V,1)
Q ?= @
endif

#DEBUG	= -g -O0
DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lwiringPi -lwiringPiDev -lpthread -lm -lsqlite3

# Should not alter anything below this line
###############################################################################

SRC	=	interruptTest.c

OBJ	=	$(SRC:.c=.o)

BINS	=	$(SRC:.c=)

interruptTest:	interruptTest.o
	$Q echo [link]
	$Q $(CC) -o $@ interruptTest.o $(LDFLAGS) $(LDLIBS)

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) *~ core tags $(BINS)

depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
