#ifndef SCENE
#define SCENE

#include <string>

#include <stb_image.h>

#include "Astral/box.h"
#include "Astral/bvh.h"
#include "Astral/camera.h"
#include "Astral/constant_medium.h"
#include "Astral/flip_normals.h"
#include "Astral/hittablelist.h"
#include "Astral/image_texture.h"
#include "Astral/material.h"
#include "Astral/random.h"
#include "Astral/rotate.h"
#include "Astral/sphere.h"
#include "Astral/triangle.h"
#include "Astral/texture.h"
#include "Astral/translate.h"
#include "Astral/xyz_rect.h"

#include <config.hpp>

//hittable *texture_spheres() {
//
//  std::string path = ASSET_DIR;
//  std::string earth_tex_path = path + "/earthmap.jpg";
//  int nx, ny, nn;
//  unsigned char *tex_data = stbi_load(earth_tex_path.c_str(), &nx, &ny, &nn, 0);
//  material *mat = new lambertian(new image_texture(tex_data, nx, ny));
//  int n = 50;
//  hittable **list = new hittable *[n + 1];
//  list[0] = new sphere(vec3(0, 0, 0), 1, mat);
//  return new hittable_list(list, 1);
//}
//hittable *two_spheres() {
//  texture *checker =
//      new checker_texture(new constant_texture(vec3(0.2, 0.3, 0.1)),
//                          new constant_texture(vec3(0.9, 0.9, 0.9)));
//  texture *simple = new constant_texture(vec3(0.5, 0.5, 0.5));
//
//  int n = 50;
//  hittable **list = new hittable *[n + 1];
//  list[0] = new sphere(vec3(0, -10, 0), 10, new lambertian(checker));
//  list[1] = new sphere(vec3(0, 10, 0), 10, new lambertian(simple));
//  return new hittable_list(list, 2);
//}
//
//hittable *two_perlin_spheres() {
//  texture *pertext = new noise_texture(10);
//  texture *simple = new constant_texture(vec3(0.0, 0.0, 0.0));
//  hittable **list = new hittable *[2];
//  list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
//  list[1] = new sphere(vec3(0, 2, 0), 1, new lambertian(pertext));
//  return new hittable_list(list, 2);
//}
//
//hittable *simple_light() {
//  texture *pertext = new noise_texture(4);
//  hittable **list = new hittable *[4];
//  list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
//  list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
//  list[2] = new sphere(vec3(0, 7, 0), 2,
//                       new diffuse_light(new constant_texture(vec3(4, 4, 4))));
//  list[3] = new xy_rect(3, 5, 1, 3, -2,
//                        new diffuse_light(new constant_texture(vec3(4, 4, 4))));
//  return new hittable_list(list, 4);
//}

hittable* cornell_box() {
    hittable** list = new hittable * [50];
    int i = 0;
    material* red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material* white =
        new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material* green =
        new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material* light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));
    material* spec = new metal(vec3(1, 1, 1), 0);

    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    list[i++] = new translate(
        new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
        vec3(130, 0, 65));
    list[i++] = new translate(
        new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
        vec3(265, 0, 295));
    return new hittable_list(list, i);
}

hittable* cornell_smoke() {
    hittable** list = new hittable * [8];
    int i = 0;
    material* red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material* white =
        new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material* green =
        new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material* light = new diffuse_light(new constant_texture(vec3(7, 7, 7)));

    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(113, 443, 127, 432, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    hittable* b1 = new translate(
        new rotate_y(new box(vec3(0, 0, 0), vec3(165, 165, 165), white), -18),
        vec3(130, 0, 65));
    hittable* b2 = new translate(
        new rotate_y(new box(vec3(0, 0, 0), vec3(165, 330, 165), white), 15),
        vec3(265, 0, 295));

    list[i++] =
        new constant_medium(b1, 0.01, new constant_texture(vec3(1.0, 1.0, 1.0)));
    list[i++] =
        new constant_medium(b2, 0.01, new constant_texture(vec3(0.0, 0.0, 0.0)));

    return new hittable_list(list, i);
}

hittable* final() {
    int nb = 20;
    hittable** list = new hittable * [30];
    hittable** boxlist = new hittable * [10000];
    hittable** boxlist2 = new hittable * [10000];
    material* white =
        new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material* ground =
        new lambertian(new constant_texture(vec3(0.48, 0.83, 0.53)));
    int b = 0;
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < nb; j++) {
            float w = 100;
            float x0 = -1000 + i * w;
            float z0 = -1000 + j * w;
            float y0 = 0;
            float x1 = x0 + w;
            float y1 = 100 * (random_double() + 0.01);
            float z1 = z0 + w;
            boxlist[b++] = new box(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
        }
    }
    int l = 0;
    list[l++] = new bvh_node(boxlist, b, 0, 1);
    material* light = new diffuse_light(new constant_texture(vec3(7, 7, 7)));
    list[l++] = new xz_rect(123, 423, 147, 412, 554, light);
    vec3 center(400, 400, 200);
    list[l++] = new moving_sphere(
        center, center + vec3(30, 0, 0), 0, 1, 50,
        new lambertian(new constant_texture(vec3(0.7, 0.3, 0.1))));
    list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(1.5));
    list[l++] =
        new sphere(vec3(0, 150, 145), 50, new metal(vec3(0.8, 0.8, 0.9), 10.0));
    hittable* boundary = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
    list[l++] = boundary;
    list[l++] = new constant_medium(boundary, 0.2,
        new constant_texture(vec3(0.2, 0.4, 0.9)));
    boundary = new sphere(vec3(0, 0, 0), 5000, new dielectric(1.5));
    list[l++] = new constant_medium(boundary, 0.0001,
        new constant_texture(vec3(1.0, 1.0, 1.0)));

    std::string path = ASSET_DIR;
    std::string earth_tex_path = path + "/earthmap.jpg";
    int nx, ny, nn;
    unsigned char* tex_data = stbi_load(earth_tex_path.c_str(), &nx, &ny, &nn, 0);
    material* emat = new lambertian(new image_texture(tex_data, nx, ny));
    list[l++] = new sphere(vec3(400, 200, 400), 100, emat);
    texture* pertext = new noise_texture(0.1);
    list[l++] = new sphere(vec3(220, 280, 300), 80, new lambertian(pertext));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxlist2[j] = new sphere(vec3(165 * random_double(), 165 * random_double(),
            165 * random_double()),
            10, white);
    }
    list[l++] =
        new translate(new rotate_y(new bvh_node(boxlist2, ns, 0.0, 1.0), 15),
            vec3(-100, 270, 395));
    return new hittable_list(list, l);
}

hittable* simple_triangle() {
    hittable** list = new hittable * [50];
    int i = 0;
    material* red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material* white =
        new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material* green =
        new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material* light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));
    material* spec = new metal(vec3(1, 1, 1), 0);

    list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
    list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
    list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
    list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
    list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
    list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    list[i++] = new triangle(vec3(200, 150, 400), vec3(200, 200, 600),
        vec3(300, 150, 400), green);

    return new hittable_list(list, i);
}

inline hittable* get_scene(int index) {
    switch (index) {
    case 1:
        return cornell_box();
    case 2:
        return cornell_smoke();
    case 3:
        return final();
    case 4:
        return simple_triangle();
    default:
        return nullptr;
    }
}

#endif