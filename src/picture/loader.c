#include "loader.h"

static GdkPixbuf *picture = NULL;

int picture_load_from_file(const char *filename)
{
    GError *err;

    err = NULL;
    picture = gdk_pixbuf_new_from_file(filename, &err);

    if(!picture)
    {
        fprintf(stderr, "Unable to load picture :\n\t-> %s\n", err->message);
        g_error_free(err);
        return 1;
    }

    return 0;
}

GdkPixbuf *picture_get_image()
{
    return picture;
}
