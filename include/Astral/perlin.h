#ifndef PERLIN
#define PERLIN

#include "random.h"

static vec3 *perlin_generate();

void permute(int *p, int n);

static int *perlin_generate_perm();

inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w) {
  float uu = u * u * (3 - 2 * u); // 缓和曲线
  float vv = v * v * (3 - 2 * v);
  float ww = w * w * (3 - 2 * w);
  float accum = 0;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++) {
        vec3 weight_v(u - i, v - j, w - k); // 权重
        accum += (i * uu + (1 - i) * (1 - uu)) * (j * vv + (1 - j) * (1 - vv)) *
                 (k * ww + (1 - k) * (1 - ww)) * dot(c[i][j][k], weight_v);
      }
  return accum;
}

class perlin {
public:
  float noise(const vec3 &p) const;
  float turb(const vec3 &, int) const;
  static vec3 *ranvec;
  static int *perm_x;
  static int *perm_y;
  static int *perm_z;
};

#endif