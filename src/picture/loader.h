#ifndef LOADER_H
#define LOADER_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>

int picture_load_from_file(const char *filename);
GdkPixbuf *picture_get_image(void);

#endif

