#ifndef SPHEREH
#define SPHEREH

#include "hittable.h"

class sphere : public hittable {
public:
  sphere(){};
  sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m){};
  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;
  vec3 center;
  float radius;
  material *mat_ptr; /* NEW */
};

class moving_sphere : public hittable {
public:
  moving_sphere(){};
  moving_sphere(vec3 cen0, vec3 cen1, float t0, float t1, float r, material *m)
      : center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r),
        mat_ptr(m){};
  ~moving_sphere();
  virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;
  virtual bool bounding_box(float t0, float t1, aabb &box) const;
  vec3 center(float time) const;

  vec3 center0, center1;
  float time0, time1;
  float radius;
  material *mat_ptr;
};

#endif