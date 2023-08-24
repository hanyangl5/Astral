#ifndef TRIANGLE
#define TRIANGLE

#include "hittable.h"

class triangle : public hittable {
public:
  triangle(){};
  triangle(const vec3 &v1, const vec3 &v2, const vec3 &v3, material *m)
      : v{v1, v2, v3}, mat_ptr(m){};
  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;

  vec3 v[3];
  material *mat_ptr; /* NEW */
};

#endif