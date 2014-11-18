CC=clang
CFLAGS= -g -Wall -Wextra -Werror -std=c99 -O2
LDFLAGS=`pkg-config --cflags gtk+-2.0`
LDLIBS=
GTKLIBS=`pkg-config --libs gtk+-2.0` -lm

#
# OCAML Makefile
# By : Team Gigatank3000
#
# TODO : "CFLAGS= -Wall -Wextra -Werror -std=c99 -O2"
#

SRC= ${wildcard ./src/*.c ./src/*/*.c}
OBJ= ${addprefix obj/,$(notdir $(SRC:.c=.o))}
VPATH= ${dir ${SRC}}
BUILDNAME= ocrocaml

all: obj/${BUILDNAME}
	mv obj/${BUILDNAME} ./${BUILDNAME}

obj/${BUILDNAME}: ${OBJ}
	$(CC) $(CFLAGS) $(GTKLIBS) -o obj/${BUILDNAME} obj/*.o

obj:
	mkdir obj

obj/%.o: %.c obj
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf *~ *.o obj/* ./${BUILDNAME} obj/

# END