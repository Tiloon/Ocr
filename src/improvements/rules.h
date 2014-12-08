#ifndef IMPROVE_RULES_H
#define IMPROVE_RULES_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <wchar.h>
#include <wctype.h>

#include "../redef.h"
#include "../main.h"

wchar_t * match_rule(long double **chars, size_t count,
        struct s_neural_network *network);

#endif
