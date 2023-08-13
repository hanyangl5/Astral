#ifndef TRANSLATE
#define TRANSLATE

#include "hittable.h"

class translate : public hittable {
public:
  translate(hittable *p, const vec3 &displacement) {
    ptr = p;
    offset = displacement;
  };
  ~translate(){};
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;
  hittable *ptr;
  vec3 offset;
};

#endif