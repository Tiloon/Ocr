#include "filters.h"
#include "rot_filter.h"
#include "../main.h"

#ifndef M_PI
#define M_PI 3.14159265358979
#endif

#define RAD(A)  (M_PI*((float)(A))/180.0)

void roti(int *x, int *y, int i, int j, int w, int h, double cost, double sint)
{
w++;
h++;
float xx = 0;
float yy = 0;
//float ii = i-(w+1)/2.0;
  i-=w/2+1; j-=h/2+1;
//printf(" %i, %i, %i, %i ", i, j, h, w);
  
xx=i*cost-j*sint + w/2;
  yy=i*sint+j*cost + h/2;
*x = xx;
*y = yy;
if (xx-*x > 0.5)
*x = *x +1;
if(yy-*y > 0.5)
*y = *y +1;
//printf(" %i, %i, %i, %i ", x, y, h, w);
*x = *x-1;
*y = *y-1;
}

void Rot(guchar **img, double angle,int ht,int wt)
{
guchar **copy;
copy = calloc(ht, sizeof (guchar *));
  for (int i = 0; i < ht; i++)
    copy[i] = calloc(wt, sizeof (guchar));

  angle*=M_PI/(double)180;
  double cost = cos(angle), sint = sin(angle);
  int x=0, y=0;
  printf("all OK\n");
  for(int j=0; j<ht; j++)
    {
      for(int i=0; i<wt; i++)
	{
//printf(" %i, %i, %i, %i ", i, j, ht, wt);
	  roti(&x, &y, i, j, wt, ht, cost, sint);
//printf(" %i, %i\n ", x, y);

	  if(x < wt && y < ht && x > 0 && y > 0)
	    {
		copy[y][x] = img[j][i];
	    }
	}
    }
  printf("done\n");
for(int j=0; j<ht; j++)
    {
      for(int i=0; i<wt; i++)
        {
                img[j][i] = copy[j][i];
        }
    }

  free(copy);
}


/*int	getmax(int	**hough,
		       int	rmax)
{
  int		max = 0;
  int		teta = 0;
  int		i;
  int		j;

  for (j = 0; j < rmax; j++)
    {
      for (i = 0; i < 180; i++)
	{
	  if (max < hough[j][i])
	    {
	      max = hough[j][i];
	      teta = i;
	    }
	}
    }
  return (teta);
}

int **angle (int **hough, int x, int y, int rmax)
{
float r = 0.0;
int r1 = 0;
float theta = 0.0;
int tete = 0;
for (teta = 0; teta < 180; teta++)
    {
theta = teta*M_PI/180;
      r = cos(theta) * x + sin(theta) * y;
      r1 = r;
      if ((r - r1) > 0.5)
	r1++;
      if ((r1 < rmax) && (r1 > 0))
	hough[r1][teta]++;
    }
  return (hough);
}*/

int rot_filter(GdkPixbuf **picture, size_t nb_params, char **params)
{
int bpp;
int ht;
int wt;
int rowstride;
int grayscale;
int i, j;
guchar *pixel;
//int **hough;
guchar ** tab;
    if(FLAGS->verbosity && nb_params >= 1)
        printf("Filter parameters : \"%s\"\n", params[0]);
    printf("%zu\n", nb_params);
    if(gdk_pixbuf_get_bits_per_sample(*picture) != 8)
        return 1;
    pixel = gdk_pixbuf_get_pixels(*picture);
    bpp = gdk_pixbuf_get_n_channels(*picture);
    ht = gdk_pixbuf_get_height(*picture);
    wt = gdk_pixbuf_get_width(*picture);
   rowstride = wt*bpp;
tab = calloc(ht, sizeof (guchar *));
gdk_to_binary(*picture);
  for (int i = 0; i < ht; i++)
    tab[i] = calloc(wt, sizeof (guchar));
for(i = 0; i < ht; i++) //iterate over the height of image.
    {
        for(j = 0; j < rowstride; j += bpp)
        {
            grayscale = pixel[i * rowstride + j];
            grayscale += pixel[i * rowstride + j + 1];
            grayscale += pixel[i * rowstride + j + 2];
            if(grayscale < 0xFF*3/2)
{
                grayscale = 0;
}
            else
                grayscale = ~0;
tab[i][j/bpp] = grayscale;
            pixel[i * rowstride + j] = grayscale;
            pixel[i * rowstride + j + 1] = grayscale;
            pixel[i * rowstride + j + 2] = grayscale;
        }
    }
Rot(tab, 4, ht, wt);
for(i = 0; i < ht; i++) //iterate over the height of image.
    {
        for(j = 0; j < rowstride; j += bpp)
        {
pixel[i * rowstride + j] = tab[i][j/bpp];
pixel[i * rowstride + j+1] = tab[i][j/bpp];
pixel[i * rowstride + j+2] = tab[i][j/bpp];
}
}
return 0;
}
