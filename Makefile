CC=clang
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=`pkg-config --cflags gtk+-2.0`
LDLIBS=`pkg-config --libs gtk+-2.0`

#
# OCAML Makefile
# By : Team Gigatank3000
#
# TODO : "CFLAGS= -Wall -Wextra -Werror -std=c99 -O2"
#

all: obj/main
	mv obj/main ./ocrocaml

obj/main: obj/gui_gui.o obj/main.o

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ $(LDFLAGS) $(LDLIBS)


# TODO : there should be a way to do "obj/`path`_%.o: src/`path`/%.c
obj/gui_%.o: src/gui/%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f *~ *.o obj/* ./ocrocaml


# END