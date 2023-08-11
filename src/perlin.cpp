#include "perlin.h"
#include "random.h"

vec3 *perlin_generate() {
  vec3 *p = new vec3[256];
  for (int i = 0; i < 256; ++i) {
    double x_random = 2 * random_double() - 1;
    double y_random = 2 * random_double() - 1;
    double z_random = 2 * random_double() - 1;
    p[i] = unit_vector(vec3(x_random, y_random, z_random));
  }
  return p;
}

void permute(int *p, int n) {
  for (int i = n - 1; i > 0; i--) {
    int target = int(random_double() * (i + 1));
    int tmp = p[i];
    p[i] = p[target];
    p[target] = tmp;
  }
  return;
}

int *perlin_generate_perm() {
  int *p = new int[256];
  for (int i = 0; i < 256; i++)
    p[i] = i;
  permute(p, 256);
  return p;
}


namespace identifier {

}
vec3 *perlin::ranvec = perlin_generate();
int *perlin::perm_x = perlin_generate_perm();
int *perlin::perm_y = perlin_generate_perm();
int *perlin::perm_z = perlin_generate_perm();

float perlin::noise(const vec3 &p) const {

  float u = p.x() - floor(p.x());
  float v = p.y() - floor(p.y());
  float w = p.z() - floor(p.z());

  int i = floor(p.x());
  int j = floor(p.y());
  int k = floor(p.z());

  vec3 c[2][2][2];
  for (int di = 0; di < 2; di++)
    for (int dj = 0; dj < 2; dj++)
      for (int dk = 0; dk < 2; dk++)
        c[di][dj][dk] = ranvec[perm_x[(i + di) & 255] ^ perm_y[(j + dj) & 255] ^
                               perm_z[(k + dk) & 255]]; //保留后8位
  return perlin_interp(c, u, v, w);
}

float perlin::turb(const vec3 &p, int depth = 7) const {
  float accum = 0;
  vec3 temp_p = p;
  float weight = 1.0;
  for (int i = 0; i < depth; i++) {
    accum += weight * noise(temp_p);
    weight *= 0.5;
    temp_p *= 2;
  }
  return fabs(accum);
}

