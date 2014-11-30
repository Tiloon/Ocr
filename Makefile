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
OBJ= ${notdir ${SRC:.c=.o}}
VPATH= ${dir ${SRC}}
BUILDNAME= ocrocaml

all: ${BUILDNAME}

${BUILDNAME}: ${OBJ}
	$(CC) $(CFLAGS) $(GTKLIBS) -o ${BUILDNAME} *.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS) $(LDLIBS)

clean: proper
	rm -rf ./${BUILDNAME}

proper:
	rm -rf *.o *~

# END
