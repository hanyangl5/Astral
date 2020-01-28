#include "scene.h"


vec3 color(const ray& r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.1, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        vec3 emitted = rec.mat_ptr->emitted(rec.u,rec.v,rec.p);
        if (depth < 100 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return emitted+attenuation*color(scattered, world, depth+1);
        }
        else {
            return emitted;
        }
    }
    return vec3(0,0,0);
}


int main() {

    int nx=600,ny=300,ns=30;
    unsigned char rgb[nx * ny * 3], *p = rgb;
    FILE *fp = fopen("test.png", "wb");

    vec3 lookfrom(13,4,3);
    vec3 lookat(0,2,0);
    float dist_to_focus = 10.0;
    float aperture = 0.0;
    float vfov = 20.0;

    camera cam(lookfrom, lookat, vec3(0,1,0), vfov, float(nx)/float(ny),
    aperture, dist_to_focus, 0.0, 1.0);
    hittable* world=cornell_box();

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
