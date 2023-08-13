#include "scene.h"

#include <algorithm>
#include <cfloat>

#include "svpng.inc"

#include <Astral/render.h>

int main() {

  constexpr int nx = 1000, ny = 1000, ns = 100;
  unsigned char *rgb = new unsigned char[nx * ny * 3];
  FILE *fp = fopen("test.png", "wb");

  vec3 lookfrom(278, 278, -800);
  vec3 lookat(278, 278, 0);
  float dist_to_focus = 10.0;
  float aperture = 0.0;
  float vfov = 40.0;

  camera cam(lookfrom, lookat, vec3(0, 1, 0), vfov, float(nx) / float(ny),
             aperture, dist_to_focus, 0.0, 1.0);

  hittable *world = final();
  render(nx, ny, ns, rgb, world, &cam);

  svpng(fp, nx, ny, rgb, 0);
  fclose(fp);
  delete[] rgb;
  return 0;
}
