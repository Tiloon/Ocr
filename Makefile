CC=clang
CFLAGS= -Wall -Wextra -std=c99 -O2
LDFLAGS=
LDLIBS=
 
# empty all rule to prevent clean being the default rule
all: src/main.o

gui:
	

clean:
	rm -f *~ *.o

 
# END