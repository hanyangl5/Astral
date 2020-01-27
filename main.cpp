#include "svpng.inc"
#include "sphere.h"
#include "hittablelist.h"
#include "camera.h"
#include "random.h"
#include "material.h"
#include "texture.h"
#include "image_texture.h"
#include<cfloat>

vec3 color(const ray& r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.1, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if (depth < 100 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else{
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);   
    }
}

hittable* texture_spheres(){
    int nx, ny, nn;
    unsigned char *tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
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
    texture* simple=new constant_texture(vec3(1.0,0.0,0.0));
    hittable **list = new hittable*[2];
    list[0] = new sphere(vec3(0,-1000, 0), 1000, new lambertian(simple));
    list[1] = new sphere(vec3(0, 2, 0), 1, new lambertian(pertext));
    return new hittable_list(list, 2);
}

int main() {

    int nx=600,ny=300,ns=30;
    unsigned char rgb[nx * ny * 3], *p = rgb;
    FILE *fp = fopen("test.png", "wb");

    vec3 lookfrom(13,2,3);
    vec3 lookat(0,0,0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;

    camera cam(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus, 0.0, 1.0);

    hittable* world=texture_spheres();

    for (int j = ny-1; j >= 0; j--){
        for (int i = 0; i < nx; i++) {
            vec3 col(0,0,0);
            for(int s = 0; s < ns ; s++){
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                ray r = cam.get_ray(u,v);               
                col += color(r, world, 0);           
            }
            col /= float(ns);
            col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
            *p++ = int(255.99*col[0]);    /* R */
            *p++ = int(255.99*col[1]);    /* G */
            *p++ = int(255.99*col[2]);    /* B */   
        }
    }
    svpng(fp, nx, ny, rgb, 0);
    fclose(fp); 
    return 0;
}
