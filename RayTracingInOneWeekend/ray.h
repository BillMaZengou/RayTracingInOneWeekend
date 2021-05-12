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
        double shutterTime;
    
    public :
        ray() {}
        ray(const point3& origin, const vec3& direction, double time = 0.0)
            :   orig(origin), dir(direction), shutterTime(time) {}
    
    point3 origin() const      { return orig; }
    vec3 direction() const      { return dir; }
    double time() const { return shutterTime; }
    
    point3 at(double t) const {
        return orig + t*dir;
    }
};

#endif /* ray_h */
