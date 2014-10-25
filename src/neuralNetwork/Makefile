CC=clang
CFLAGS= -Wall -Wextra -Wall -std=c99 -O2
LDFLAGS=
LDLIBS=-lm

#
# OCAML neuralNetwork Makefile
# By : Team Gigatank3000
#
# TODO : "CFLAGS= -Wall -Wextra -Werror -std=c99 -O2"
#

all: main.o network.o
	clang -Wall -Wextra -Wall -std=c99 -O2 neuralNetwork.c tests.c -lm -o tests


clean:
	rm -rf *~ *.o obj/* ./ocrocaml obj/


# END
