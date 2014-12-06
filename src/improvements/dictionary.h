#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wchar.h>

#include "../redef.h"

struct s_dictionary {
    wchar_t **words; // word list sorted by size the by alphabetical order
    size_t *indexes;
};

wchar_t * approcimative_match(long double **chars, size_t count, wchar_t *text,
        size_t text_len, struct s_dictionary *dictionary, wchar_t *charset,
        size_t charset_count);

struct s_dictionary * load_dictionary(char *filename);

#endif
