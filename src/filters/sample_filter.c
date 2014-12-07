#include "filters.h"
#include "sample_filter.h"
#include "../main.h"


#ifndef M_PI
#define M_PI 3.1415927
#endif

#define RAD(A)  (M_PI*((float)(A))/180.0)
/*
static int getmax(int **hough, int rmax)
{
    int max = 0;
    int teta = 0;
    int i;
    int j;

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

int **angle(int **hough, int x, int y, int rmax)
{
    float r = 0;
    int r1 = 0;
    int teta = 0;

    for(teta = 0; teta < 180; teta++)
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


float detectangle(int **tab, int width, int height)
{
    int i;
    int j;
    int rmax = 0;
    int **hough;
    float teta = 0;

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

void pointrotate(int **new,
        int **tab,
        int i,
        int j,
        float teta,
        int width,
        int height)
{
    double rotinv[2][2];
    double x = 0;
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
        new[j][i] = tab[y1][x1];
    }
}

void rotation(int **tab, int width, int height)
{
    float teta = 0;
    int **new;
    int i;
    int j;

    teta = detectangle(tab, width, height);
    printf("teta: %f\n", teta);
    new = calloc(height, sizeof (int *));
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
*//*
static int rotate_pixbuf(GdkPixbuf **picture, long double angle,
        size_t channels)
{
    guchar *pixels, *tmp;
    size_t h1, w1, h2, w2, x, y, x_rot, y_rot;
size_t dh, dw;
    angle = -angle;

    h1 = gdk_pixbuf_get_height(*picture);
    w1 = gdk_pixbuf_get_width(*picture);
dh = h1 /2;
dw = w1 /2;
    h2 = abs(w1-dw * sin(angle) + h1-dh * cos(angle));
    w2 = abs(w1-dw * cos(angle) - h1-dh * sin(angle));
h2 +=dh;
w2 += dw;
printf ("%lu et %lu \n et %lu et %lu", h2, w2, h1, w1);
    pixels = gdk_pixbuf_get_pixels(*picture);

    wprintf(L"x1 %zu, x2 %zu\ny1 %zu, y2 %zu\n", h1, h2, w1, w2);

    tmp = calloc(h2 * w2 * channels, sizeof(guchar));

    for(y = 0; y < h2; y++)
    {
        for(x = 0; x < w2; x++)
        {
            x_rot = (x+dw) * cos(angle) - (y+dh) * sin(angle);
            y_rot = (x+dw) * sin(angle) + (y+dw) * cos(angle);
y_rot -= dh;
x_rot -= dw;

if ((y*w2+x)*channels +2 < h2*w2*channels && (y_rot*w1+x_rot)*channels + 2 < h1*w1*channels)
{            
tmp[(y * w2 + x) * channels] =
                pixels[(y_rot * w1 + x_rot) * channels];
            tmp[(y * w2 + x) * channels + 1] =
                pixels[(y_rot * w1 + x_rot) * channels + 1];
            tmp[(y * w2 + x) * channels + 2] =
                pixels[(y_rot * w1 + x_rot) * channels + 2];
} 
       }
    }


    g_object_unref(*picture);
    //while(*picture)

    if(!(*picture = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, w2, h2)))
    {
        LOG_ALLOC_ERR();
        return -1;
    }

    pixels = gdk_pixbuf_get_pixels(*picture);

    for(y = 0; y < h2; y++)

    {
        for(x = 0; x < w2; x++)
        {*/
//printf("%lu \n", (y*w2+x)*channels +2);
//if ((y*w2+x)*channels +2 < h2*w2*channels && (y*w2+x)*channels + 20000000000000 < h1*w1*channels && (y*w2+x)*channels > 0)
//{
        //    pixels[(y * w2 + x) * channels] =
             //   tmp[(y * w2 + x) * channels];
           // pixels[(y * w2 + x) * channels + 1] =
         //       tmp[(y * w2 + x) * channels + 1];
       //     pixels[(y * w2 + x) * channels + 2] =
     //           tmp[(y * w2 + x) * channels + 2];
//} 
    //   }
   // }


/*for (size_t i = 0; i< h2*w2*channels; i++)
{
if (i +2 < h2*w2*channels && i + 2 < h1*w1*channels)
{
            pixels[i] =
                tmp[i];
            pixels[i + 1] =
                tmp[i + 1];
            pixels[i + 2] =
                tmp[i + 2];
} 

}*/
  //  return 0;
//}
/*int detectAngle()
{
}*/



int sample_filter(GdkPixbuf **picture, size_t nb_params, char **params)
{
    int bpp;
    if(FLAGS->verbosity && nb_params >= 1)
        printf("Filter parameters : \"%s\"\n", params[0]);

    printf("%zu\n", nb_params);
    if(gdk_pixbuf_get_bits_per_sample(*picture) != 8)
        return 1;
    //look at 3 bytes per pixel.
    //getting attributes of height,
    //width, and bpp.Also get pointer
    //to pixels.
    bpp = gdk_pixbuf_get_n_channels(*picture);
/*
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
    //rotation(tab, wt, ht);
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

*/
//    randome = rotate_pixbuf(picture, M_PI / 90.0, bpp);

    return 0;
}
