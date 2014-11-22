#ifndef SPLIT_BLOCS_H
#define SPLIT_BLOCS_H

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include "../picture/binarypic.h"
#include "rectangle.h"

struct s_rectangle *split_blocs(struct s_binarypic *picture);

struct duet {
    unsigned int i;
    unsigned int j;
};

struct pile { // ceci n est pas une pile
    struct pile *next;
    struct duet *duet;
};

static inline
void pile_init(struct pile *pile) {
    pile->duet = NULL;
    pile->next = NULL;
}

static inline
int isempty(struct pile *pile) {
    return pile == NULL;
    //return pile->next == NULL;
}

static inline
int length(struct pile *pile) {
if(isempty(pile))
    return 0;
else
    return 1 + length(pile->next);
}

static inline
void add(struct duet *duet, struct pile *pile) {
    struct pile *sub = calloc(1, sizeof(struct pile));;
    *sub->duet = *duet;
        sub->next = pile;
    pile = sub;
}

static inline
struct duet* rmv(struct pile *pile) {
    struct duet *sub;
    sub = pile->duet;
    /*if(pile->next == NULL)
        pile = NULL;
    else*/
        pile = pile->next;
    return sub;
}

#endif

