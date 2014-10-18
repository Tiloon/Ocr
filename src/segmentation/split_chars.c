#include "split_chars.h"

struct s_rectangle* splitChars(struct s_binarypic picture,int *tab)
{
    int i,j, height, width, row, bpp;
    int nbrCar, nbrLigne, carFound, coord, coord2;
    struct s_caractere *rep; //need alloc i guess
    char *pixel;

    height = gdk_pixbuf_get_height(picture);
    width = gdk_pixbuf_get_width(picture);
    pixel = gdk_pixbuf_get_pixels(picture);


    if(gdk_pixbuf_get_bits_per_sample(pixel)!=8)
        return 1; //add error

    nbrLigne = 0;
    nbrCar = 0;
    carFound = 0;
    j = 0;
    bpp = 3;
    row = width * bpp;
    rep = malloc(0 * sizeof(*rep)); //need confirmation


    while(1)
    {

        for(;j<width && carFound==0;j+=bpp)
        {
            for(i=tab[nbrLigne];i<=tab[nbrLigne+1]
                    && carFound == 0;i++)
            {
                if(pixel[tab[nbrLigne]*row+j] == 0
                        && pixel[tab[nbrLigne]*row+j+1]==0
                        && pixel[tab[nbrLigne]*row+j+2]==0)
                {
                    carFound = 1;
                    coord = j;
                }
            }
        }
        if(j>=width)
            return rep;
        //condition d arret
        carFound = 0;
        rep = realloc(rep, (nbrCar + 1) * sizeof(*rep)); //need confirm
        rep[nbrCar].x = coord;
        rep[nbrCar].y = tab[nbrLigne];
        rep[nbrCar].h = tab[nbrLigne] - tab[nbrLigne+1];
        for(;j<width && carFound == 1;j+=bpp)
        {
            carFound = 0;
            for(i=tab[nbrLigne];i<=tab[nbrLigne+1]
                    && carFound == 0;i++)
            {
                if(pixel[ i * row + j] == 255
                        && pixel[i * row + j + 1] == 255
                        && pixel[i * row + j + 2] == 255)
                {
                    carFound = 1;
                    coord2 = j;
                }

            }
        }
        if(j>=width)
            return rep;
        //condition d arret
        rep[nbrCar].w = coord2 - coord;
        carFound = 0;
        nbrLigne += 2;
        nbrCar++;

    } //endwhile
}
