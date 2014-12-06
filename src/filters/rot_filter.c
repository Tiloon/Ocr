#include "filters.h"
#include "rot_filter.h"
#include "../main.h"

#ifndef M_PI
#define M_PI 3.1415927
#endif

#define RAD(A)  (M_PI*((double)(A))/180.0)

void pointrotate(guchar *new, guchar *tab, int i, int j, int teta, int width, int height, int bpp)
{
<<<<<<< HEAD
// i = width = x
// j = height = y
int z = i* bpp;
int v = j*width *bpp;
  double	rotinv[2][2];
  double        x = 0;
  double	y = 0;
  int	        x1 = 0;
  int		y1 = 0;
  double      	xm = (width / 2);
  double	ym = (height / 2);
//printf ("%d + %d", width, height);

//printf ("%d + %d", i, j);
  rotinv[0][0] = cos(teta * M_PI / 180);
  rotinv[1][1] = cos(teta * M_PI / 180);
  rotinv[0][1] = -sin(teta * M_PI / 180);
  rotinv[1][0] = sin(teta * M_PI / 180);
//  x = rotinv[0][0] * (z - xm) + rotinv[0][1] * (j - ym);
 // y = rotinv[1][0] * (z - xm) + rotinv[1][1] * (j - ym);
x= rotinv[0][0] * (i-xm) + rotinv[0][1] * (j-ym);
y = rotinv[1][0] * (i-xm) + rotinv[1][1] * (j-ym);
  x1 = x;
  y1 = y;
  if ((x - x1) > 0.5)
    x1++;
  if ((y - y1) > 0.5)
    y1++;
  y1 += ym;
  x1 += xm;
  if (/*(x1 >= 0) && (x1 < width) && (y1 >= 0) && (y1 < height) && */(y1*bpp*width+x1*bpp+bpp <= height*bpp*width) && y1*bpp*width >= 0)
    {
      new[v+z] = tab[y1*bpp*width + x1*bpp/*y1*bpp+x1*bpp*height*/];
      new[v+z+1] = tab[y1*bpp*width+x1*bpp + 1/*y1*bpp+x1*bpp*height+1*/];
      new[v+z+2] = tab[y1*width*bpp+x1*bpp+2/*y1*bpp+x1*bpp*height+2*/];
      //new[y1*bpp*width + x1*bpp] = tab[v+z/*y1*bpp+x1*bpp*height*/];
      //new[y1*bpp*width + x1*bpp+1] = tab[v+z + 1/*y1*bpp+x1*bpp*height+1*/];
      //new[y1*bpp*width + x1*bpp+2] = tab[v+z+2/*y1*bpp+x1*bpp*height+2*/];
=======
    double rotinv[2][2];
    double        x = 0;
    double y = 0;
    int x1 = 0;
    int y1 = 0;
    double xm = (width / 2);
    double ym = (height / 2);

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
        new[j*3*height+i] = tab[y1*3*height + x1];
        new[j*3*height+1+i] = tab[y1*3*height+x1 + 1];
        new[j*3*height+i+2] = tab[y1*3*height+x1+2];
>>>>>>> 953ceb83b8446931f9554100d817b37c25833a6e
    }
//new[j+i] = 0;
//new[j+i+1] = 0;
//new[j+i+2] = 0;

}

