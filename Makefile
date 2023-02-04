# Makefile

CC = gcc
CFLAGS = `pkg-config --cflags gdk-x11-3.0 gdk-3.0 gtk+-3.0`# -g -fsanitize=address -Wall -Wextra 
LDLIBS = `pkg-config --libs gdk-x11-3.0 gdk-3.0 gtk+-3.0`
EXE = bin/vimshit

ListDir = Colorations
SRC = $(wildcard *.c) $(foreach folder,$(ListDir),$(wildcard $(folder)/*.c))
OBJ = ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

#all: ${OBJ}
#all: $(EXE)
all: ${OBJ}
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) $(LDLIBS)


$(foreach f, $(EXE), $(eval $(f):))

-include ${DEP}

.PHONY: clean

clean:
	$(RM) $(OBJ)
	$(RM) $(EXE)
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
# END
