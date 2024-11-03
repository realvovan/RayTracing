#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class Material;

class HitRecord {
    public:
        Point3 p;
        Vector3 normal;
        double t;
        bool front_face;
        shared_ptr<Material> mat;

        //Sets the hit record normal vector
        //@param outward_normal: NOTE this parameter is assumed to have unit length
        void set_face_normal(const Ray& ray, const Vector3& outward_normal) {
            this->front_face = ray.direction().dot(outward_normal) < 0;
            this->normal = this->front_face ? outward_normal : -outward_normal;
        }
};

class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif