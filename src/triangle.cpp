#include "hittable.h"
#include "triangle.h"


bool triangle::hit(const ray &r, float t_min, float t_max,
                 hit_record &rec) const {
  // triangle vs ray
  auto &v1 = v[0];
  auto &v2 = v[1];
  auto &v3 = v[2];
  vec3 E1 = v2 - v1;
  vec3 E2 = v3 - v1;
  vec3 S = r.origin() - v1;

  vec3 S1 = cross(r.direction(), E2);
  vec3 S2 = cross(S, E1);
  float coeff = 1.0f / dot(S1, E1);
  float t = coeff * dot(S2 , E2);
  float b1 = coeff * dot(S1 , S);
  float b2 = coeff * dot(S2 , r.direction());
  float u = 0.0f, v = 0.0f;
  if (t >= 0 && b1 >= 0 && b2 >= 0 && (1 - b1 - b2) >= 0) {
    rec.p = r.point_at_parameter(t);
    rec.t = t;
    rec.normal = (cross(E1, E2));
    rec.normal.make_unit_vector();
    rec.mat_ptr = mat_ptr;
    // rec.u;
    // rec.v;
    return true;
  }
  return false;
}

bool triangle::bounding_box(float t0, float t1, aabb &box) const {
  aabb bound;
  auto &v1 = v[0];
  auto &v2 = v[1];
  auto &v3 = v[2];

  vec3 min = vec3(std::min({v1.x(), v2.x(), v3.x()}),
                  std::min({v1.y(), v2.y(), v3.y()}),
                  std::min({v1.z(), v2.z(), v3.z()}));
  vec3 max = vec3(std::max({v1.x(), v2.x(), v3.x()}),
                  std::max({v1.y(), v2.y(), v3.y()}),
                  std::max({v1.z(), v2.z(), v3.z()}));
  bound._min = min;
  bound._max = max;
  return true;
}
