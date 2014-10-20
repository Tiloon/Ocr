#ifndef RECTANGLE_H
#define RECTANGLE_H

struct s_rectangle {
  unsigned int x;
  unsigned int y;
  unsigned int w;
  unsigned int h;
};
/*
unsigned int max(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}

unsigned int min(unsigned int a, unsigned int b)
{
    return a < b ? a : b;
}
*/

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))


#endif
