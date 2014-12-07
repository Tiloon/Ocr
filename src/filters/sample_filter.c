#include "filters.h"
#include "sample_filter.h"
#include "../main.h"


#ifndef M_PI
#define M_PI 3.1415927
#endif

#define RAD(A)  (M_PI*((float)(A))/180.0)





void pointrotate(guchar *new, guchar *tab, int i, int j, int teta, int height, int width, int bpp)
{
// i = width = x
// j = height = y
int z = i* bpp;
int v = j *bpp*width;
  float         rotinv[2][2];
  float        x = 0;
  float         y = 0;
  int           x1 = 0;
  int           y1 = 0;
  float         xm = (width) / 2.0;
  float         ym = (height) / 2.0;
  rotinv[0][0] = cos(RAD(teta));
  rotinv[1][1] = cos(RAD(teta));
  rotinv[0][1] = -sin(RAD(teta));
  rotinv[1][0] = sin(RAD(teta));
x= rotinv[0][0] * (i-xm) + rotinv[1][0] * (j-ym);
y = rotinv[0][1] * (i-xm) + rotinv[1][1] * (j-ym);
//printf ("xf = %f, yf = %f \n", x, y);
//printf(" %d et %d et %d \n", tab[42], tab[43], tab[44]);
 // x1 = x;
 // y1 = y;
//  if ((x - x1) > 0.5)
  //  x1++;
 // if ((y - y1) > 0.5)
   // y1++;
  y += ym ;
  x += xm ;
x1 = x;
y1 = y;
  x1 = x;
  y1 = y;
  if ((x - x1) > 0.5)
    x1++;
  if ((y - y1) > 0.5)
    y1++;
//printf ("h = %d, w = %d \n", height, width);
//printf ("xm = %f, ym = %f \n", xm, ym);
//printf ("xf = %f, yf = %f \n", x, y);
//printf ("x = %d, y = %d \n", x1, y1);
  if (/*(x1 >= 0) && (x1 < width) && (y1 >= 0) && (y1 < height) &&*/ (y1*bpp*width+x1*bpp+bpp-1 <= height*bpp*width) )
    {

for (int b = 0; b < bpp; b++)
{
//printf ("%d + %d \n", y1, x1);
//printf ("%d et %d\n", v+z+b, y1*bpp+b+x1*bpp*height);
//printf("%d\n", tab[y1*bpp+b+x1*bpp*height]);      
//new[v+z+b] = tab[y1*bpp*width + b + x1*bpp/*y1*bpp+x1*bpp*height*/];
      //tab[y1*bpp*width+b+x1*bpp] = 255;
new[v+z+b] = tab[y1*bpp*width+x1*bpp + b/*y1*bpp+x1*bpp*height+1*/];
      //new[v+z+2] = tab[y1*width*bpp+x1*bpp+2/*y1*bpp+x1*bpp*height+2*/];
      //new[y1*bpp*width + x1*bpp+b] = tab[v+z+b/*y1*bpp+x1*bpp*height*/];
      //new[y1*bpp*width + x1*bpp+1] = tab[v+z + 1/*y1*bpp+x1*bpp*height+1*/];
      //new[y1*bpp*width + x1*bpp+2] = tab[v+z+2/*y1*bpp+x1*bpp*height+2*/];
}
}
//else
//{
//for (int b = 0; b < bpp; b++)
//{

//printf ("%d et %d\n", v+z+b, y1*bpp*width+b+x1*bpp);
//printf("%d\n", tab[y1*bpp*width+b+x1*bpp]);

//}
//for(int b=0; b < bpp; b++)
//{
//new[v+z+b] = 255;
//}
//}

//new[j+i] = 0;
//new[j+i+1] = 0;
//new[j+i+2] = 0;

}

void rotation(guchar    *tab,
                                   int          width,
                                   int          height, int bpp)
{
printf(" %d et %d et %d \n", tab[42], tab[43], tab[44]);
printf("h : %d w : %d \n", height, width);
  int                   teta;
  guchar                *new;
int                     i;
int                     j;
teta =90;
new = calloc(width * height * bpp,sizeof(guchar));
for(int a = 0; a < width*height*bpp; a++)
  { new[a] = 0;
//printf("%d \n", tab[a]);
}
printf ("%d ", width*height*bpp );
for (j = 0; j < width; j++)
  {
   for (i = 0; i < height ; i++)
//printf ("%d  ", width*bpp*height);

        pointrotate(new, tab, i, j, teta, height, width, bpp);
    }
for(int z = 0; z < width*height*bpp; z++)
{
//printf("%d \n", new[z]);
   tab[z] = new[z];
}
//for (int a = 0; a < width*height*bpp; a++)
//tab[a] = 0;

//  return (0);
}



int sample_filter(GdkPixbuf *picture, size_t nb_params, char **params)
{
    int ht, wt;
    int i, j;
    int rowstride;
    int bpp;
    unsigned int grayscale;
    guchar *pixel;

    if(FLAGS->verbosity && nb_params >= 1)
        printf("Filter parameters : \"%s\"\n", params[0]);

    printf("%zu\n", nb_params);
    if(gdk_pixbuf_get_bits_per_sample(picture) != 8)
        return 1;
    //look at 3 bytes per pixel.
    //getting attributes of height,
    ht = gdk_pixbuf_get_height(picture);
    //width, and bpp.Also get pointer
    wt = gdk_pixbuf_get_width(picture);
    //to pixels.
    pixel = gdk_pixbuf_get_pixels(picture);
    bpp = gdk_pixbuf_get_n_channels(picture);
printf ("%d", bpp);
    rowstride = wt * bpp;
    for(i = 0; i < ht; i++) //iterate over the height of image.
    {
        for(j = 0; j < rowstride; j += bpp)
            //read every pixel in the row.skip//bpp bytes
        {
            grayscale = pixel[i * rowstride + j];
            grayscale += pixel[i * rowstride + j + 1];
            grayscale += pixel[i * rowstride + j + 2];
            //access pixel[i][j] as
            // pixel[i*rowstride + j]
            //access red,green and blue as
            //pixel[i*rowstride + j+0]=0;
            //pixel[i*rowstride + j+1]=0;
            //pixel[i*rowstride + j+2]=blue
            if(grayscale < 0xFF*3/2)
                grayscale = 0;
            else
                grayscale = ~0;

            pixel[i * rowstride + j] = grayscale;
            pixel[i * rowstride + j + 1] = grayscale;
            pixel[i * rowstride + j + 2] = grayscale;
        }
    }
rotation(pixel, wt, ht, bpp);
printf("%d", pixel[0]);
    return 0;
}
