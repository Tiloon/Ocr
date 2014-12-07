#include "filters.h"
#include "rot_filter.h"
#include "../main.h"

#ifndef M_PI
#define M_PI 3.1415927
#endif

#define RAD(A)  (M_PI*((float)(A))/180.0)

/*
void pointrotate(guchar *new, guchar *tab, int i, int j, int teta, int width, int height, int bpp)
{
// i = width = x
// j = height = y
int z = i* bpp*height;
int v = j *bpp;
  float 	rotinv[2][2];
  float        x = 0;
  float 	y = 0;
  int	        x1 = 0;
  int		y1 = 0;
  float      	xm = (width+1) / 2.0;
  float		ym = (height+1) / 2.0;
  rotinv[0][0] = cos(RAD(teta));
  rotinv[1][1] = cos(RAD(teta));
  rotinv[0][1] = -sin(RAD(teta));
  rotinv[1][0] = sin(RAD(teta));
x= rotinv[0][0] * (i-xm) + rotinv[0][1] * (j-ym);
y = rotinv[1][0] * (i-xm) + rotinv[1][1] * (j-ym);
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
  if (*//*(x1 >= 0) && (x1 < width) && (y1 >= 0) && (y1 < height) &&*/ /*(y1*bpp+x1*height*bpp+bpp-1 <= height*bpp*width) )
    {
for (int b = 0; b < bpp; b++)
{
//printf ("%d + %d \n", y1, x1);
//printf ("%d et %d\n", v+z+b, y1*bpp+b+x1*bpp*height);
//printf("%d\n", tab[y1*bpp+b+x1*bpp*height]);      
//new[v+z+b] = tab[y1*bpp*width + b + x1*bpp*//*y1*bpp+x1*bpp*height*//*];
      //tab[y1*bpp*width+b+x1*bpp] = 255;
new[v+z+b] = tab[y1*bpp+x1*bpp*height + by1*bpp+x1*bpp*height+1];
      //new[v+z+2] = tab[y1*width*bpp+x1*bpp+2y1*bpp+x1*bpp*height+2];
      //new[y1*bpp*width + x1*bpp+b] = tab[v+z+by1*bpp+x1*bpp*height];
      //new[y1*bpp*width + x1*bpp+1] = tab[v+z + 1y1*bpp+x1*bpp*height+1];
      //new[y1*bpp*width + x1*bpp+2] = tab[v+z+2y1*bpp+x1*bpp*height+2];
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

void rotation(guchar	*tab,
				   int		width,
				   int		height, int bpp)
{
printf(" %d et %d et %d \n", tab[42], tab[43], tab[44]);
printf("h : %d w : %d \n", height, width);
  int			teta;
  guchar		*new;
int			i;
int			j;
teta =180;  
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

	pointrotate(new, tab, j, i, teta, width, height, bpp);
    }
for(int z = 0; z < width*height*bpp; z++)
{
//printf("%d \n", new[z]);
   tab[z] = new[z];
}
//for (int a = 0; a < width*height*bpp; a++)
//tab[a] = 0;

//  return (0);
}*/
/*int **angle(int **hough, int x, int y, int th)
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
}*/

/*static int getmax(int **h, int th)
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
}*/

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
/*tab = malloc (sizeof (guchar *) * ht;
for (i = 0; i < th; i++)
tab[i]  = malloce (sizeof (guchar) * wt;*/
//    to pixels.
pixel = gdk_pixbuf_get_pixels(picture);
    bpp = gdk_pixbuf_get_n_channels(picture);
gboolean a = gdk_pixbuf_get_has_alpha(picture);
//rotation(pixel, wt, ht, bpp);

if (a)
printf ("dadada");
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
{
//tab[i][j/3];

//th = sqrt (i*i+j/3*j/3);
//hough = angle(hough,j/3 , i,  th);
    grayscale = 0;
}
            else
                grayscale = ~0;

	
            pixel[i * rowstride + j] = grayscale;
           pixel[i * rowstride + j + 1] = grayscale;
            pixel[i * rowstride + j + 2] = grayscale;
        }
    }
//theta = getmax(hough,th);
//printf(" %d et %d et %d \n", pixel[42], pixel[43], pixel[44]);
//rotation(pixel, wt, ht, bpp);

/*for (int k = 0; k < ht*wt*bpp; k++)
	{
if (k%3==0)
printf("\n");
printf ("%d : %d ", k, pixel[k]);
}*/
/*for(i = 0; i < ht; i++) //iterate over the height of image.
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
{
//tab[i][j/3];

//th = sqrt (i*i+j/3*j/3);
//hough = angle(hough,j/3 , i,  th);
    grayscale = 0;
}
            else
                grayscale = ~0;


            pixel[i * rowstride + j] = grayscale;
           pixel[i * rowstride + j + 1] = grayscale;
            pixel[i * rowstride + j + 2] = grayscale;
        }
    }
*/
return theta;
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
