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

#endif