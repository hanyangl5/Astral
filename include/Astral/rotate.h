#ifndef ROTATE
#define ROTATE

#include "hittable.h"
#include <cfloat>

class rotate_y : public hittable {
public:
  rotate_y(hittable *p, float angle);
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const {
    box = bbox;
    return hasbox;
  }
  hittable *ptr;
  float sin_theta;
  float cos_theta;
  bool hasbox;
  aabb bbox;
};

#endif