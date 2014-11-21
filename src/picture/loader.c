#include "loader.h"

static GdkPixbuf *picture = NULL;

int picture_load_from_file(const char *filename)
{
    GError *err;

    err = NULL;
    picture = gdk_pixbuf_new_from_file(filename, &err);

    if(!picture)
    {
        fprintf(stderr, "Unable to load picture : %s\n", err->message);
        g_error_free(err);
        return 1;
    }

    return 0;
}

int picture_save_to_file(const char *filename)
{
    return picture_save_pixbuf(picture, filename);
}

int picture_save_pixbuf(GdkPixbuf *pic, const char *filename)
{
    GError *err;
    char *filetype;

    err = NULL;
    filetype = strrchr(filename, '.');
    if(pic == NULL)
    {
        fprintf(stderr, "Can't save : picture adress is NULL.\n");
        return 1;
    }

    if((filetype == NULL) || (*(++filetype) == 0))
    {
        fprintf(stderr, "Can't save : extension  error : \"%s\"\n", filename);
        return 1;
    }

    if(gdk_pixbuf_save(pic, filename, filetype, &err, NULL) == FALSE)
    {
        fprintf(stderr, "Unable to save picture : %s\n", err->message);
        g_error_free(err);
        return 1;
    }

    return 0;
}

GdkPixbuf *picture_get_image()
{
    return picture;
}
