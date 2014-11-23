#ifndef DRAW_RECTANGLE_H
#define DRAW_RECTANGLE_H

#include "rectangle.h"
#include <gdk-pixbuf/gdk-pixbuf.h>

int draw_rectangle(GdkPixbuf *picture, struct s_rectangle *rect, guchar r,
        guchar g, guchar b);

#endif
