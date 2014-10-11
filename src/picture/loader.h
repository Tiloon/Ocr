#ifndef LOADER_H
#define LOADER_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>

int load_from_file(const char *filename);
GdkPixbuf *get_image(void);

#endif

