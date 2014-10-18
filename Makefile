CC=clang
CFLAGS= -g -Wall -Wextra -Wall -std=c99 -O2
LDFLAGS=`pkg-config --cflags gtk+-2.0`
LDLIBS=
#LDLIBS=`pkg-config --libs gtk+-2.0`
GTKLIBS=`pkg-config --libs gtk+-2.0`


#
# OCAML Makefile
# By : Team Gigatank3000
#
# TODO : "CFLAGS= -Wall -Wextra -Werror -std=c99 -O2"
#

all: obj/ocrocaml
	mv obj/ocrocaml ./ocrocaml

obj/ocrocaml: obj/split_lines.o obj/morphology.o obj/convert_pic.o obj/filters.o obj/sample_filter.o obj/gui.o obj/loader.o obj/main.o
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
