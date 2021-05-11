//
//  sphere.h
//  RayTracingInOneWeekend
//
//  Created by Bill Ma on 2021/5/10.
//

#ifndef sphere_h
#define sphere_h

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        point3 center;
        double radius;
        shared_ptr<material> mat_ptr;
    
    public:
        sphere() {}
        sphere(point3 cen, double r, shared_ptr<material> m)
            : center(cen), radius(r), mat_ptr(m) {};
        
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 O = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(O, r.direction());
    auto c = O.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    
    if (discriminant < 0)
        return false;
    
//    Find the nearest root that lies in the acceptable range.
    auto sqrtDis = sqrt(discriminant);
    auto root = (-half_b - sqrtDis) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtDis) / a;
        if (root < t_min || t_max < root)
            return false;
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    
    return true;
}

#endif /* sphere_h */
