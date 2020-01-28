#ifndef SCENE
#define SCENE 

#include "svpng.inc"
#include "sphere.h"
#include "hittablelist.h"
#include "camera.h"
#include "random.h"
#include "material.h"
#include "texture.h"
#include "image_texture.h"
#include "xy_rect.h"
#include<cfloat>

hittable* texture_spheres(){
    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("earthjpg.jpg", &nx, &ny, &nn, 0);
    material *mat = new lambertian(new image_texture(tex_data, nx, ny));
    int n = 50;
    hittable **list = new hittable*[n+1];
    list[0] = new sphere(vec3(0,0, 0), 1, mat);
    return new hittable_list(list,1);
}
hittable *two_spheres() {
    texture *checker = new checker_texture(
        new constant_texture(vec3(0.2, 0.3, 0.1)),
        new constant_texture(vec3(0.9, 0.9, 0.9))
    );
    texture* simple=new constant_texture(vec3(0.5,0.5,0.5));


    int n = 50;
    hittable **list = new hittable*[n+1];
    list[0] = new sphere(vec3(0,-10, 0), 10, new lambertian(checker));
    list[1] = new sphere(vec3(0, 10, 0), 10, new lambertian(simple));
    return new hittable_list(list,2);
}

hittable *two_perlin_spheres() {
    texture* pertext = new noise_texture(10);
    texture* simple=new constant_texture(vec3(0.0,0.0,0.0));
    hittable **list = new hittable*[2];
    list[0] = new sphere(vec3(0,-1000, 0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 2, 0), 1, new lambertian(pertext));
    return new hittable_list(list, 2);
}
hittable *simple_light() {
    texture *pertext = new noise_texture(4);
    hittable **list = new hittable*[4];
    list[0] = new sphere(vec3(0,-1000, 0), 1000, new lambertian(pertext));
    list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
    list[2] = new sphere(vec3(0, 7, 0), 2,
        new diffuse_light(new constant_texture(vec3(4,4,4))));
    list[3] = new xy_rect(3, 5, 1, 3, -2,
        new diffuse_light(new constant_texture(vec3(4,4,4))));
    return new hittable_list(list,4);
}

hittable *cornell_box() {
    hittable **list = new hittable*[5];
    int i = 0;
    material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));

    list[i++] = new yz_rect(0, 555, 0, 555, 555, green);
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new xy_rect(0, 555, 0, 555, 555, white);

    return new hittable_list(list,i);
}

#endif