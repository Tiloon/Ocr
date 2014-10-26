#ifndef SPLIT_BLOCS_H
#define SPLIT_BLOCS_H

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include "../picture/binarypic.h"
#include "rectangle.h"


//extern int *splitLines(GdkPixbuf *picture);
struct s_rectangle *splitBlocs(struct s_binarypic *picture);

#endif