<<<<<<< HEAD
void rotation(guchar	*tab,
				   int		width,
				   int		height, int bpp)
{
  int			teta;
  guchar		*new;
int			i;
int			j;
teta =-2;  
new = calloc(width * height * bpp,sizeof(guchar));
for(int a = 0; a < width*height*bpp; a++)
new[a] = tab[a]; 
//printf ("%d + %d", width, height);
  for (j = 0; j < height; j++)
    {
     for (i = 0; i < width ; i++)
//printf ("%d + %d ", i, j);

	pointrotate(new, tab, i, j, teta, width, height, bpp);
    }
for(int z = 0; z < width*height*bpp; z++)
tab[z] = new[z];
//for (int a = 0; a < width*height*bpp; a++)
//tab[a] = 0;

//  return (0);
=======
guchar *rotation(guchar *tab,
        int width,
        int height)
{
    int teta = 0;
    guchar *new;
    int i;
    int j;
    teta = 60;
    new = tab;
    for (j = 0; j < height; j++)
    {
        for (i = 0; i < width ; i++)
            pointrotate(new, tab, i, j, teta, width, height);
    }
    return (new);
>>>>>>> 953ceb83b8446931f9554100d817b37c25833a6e
}

int **angle(int **hough, int x, int y, int th)
{
    float r = 0;
    int r1 = 0;
    int   theta = 0;
    float teta = 0;
    for (theta = 0; theta < 180; theta++)
    {
        //printf ("%f ", cos(theta*M_PI/180));
        teta = theta*M_PI/180;
        r = cos(teta) * x + sin(teta) * y;
        //r = cos (theta)*x+sin(theta)*y;

        r = abs(r);
        //printf ("%f ",r );
        r1 = r;
        //printf("%d ", r1);
        if ((r - r1) > 0.5)
        {
            r1++;
            //printf("%f", r);
        }

        if ((r1 < th) && (r1 > 0))
        {
            // if (theta >=90)
            // hough[r1][theta - 90]++;
            //}
            //else
        hough[r1][(theta%90)]++;
        //printf (" %d ", r1);
    }
}
return (hough);
}

static int getmax(int **h, int th)
{
    int max = 0;
    int theta = 0;
    int i;
    int j;

    for (j = 0; j < th; j++)
    {
        for (i = 0; i < 180; i++)
        {
            //printf ("%d ", h[j][i]);
            if (max < h[j][i])
            {
                max = h[j][i];
                theta = i;
                printf("debug : %d\n", max);
                printf("sortie : %d\n", theta);
                printf("sortie2 : %d\n", j);
            }
        }
        //printf("\n");
    }
    return (theta);
}

int rot_filter(GdkPixbuf *picture, size_t nb_params, char **params)
{
    int **hough;
    float theta = 0;
    theta++;
    int th;
    int ht, wt;
    int i, j;
    int rowstride;
    int bpp;
    //guchar ** tab;
    guchar *pixel;
    unsigned int grayscale = 0;
    if(FLAGS->verbosity && nb_params >= 1)
        printf("Filter parameters : \"%s\"\n", params[0]);

    printf("%zu\n", nb_params);
    if(gdk_pixbuf_get_bits_per_sample(picture)!=8)
        return 1;
    //look at 3 bytes per pixel.
    //getting attributes of height,
    ht = gdk_pixbuf_get_height(picture);
    //width, and bpp.Also get pointer
    wt = gdk_pixbuf_get_width(picture);

    /*pixel = gdk_pixbuf_get_pixels(picture);
      bpp = 3;
      rowstride = wt * bpp;
      */

    th = sqrt(ht*ht+wt*wt);
    hough = calloc(th,sizeof (int *));
    for (i = 0; i < th; i++)
        hough[i] = calloc(180, sizeof (int));
    /*for (i = 0; i < th; i++)
      {
      for (j = 0; j < 180; j++)
      hough[i][j] = 0;
    //printf ("%d ", hough[i][j]);
    }*/
<<<<<<< HEAD
/*tab = malloc (sizeof (guchar *) * ht;
for (i = 0; i < th; i++)
tab[i]  = malloce (sizeof (guchar) * wt;*/
//    to pixels.
pixel = gdk_pixbuf_get_pixels(picture);
=======
    /*tab = malloc (sizeof (guchar *) * ht;
      for (i = 0; i < th; i++)
      tab[i]  = malloce (sizeof (guchar) * wt;*/
    //    to pixels.
    pixel = gdk_pixbuf_get_pixels(picture);
>>>>>>> 953ceb83b8446931f9554100d817b37c25833a6e
    bpp = gdk_pixbuf_get_n_channels(picture);
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
<<<<<<< HEAD
         //   if(grayscale < 0xFF*3/2)
//{
//tab[i][j/3];

//th = sqrt (i*i+j/3*j/3);
//hough = angle(hough,j/3 , i,  th);
  //  grayscale = 0;
//}
  //          else
    //            grayscale = ~0;

	
      //      pixel[i * rowstride + j] = grayscale;
        //   pixel[i * rowstride + j + 1] = grayscale;
          //  pixel[i * rowstride + j + 2] = grayscale;
        }
    }
theta = getmax(hough,th);
rotation(pixel, wt, ht, bpp);
return theta;
=======
            if(grayscale < 0xFF*3/2)
            {
                //tab[i][j/3];

                //th = sqrt (i*i+j/3*j/3);
                hough = angle(hough,j/3 , i,  th);
                grayscale = 0;
            }
            else
                grayscale = ~0;


            //    pixel[i * rowstride + j] = grayscale;
            //  pixel[i * rowstride + j + 1] = grayscale;
            //pixel[i * rowstride + j + 2] = grayscale;
        }
    }
    theta = getmax(hough,th);

    printf("Detected rotation : %f", theta);
    //pixel = rotation(pixel, wt, ht);
    return theta;
>>>>>>> 953ceb83b8446931f9554100d817b37c25833a6e
}
/*for(i = 0; i < ht; i++) //iterate over the height of image.
  {
  for(j = 0; j < rowstride; j += bpp)
//read every pixel in the row.skip//bpp bytes
{

if ((pixel[i*rowstride+j] < 90) && (pixel[i*rowstride+j+1]  < 90) && (pixel[i*rowstride+j+2]  < 90))
{
hough = angle(hough, i, j, th);
}*/
