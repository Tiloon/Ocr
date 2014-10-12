#include "splitlines.h"
#include <stdlib.h>

int splitLines(GdkPixbuf *picture)
{
    int i,j,height,width,row, bpp, lineFound, nbrLigne;
    gchar *pixels;
    int *lines; // pair pair, lines[0] haut de la premiere ligne, lines[1] bas de la premiere ligne, lines[2] haut de la seconde ligne etc
                //need malloc ou *lines(mais du coup ca marche? ou need lines[]) fait le taffe? jsuis pas sur d avoir bien compris donc aucasou j ecris ca

    if(gdk_pixbuf_get_bits_per_sample(picture)!=8)   //handle only 24 bit images.
        return; //add error

    nbrLigne = 0;
    bpp = 3; // gdk_pixbuf_get_n_channels(picture) needed?
    height = gdk_pixbuf_get_height(picture);
    width = gdk_pixbuf_get_width(picture);
    pixels = gdk_pixbuf_get_pixels(picture);
    row = width * bpp;
    lineFound = 0;

    //add super while pour chaque ligne
    while(0=0)
    {
        for(i=0; i<height && lineFound == 0; i++) //cherche un premier noir apres un bloc de blanc => haut de ligne
        {
            for(j=0; j<row && lineFound == 0; j+=bpp)
            {
                if(pixels[i*row+j] == 255 && pixels[i*row+j+1] == 255 && pixels[i*row+j+2] == 255)
                    lineFound = 1;
            }
        }
        if(i>= heigth) return lines;
        lines[nbrLigne] = i;
        nbrLigne++;
        lineFound = 0;
        for(i=0; i<height && lineFound == 0; i++) //cherche un premier blanc apres un bloc de noir => bas de ligne
        {
            for(j=0; j<row && lineFound == 0; j+=bpp)
            {
                if(pixels[i*row+j] == 0 && pixels[i*row+j+1] == 0 && pixels[i*row+j+2] == 0)
                    lineFound = 1;
            }
        }
        if(i>= heigth)
        {
            lines[nbrLigne] = i-1; //derniere ligne = noir, faut quand meme prendre le bas de ligne
            return lines;
        }
        lines[nbrLigne] = i-1;
        nbrLigne++;
        lineFound=0;

        //end super while
    }
}
