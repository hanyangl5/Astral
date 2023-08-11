#ifndef BVH
#define BVH

#include "hittable.h"
#include "random.h"

int box_x_compare(const void *a, const void *b);

int box_y_compare(const void *a, const void *b);

int box_z_compare(const void *a, const void *b);

class bvh_node : public hittable {
public:
  bvh_node() {}
  bvh_node(hittable **l, int n, float time0, float time1);

  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;

  hittable *left;
  hittable *right;
  aabb box;
};

#endif