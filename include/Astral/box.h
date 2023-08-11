#ifndef BOX
#define BOX

#include "flip_normals.h"
#include "hittablelist.h"
#include "xyz_rect.h"

class box : public hittable {
public:
  box() {}
  box(const vec3 &p0, const vec3 &p1, material *ptr);
  virtual bool hit(const ray &r, float t0, float t1, hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const {
    box = aabb(pmin, pmax);
    return true;
  }
  vec3 pmin, pmax;
  hittable *list_ptr;
};

#endif