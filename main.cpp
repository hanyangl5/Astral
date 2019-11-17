#include "float.h"
#include "hittablelist.h"
#include "sphere.h"



#include <fstream>
#include <string>
#include <iostream>


//calculate color
vec3 color(const ray& r, hittable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)) {
        return 0.5*vec3(rec.normal.x()+1, rec.normal.y()+1, rec.normal.z()+1);
    }
    else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
    }
}

int main(){

	std::cout<<"test1";
	std::string path="test/test3.ppm";
	std::ofstream file(path.c_str());
	if(!file){
		std::cerr<<"failed to create file ";
		exit(-1);
	}

	int nx=600; //width
	int ny=360; //height

	file<<"P3\n"<<nx<<" "<<ny<<"\n255\n";


	vec3 lower_left_corner(-2.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);

	hittable *list[2];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);
    hittable *world = new hittable_list(list,2);

	for(int j=ny-1;j>=0;j--){ 
		// up to down
		for(int i=0;i<nx;i++){
			//left to right
			float u=float(i)/float(nx);
			float v=float(j)/float(ny);
			// create light for each pixel
			ray r(origin,lower_left_corner+u*horizontal+v*vertical);
			//range (-1.-1.-1) to (3,1,-1)
     		vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);
			
			int ir=int(255.99*col[0]);
			int ig=int(255.99*col[1]);
			int ib=int(255.99*col[2]);
			
			file<<ir<<" "<<ig<<" "<<ib<<std::endl;
		}
	}



	std::cout<<"test2";
	return 0;
}
