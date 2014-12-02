#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../redef.h"

struct s_dictionary {
    char **words; // word list sorted by size the by alphabetical order
    size_t *indexes;
};

char * approcimative_match(long double **chars, size_t count, char *text,
        size_t text_len, struct s_dictionary *dictionary, char *charset,
        size_t charset_count);

#endif
