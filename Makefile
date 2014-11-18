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

SRC= ${wildcard ./src/*.c} ${wildcard ./src/*/*.c}
OBJ= ${addprefix obj/,$(notdir $(SRC:.c=.o))}

all: obj/ocrocaml
	mv obj/ocrocaml ./ocrocaml

obj/ocrocaml: ${OBJ}
	$(CC) $(CFLAGS) $(GTKLIBS) -o obj/ocrocaml obj/*.o

obj:
	mkdir obj

obj/%.o: src/%.c obj
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

# TODO : there should be a way to do "obj/`path`_%.o: src/`path`/%.c
obj/%.o: src/*/%.c obj
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf *~ *.o obj/* ./ocrocaml obj/


# END