#ifndef CONVERT_PIC_H
#define CONVERT_PIC_H

#include <stdlib.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

#include "../redef.h"
#include "binarypic.h"

extern int gdk_to_binary(GdkPixbuf *picture, struct s_binarypic *binarypic);
extern int binary_to_gdk(struct s_binarypic *binarypic, GdkPixbuf **picture);

#endif
