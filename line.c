#include <math.h>
#include "defs.h"

#define ABS(_X) ((_X) >= 0 ? (_X) : -(_X))

void draw_to (int x, int y)
{
  draw_xyz (x, y, 65535);
}

void draw_blank (int x, int y)
{
  int i;
  for (i = 0; i < 10; i++)
    draw_xyz (x, y, 0);
}

void draw_point (int x, int y)
{
  draw_blank (x, y);
  draw_point (x, y);
  draw_blank (x, y);
}

void draw_line(int x1, int y1, int x2, int y2)
{
#if 1
  double x, y, dx, dy, r;
  int i, n = 500;
  dx = x2 - x1;
  dy = y2 - y1;
  r = sqrt (dx * dx + dy * dy);
  dx /= r;
  dy /= r;

  x = x1 + .5;
  y = y1 + .5;
  
  draw_blank ((int)x, (int)y);

  for (i = 0; i < (int)r; i += n) {
    draw_to ((int)x, (int)y);
    x += n * dx;
    y += n * dy;
  }

  draw_blank ((int)x, (int)y);

#else
  int dx, dy;
  int xdx, xdy, ydx, ydy;
  int x, y;
  int ax, ay;
  int ix, iy;
  int ex, ey;
  int n = 0;

  dx = x2 - x1;
  dy = y2 - y1;

  xdx = ydx = ABS(dx);
  xdy = ydy = ABS(dy);

  ex = x2;
  ey = y2;

  if (ABS (dx) > ABS(dy)) {
    xdx = xdy = 0;
    ey = -1;
  } else {
    ydx = ydy = 0;
    ex = -1;
  }

  ix = dx >= 0 ? 1 : -1;
  iy = dy >= 0 ? 1 : -1;

  ax = ay = 0;
  x = x1;
  y = y1;
  for (;;) {
    if ((++n % 200) == 0)
      draw_to (x, y);

    if (x == ex || y == ey)
      break;

    if (ax >= 0) {
      x += ix;
      ax -= xdy;
    } else
      ax += xdx;

    if (ay >= 0) {
      y += iy;
      ay -= ydx;
    } else
      ay += ydy;
  }
#endif
}
