#ifndef LOADER_H
#define LOADER_H

#include <string.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <glib.h>

int picture_load_from_file(const char *filename);
int picture_save_to_file(const char *filename);
int picture_save_pixbuf(GdkPixbuf *pic, const char *filename);
GdkPixbuf *picture_get_image(void);

#endif

