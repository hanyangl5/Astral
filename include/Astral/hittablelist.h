#ifndef HITTABLELISTH
#define HITTABLELISTH

#include "hittable.h"

class hittable_list : public hittable {
public:
  hittable_list() {}
  hittable_list(hittable **l, int n) {
    list = l;
    list_size = n;
  }
  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;
  hittable **list;
  int list_size;
};

#endif