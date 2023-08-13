#include "camera.h"
#include "hittable.h"
#include "vec3.h"

vec3 color(const ray &r, hittable *world, int depth);

void render(int w, int h, int spp, unsigned char *color_buffer, hittable *scene,
            camera *cam);