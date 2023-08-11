#ifndef FLIPNORMALS
#define FLIPNORMALS

#include "hittable.h"

class flip_normals : public hittable {
public:
  flip_normals(hittable *p) : ptr(p){};
  flip_normals(){};
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;

  hittable *ptr;
};

#endif