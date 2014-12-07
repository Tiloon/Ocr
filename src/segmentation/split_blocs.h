#ifndef SPLIT_BLOCS_H
#define SPLIT_BLOCS_H

#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>

#include "../redef.h"
#include "../picture/binarypic.h"
#include "../picture/copy_binarized.h"
#include "morphology.h"
#include "rectangle.h"

struct s_rectangle *split_blocs(struct s_binarypic *picture);

#endif
