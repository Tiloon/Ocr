#include "filters.h"
#include "sample_filter.h"
#include "../main.h"


#ifndef M_PI
#define M_PI 3.1415927
#endif

#define RAD(A)  (M_PI*((float)(A))/180.0)



static int	getmax(int	**hough,
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

int	**angle(int	**hough,
		int	x,
		int	y,
		int	rmax)
{
  float	r = 0;
  int	r1 = 0;
  int   teta = 0;

  for (teta = 0; teta < 180; teta++)
    {
      r = cos(teta) * x + sin(teta * M_PI / 180) * y;
      r1 = r;
      if ((r - r1) > 0.5)
	r1++;
      if ((r1 < rmax) && (r1 > 0))
	hough[r1][teta]++;
    }
  return (hough);
}


float		detectangle(int		**tab,
			    int		width,
			    int		height)
{
  int		i;
  int		j;
  int		rmax = 0;
  int		**hough;
  float		teta = 0;

  rmax = sqrt(height * height + width * width);
  hough = malloc(sizeof (int *) * rmax);
  for (i = 0; i < rmax; i++)
    hough[i] = malloc(sizeof (int) * 180);
  for (i = 0; i < rmax; i++)
    {
      for (j = 0; j < 45; j++)
	hough[i][j] = 0;
    }
  for (j = 0; j < height; j++)
    {
      for (i = 0; i < width; i++)
	{
	  if ((tab[j][i] < 90))
	    {
	      hough = angle(hough, i, j, rmax);
	    }
	}
    }
  printf("end get angle\n");
  teta = getmax(hough, rmax);
  return (teta);
}
void		pointrotate(int		**new,
			    int		**tab,
			    int		i,
			    int		j,
			    float		teta,
			    int		width,
			    int		height)
{
  double	rotinv[2][2];
  double        x = 0;
  double	y = 0;
  int	        x1 = 0;
  int		y1 = 0;
  double      	xm = (width / 2);
  double	ym = (height / 2);

  rotinv[0][0] = cos(teta * M_PI / 180);
  rotinv[1][1] = cos(teta * M_PI / 180);
  rotinv[0][1] = -sin(teta * M_PI / 180);
  rotinv[1][0] = sin(teta * M_PI / 180);

  x = rotinv[0][0] * (i - xm) + rotinv[0][1] * (j - ym);
  y = rotinv[1][0] * (i - xm) + rotinv[1][1] * (j - ym);
  x1 = x;
  y1 = y;
  if ((x - x1) > 0.5)
    x1++;
  if ((y - y1) > 0.5)
    y1++;
  y1 += ym;
  x1 += xm;
  if ((x1 >= 0) && (x1 < width) && (y1 >= 0) && (y1 < height))
    {
      new[j][i] = tab[y1][x1];
    }
}

void			rotation(int		**tab,
				   int		width,
				   int		height)
{
  float			teta = 0;
  int			**new;
  int			i;
  int			j;

  teta = detectangle(tab, width, height);
  printf("teta: %f\n", teta);
  new = malloc(sizeof (int *) * height);
  for (i = 0; i < height; i++)
    new[i] = calloc(sizeof (int), width);
  for (j = 0; j < height; j++)
    {
      for (i = 0; i < width; i++)
	pointrotate(new, tab, i, j, teta, width, height);
    }

for (j = 0; j < height; j++)
    {
      for (i = 0; i < width; i++)
	tab[j][i] = new[j][i];   
}
}




int sample_filter(GdkPixbuf *picture, size_t nb_params, char **params)
{
    int ht, wt;
    int i, j;
    int rowstride;
    int bpp;
    unsigned int grayscale;
    guchar *pixel;
int **tab;
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
    
tab = malloc(sizeof (int *) * ht);
  for (i = 0; i < ht; i++)
    tab[i] = calloc(sizeof (int), wt);
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
tab[i][j/3] = grayscale;

            pixel[i * rowstride + j] = grayscale;
            pixel[i * rowstride + j + 1] = grayscale;
            pixel[i * rowstride + j + 2] = grayscale;
        }
    }
rotation(tab, wt, ht);
for(i = 0; i < ht; i++) //iterate over the height of image.
    {
        for(j = 0; j < rowstride; j += bpp)
            //read every pixel in the row.skip//bpp bytes
        {
pixel[i * rowstride + j] = tab[i][j/3];
            pixel[i * rowstride + j + 1] = tab[i][j/3];
            pixel[i * rowstride + j + 2] = tab[i][j/3];
        }
    }



printf("%d", pixel[0]);
    return 0;
}
