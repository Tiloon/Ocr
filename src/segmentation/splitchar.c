#include "splitchar.h"
#include <stdlib.h>

*s_caractere splitChars(GdkPixbuf *picture,int *tab)
{
	int i,j, height, width, row, bpp;
	int nbrCar, nbrLigne, carFound, coord, coord2;
	s_caractere rep; //need alloc i guess

	if(gdk_pixbuf_get_bits_per_sample(picture)!=8)
		return; //add error

	nbrLigne = 0;
	nbrCar = 0;
	carFound = 0;
	j = 0;
        rep = malloc(0 * sizeof(*rep)); //need confirmation


	while(1)
	{

		for(;j<width && carFound==0;j++)
		{
			for(i=tab[nbrLigne];i<=itab[nbrLigne+1] 
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
		rep[nbrCar].height = tab[nbrLigne] - tab[nbrLigne+1];
		for(;j<width && carFound == 1;j++)
		{
			carFound = 0;
			for(i=tab[nbrLigne];i<=tab[nbrLigne+1] 
			&& carFound == 0;i++)
			{
				if(pixels[ i * row + j] == 255
				&& pixels[i * row + j + 1] == 255 
				&& pixels[i * row + j + 2] == 255)
				{
					carFound = 1;
					coord2 = j;
				}

			}
		}
		if(j>=width)
			return repl
		//condition d arret
		rep[nbrCar].width = coord2 - coord;
		carFound = 0;
		nbrLigne += 2;
		nbrCar++;
		
	} //endwhile
}
