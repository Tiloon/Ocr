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

all:
	clang -Wall -Wextra -Wall -std=c99 -O2 network.c layer.c learning.c nn_main.c -lm -o main -D_NN_TEST


clean:
	rm -rf *~ *.o ./main


# END
