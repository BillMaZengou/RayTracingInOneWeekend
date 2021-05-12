//
//  camera.h
//  RayTracingInOneWeekend
//
//  Created by Bill Ma on 2021/5/11.
//

#ifndef camera_h
#define camera_h

#include "Utility.h"

class camera {
    private:
        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal;
        vec3 vertical;
        vec3 u, v, w;
        double lens_radius;
        double time0, time1;  // Shutter open/close times
    
    public:
        camera(
            point3 lookfrom,
            point3 lookat,
            vec3   vUp,
            double vfov,  // vertical field-of-view in degrees
            double aspect_ratio,
            double aperture,
            double focus_dist,
            double _time0 = 0,
            double _time1 = 0
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta / 2);
            auto viewPort_height = 2.0 * h;
            auto viewPort_width = aspect_ratio * viewPort_height;
            
            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vUp, w));
            v = cross(w, u);
            
            origin = lookfrom;
            horizontal = focus_dist * viewPort_width * u;
            vertical = focus_dist * viewPort_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * w;
            
            lens_radius = aperture / 2;
            time0 = _time0;
            time1 = _time1;
        }
    
    ray get_ray(double s, double t) const {
        vec3 ray_through_lens = lens_radius * random_in_unit_disk();
        vec3 offset = u * ray_through_lens.x() + v * ray_through_lens.y(); // lens position
        
        return ray(
           origin + offset,
           lower_left_corner + s*horizontal + t*vertical - origin - offset,
           random_double(time0, time1)
        );
    }
};

#endif /* camera_h */
