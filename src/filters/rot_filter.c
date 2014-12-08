#include "filters.h"
#include "rot_filter.h"
#include "../main.h"

int rot_filter(GdkPixbuf **picture, size_t nb_params, char **params)
{
    size_t i;
    char *com;

    picture_save_pixbuf(*picture, "tmp.png");
    if(nb_params == 0)
        return -1;
    for(i = 0; params[0][i]; i++);

    if(i > 5)
        return -1;

    com = calloc(45 + i, sizeof(char));
    sprintf(com, "convert tmp.png -rotate %s tmp.png", params[0]);
    system(com);
    picture_load_from_file("tmp.png");
    return 0;
}
