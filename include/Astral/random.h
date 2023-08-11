#ifndef RANDOMH
#define RANDOMH

#include "vec3.h"
#include <cstdlib>

inline double random_double() { return rand() / (RAND_MAX + 1.0); }

vec3 random_in_unit_sphere();

#endif