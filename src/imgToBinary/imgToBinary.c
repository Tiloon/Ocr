#insert "imgToBinary.h"


guchar* imgToBinary(GdkPixbuf *picture)
{

	int ht, wt, a;
	guchar* pixelsTab;

	ht = gdk_pixbuf_get_height(picture)
	//width, and bpp.Also get pointer
	wt = gdk_pixbuf_get_width(picture);
	//to pixels.
	a = wt*3;
	pixelsTab = gdk_pixbuf_get_pixels(picture);

	char[ht*wt] binaryTab;


	for (int i = 0; i < ht; i++)
	{
		for (int j = 0; j < a; j+=3)
		{
			if(pixelsTab[i*a+j]+pixelsTab[i*a+j+1]+pixelsTab[i*a*j+1] >= 600)
				binaryTab[i*wt+j] = 0;
			else
				binaryTab[i*wt+j] = 1;
		}
	}
	return binaryTab;
}
