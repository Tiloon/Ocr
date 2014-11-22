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
    pile->next = NULL;
}

static inline
int isempty(struct pile *pile) {
    return pile->next == NULL;
}

static inline
void add(struct duet *duet, struct pile *pile) {
    struct pile *sub = malloc(1*sizeof(struct pile));;
    sub->duet = duet;
    if(isempty(pile->next))
        sub->next = NULL;
    else
        sub->next = pile->next->next;
    pile->next = sub;
}

static inline
struct duet* rmv(struct pile *pile) {
    struct pile *sub;
    sub = pile->next;
    pile->next = (pile->next)->next;
    return sub->duet;
}

#endif

