CC=clang
CFLAGS= -Wall -Wextra -Wall -std=c99 -O2
LDFLAGS=`pkg-config --cflags gtk+-2.0`
LDLIBS=`pkg-config --libs gtk+-2.0` -lm

#
# OCAML Makefile
# By : Team Gigatank3000
#
# TODO : "CFLAGS= -Wall -Wextra -Werror -std=c99 -O2"
#

all: obj/main
	mv obj/main ./ocrocaml

obj/main: obj/gui.o obj/loader.o obj/main.o

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
