#include <math.h>
#include "defs.h"

#define ABS(_X) ((_X) >= 0 ? (_X) : -(_X))

static int px = -1;
static int py = -1;
static int beam = 0;

void draw_to (int x, int y)
{
  if (x == px && y == py && beam)
    return;
  draw_xyz (x, y, 65535);
  px = x;
  py = y;
  beam = 1;
}

void draw_blank (int x, int y)
{
  double dx, dy;
  int i;
  dx = x - px;
  dy = y - py;
  for (i = 0; i <= 8; i++)
    draw_xyz (px + i * dx / 8 + .5, py + i * dy / 8 + .5, 0);
  px = x;
  py = y;
  beam = 0;
}

void draw_point (int x, int y)
{
  draw_blank (x, y);
  draw_xyz (x, y, 65535);
  px = x;
  py = y;
  beam = 1;
}

void draw_line(int x1, int y1, int x2, int y2)
{
  double x, y, dx, dy, r;
  int i, n = 3000;
  dx = x2 - x1;
  dy = y2 - y1;
  r = sqrt (dx * dx + dy * dy);
  dx /= r;
  dy /= r;

  draw_blank ((int)(x1 + .5), (int)(y1 + .5));

  if (r <= n) {
    draw_to (x1, y1);
    draw_to (x2, y2);
  } else {
    for (i = 0; i <= (int)(r + .5); i += n) {
      x = x1 + i * dx + .5;
      y = y1 + i * dy + .5;
      draw_to ((int)x, (int)y);
    }

    if (i - (int)(r + .5) > n / 4) {
      x = x2 + .5;
      y = y2 + .5;
      draw_to ((int)x, (int)y);
    }
  }

  px = (int)x;
  py = (int)y;
  beam = 1;
}
