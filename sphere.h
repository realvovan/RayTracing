#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "rtweekend.h"

class Sphere : public Hittable {
    private:
        Point3 center;
        double radius;
        shared_ptr<Material> mat;
    
    public:
        Sphere(const Point3& center, double radius, shared_ptr<Material> mat) : center(center), radius(std::fmax(0,radius)), mat(mat) {
            //TODO: init the material pointer `mat`
        }

        bool hit(const Ray& ray, Interval ray_t, HitRecord& rec) const override {
            Vector3 oc = center - ray.origin();
            auto a = ray.direction().length_squared();
            auto h = ray.direction().dot(oc);
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = h*h - a*c;
            if(discriminant < 0) return false;

            double sqrtd = std::sqrt(discriminant);
            //find the nearest root that lies in the acceptable range
            auto root = (h - sqrtd) / a;
            if(!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if(!ray_t.surrounds(root)) return false;
            }

            rec.t = root;
            rec.p = ray.at(root);
            rec.set_face_normal(ray,(rec.p - center) / radius);
            rec.mat = mat;

            return true;
        }
};

#endif