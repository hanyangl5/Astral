#ifndef XYZRECT
#define XYZRECT

#include "hittable.h"

class xy_rect : public hittable {
public:
  xy_rect();
  xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, material *mat)
      : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat){};
  ~xy_rect();
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const;
  virtual bool bounding_box(float t_min, float t_max, aabb &box) const;

  float x0, x1, y0, y1, k;
  material *mp;
};

class xz_rect : public hittable {
public:
  xz_rect() {}
  xz_rect(float _x0, float _x1, float _z0, float _z1, float _k, material *mat)
      : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat){};
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const;
  virtual bool bounding_box(float t_min, float t_max, aabb &box) const;

  material *mp;
  float x0, x1, z0, z1, k;
};

class yz_rect : public hittable {
public:
  yz_rect() {}
  yz_rect(float _y0, float _y1, float _z0, float _z1, float _k, material *mat)
      : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat){};
  virtual bool hit(const ray &r, float t_min, float t_max,
                   hit_record &rec) const;
  virtual bool bounding_box(float t_min, float t_max, aabb &box) const;

  material *mp;
  float y0, y1, z0, z1, k;
};

#endif