#ifndef ISOTROPIC
#define ISOTROPIC

#include "material.h"

class isotropic : public material {
public:
  isotropic(texture *a) : albedo(a) {}
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       vec3 &attenuation, ray &scatterd) const;
  texture *albedo;
};

bool isotropic::scatter(const ray &r_in, const hit_record &rec,
                        vec3 &attenuation, ray &scatterd) const {
  scatterd = ray(rec.p, random_in_unit_sphere());
  attenuation = albedo->value(rec.u, rec.v, rec.p);
  return true;
}

#endif