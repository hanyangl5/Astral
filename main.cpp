#include <fstream>
#include <string>
#include <iostream>

#include "float.h"
#include "include/hittablelist.h"
#include "include/sphere.h"
#include "include/camera.h"
#include "include/random.h"
#include "include/material.h"


//calculate color
vec3 color(const ray& r, hittable *world, int depth) {
    hit_record rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {//ignore hits very near zero:
        ray scattered;
        vec3 attenuation;
        if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {//reflect 50% of the light
            return attenuation*color(scattered, world, depth+1);
        }
        else {
            return vec3(0,0,0);
        }
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}


int main(){

	std::cout<<"test1";
	std::string path="test/spec.ppm";
	std::ofstream file(path.c_str());
	if(!file){
		std::cerr<<"failed to create file ";
		exit(-1);
	}

	int nx=600; //width
	int ny=360; //height
	int ns=100; //multiple rays

	file<<"P3\n"<<nx<<" "<<ny<<"\n255\n";

/*
	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);
*/
	hittable *list[4];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
    hittable *world = new hittable_list(list,4);
	camera cam;
	for(int j=ny-1;j>=0;j--){ 
		// up to down
		for(int i=0;i<nx;i++){
			//left to right
			vec3 col(0, 0, 0);

			//
            for (int s = 0; s < ns; s++) {
            	//let each ray hit the sphere
                float u = float(i + random_double()) / float(nx);
                float v = float(j + random_double()) / float(ny);
                ray r = cam.get_ray(u, v);
                col += color(r, world,0);//acumulate color
            	}
            //average the color
            col /= float(ns);
			col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );//gamma correction
			
			int ir=int(255.99*col[0]);
			int ig=int(255.99*col[1]);
			int ib=int(255.99*col[2]);
			
			file<<ir<<" "<<ig<<" "<<ib<<std::endl;
		}
	}



	std::cout<<"test2";
	return 0;
}
