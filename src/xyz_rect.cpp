#include "xyz_rect.h"
#include "hittable.h"

bool xy_rect::hit(const ray &r, float t_min, float t_max,
                  hit_record &rec) const {
  float t = (k - r.origin().z()) / r.direction().z();
  if (t < t_min || t > t_max)
    return false;
  float x = r.origin().x() + t * r.direction().x();
  float y = r.origin().y() + t * r.direction().y();
  if (x < x0 || x > x1 || y < y0 || y > y1)
    return false;
  rec.u = (x - x0) / (x1 - x0);
  rec.v = (y - y0) / (y1 - y0);
  rec.t = t;
  rec.mat_ptr = mp;
  rec.p = r.point_at_parameter(t);
  rec.normal = vec3(0, 0, 1);
  return true;
}
bool xy_rect::bounding_box(float t_min, float t_max, aabb &box) const {
  box = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
  return true;
}

bool xz_rect::hit(const ray &r, float t_min, float t_max,
                  hit_record &rec) const {
  float t = (k - r.origin().y()) / r.direction().y();
  if (t < t_min || t > t_max)
    return false;
  float x = r.origin().x() + t * r.direction().x();
  float z = r.origin().z() + t * r.direction().z();
  if (x < x0 || x > x1 || z < z0 || z > z1)
    return false;
  rec.u = (x - x0) / (x1 - x0);
  rec.v = (z - z0) / (z1 - z0);
  rec.t = t;
  rec.mat_ptr = mp;
  rec.p = r.point_at_parameter(t);
  rec.normal = vec3(0, 1, 0);
  return true;
}

bool xz_rect::bounding_box(float t_min, float t_max, aabb &box) const {
  box = aabb(vec3(x0, k - 0.0001, z0), vec3(x1, k + 0.0001, z1));
  return true;
}

bool yz_rect::hit(const ray &r, float t_min, float t_max,
                  hit_record &rec) const {
  float t = (k - r.origin().x()) / r.direction().x();
  if (t < t_min || t > t_max)
    return false;
  float y = r.origin().y() + t * r.direction().y();
  float z = r.origin().z() + t * r.direction().z();
  if (y < y0 || y > y1 || z < z0 || z > z1)
    return false;
  rec.u = (y - y0) / (y1 - y0);
  rec.v = (z - z0) / (z1 - z0);
  rec.t = t;
  rec.mat_ptr = mp;
  rec.p = r.point_at_parameter(t);
  rec.normal = vec3(1, 0, 0);
  return true;
}

bool yz_rect::bounding_box(float t_min, float t_max, aabb &box) const {
  box = aabb(vec3(k - 0.0001, y0, z0), vec3(k + 0.0001, y1, z1));
  return true;
}