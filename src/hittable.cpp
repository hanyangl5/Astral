#include "hittable.h"
#include "aabb.h"
#include "ray.h"

void get_sphere_uv(const vec3 &p, float &u, float &v) {
  float phi = atan2(p.z(), p.x());
  float theta = asin(p.y());
  u = 1 - (phi + AST_PI) / (2 * AST_PI);
  v = (theta + AST_PI / 2) / AST_PI;
}
