#include <iostream>
#include "ray.h"
#include <fstream>

//if the light hit the sphere
float hit_sphere(const vec3& center, float radius, const ray& r) {

    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
	if (discriminant < 0) {
        return -1.0;
    }// doesnt hit the sphere
    else {
        return (-b - sqrt(discriminant) ) / (2.0*a);
    }// return hit point
}

//calculate color
vec3 color(const ray& r) {
	float t = hit_sphere(vec3(0,0,-1), 0.5, r);
    if (t > 0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){

	std::cout<<"test1";
	std::ofstream file("test.ppm");

	int nx=1920; //width
	int ny=1080; //height

	file<<"P3\n"<<nx<<" "<<ny<<"\n255\n";


	vec3 lower_left_corner(-1.0,-1.0,-1.0);
	vec3 horizontal(4.0,0.0,0.0);
	vec3 vertical(0.0,2.0,0.0);
	vec3 origin(0.0,0.0,0.0);

	for(int j=ny-1;j>=0;j--){ 
		// up to down
		for(int i=0;i<nx;i++){
			//left to right
			float u=float(i)/float(nx);
			float v=float(j)/float(ny);
			// create light for each pixel
			ray r(origin,lower_left_corner+u*horizontal+v*vertical);
			//range (-1.-1.-1) to (3,1,-1)
			vec3 col=color(r);
			
			int ir=int(255.99*col[0]);
			int ig=int(255.99*col[1]);
			int ib=int(255.99*col[2]);
			
			file<<ir<<" "<<ig<<" "<<ib<<std::endl;
		}
	}



	std::cout<<"test2";
	return 0;
}
