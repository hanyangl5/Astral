#ifndef FLIPNORMALS
#define FLIPNORMALS

class flip_normals:public hittable{
public:
    flip_normals(hittable *p):ptr(p){};
    flip_normals(){};
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
    virtual bool bounding_box(float t0,float t1,aabb& box)const;


    hittable *ptr;
};

bool flip_normals::hit(const ray& r, float t_min, float t_max, hit_record& rec)const{
    if(ptr->hit(r,t_min,t_max,rec)){
        rec.normal=-rec.normal;
        return true;
    }
    else
        return false;
}
bool flip_normals::bounding_box(float t0,float t1,aabb& box)const{
    return ptr->bounding_box(t0, t1, box);
}
#endif