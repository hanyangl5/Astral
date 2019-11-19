#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray{
	
public:
	ray(){};
	~ray(){};

	ray(const vec3 &a,const vec3 &b){
		A=a;
		B=b;
	}
	//orgin (vec3 type)
	vec3 origin()const{
		return A;
	}
	//direction (vec3 type)
	vec3 direction()const{
		return B;
	}
	//light function (line)
	vec3 point_at_parameter(float t)const{
		return A+t*B;
	}

	vec3 A,B;
};

#endif