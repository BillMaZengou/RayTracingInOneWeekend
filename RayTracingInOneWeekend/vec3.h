//
//  vec3.h
//  RayTracingInOneWeekend
//
//  Created by Bill Ma on 2021/5/10.
//

#ifndef vec3_h
#define vec3_h

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
    public:
        double vector[3];
    
        inline static vec3 random() {
            return vec3(random_double(), random_double(), random_double());
        }

        inline static vec3 random(double min, double max) {
            return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
        }
    
    public:
        vec3() : vector {0, 0, 0} {}
        vec3(double e0, double e1, double e2) : vector {e0, e1, e2} {}
        
    double x() const { return vector[0]; }
    double y() const { return vector[1]; }
    double z() const { return vector[2]; }
    
    vec3 operator-() const { return vec3(-vector[0], -vector[1], -vector[2]); }
    double operator[](int i) const { return vector[i]; }
    double& operator[](int i) { return vector[i]; }
    
    vec3& operator+=(const vec3 &v) {
        vector[0] += v.vector[0];
        vector[1] += v.vector[1];
        vector[2] += v.vector[2];
        return *this;
    }
    
    vec3& operator*=(const double t) {
        vector[0] *= t;
        vector[1] *= t;
        vector[2] *= t;
        return *this;
    }
    
    vec3& operator/=(const double t) {
        return *this *= 1/t;
    }
    
    double length() const {
        return sqrt(length_squared());
    }
    
    double length_squared() const {
        return vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2];
    }
    
    bool near_zero() const {
//        Return true if the vector is close to zero in all dimensions
        const auto s = 1e-8;
        return (fabs(vector[0]) < s) && (fabs(vector[1]) < s) && (fabs(vector[2]) < s);
    }
    
};

// Type aliases for vec3
using point3 = vec3;    // 3D point
using color = vec3;     // RGB color


/*  vec3 Utility Functions  */
inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.vector[0] << ' ' << v.vector[1] << ' ' << v.vector[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.vector[0]+v.vector[0], u.vector[1]+v.vector[1], u.vector[2]+v.vector[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.vector[0]-v.vector[0], u.vector[1]-v.vector[1], u.vector[2]-v.vector[2]);
}

// Value multification rather than dot or cross product
inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.vector[0]*v.vector[0], u.vector[1]*v.vector[1], u.vector[2]*v.vector[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.vector[0], t*v.vector[1], t*v.vector[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.vector[0] * v.vector[0]
        +  u.vector[1] * v.vector[1]
        +  u.vector[2] * v.vector[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.vector[1]*v.vector[2] - u.vector[2]*v.vector[1],
                u.vector[2]*v.vector[0] - u.vector[0]*v.vector[2],
                u.vector[0]*v.vector[1] - u.vector[1]*v.vector[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

inline vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0)  // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v, n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double indexI_over_indexR) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perp = indexI_over_indexR * (uv + cos_theta * n);
    vec3 r_out_para = - sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_para;
}

inline vec3 random_in_unit_disk() {
    while (true) {
        auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

#endif /* vec3_h */
