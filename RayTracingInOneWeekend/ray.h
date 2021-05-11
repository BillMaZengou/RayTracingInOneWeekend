//
//  ray.h
//  RayTracingInOneWeekend
//
//  Created by Bill Ma on 2021/5/10.
//

#ifndef ray_h
#define ray_h

#include "vec3.h"

class ray {
    public :
        point3 orig;
        vec3 dir;
    
    public :
        ray() {}
        ray(const point3& origin, const vec3& direction)
            :   orig(origin), dir(direction) {}
    
    point3 origin() const { return orig; }
    vec3 direction() const { return dir; }
    
    point3 at(double t) const {
        return orig + t*dir;
    }
};

#endif /* ray_h */
