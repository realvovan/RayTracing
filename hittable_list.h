#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "rtweekend.h"
#include "hittable.h"
#include "vector"

class HittableList : public Hittable {
    public:
        std::vector<shared_ptr<Hittable>> objects;

        HittableList() {}
        HittableList(shared_ptr<Hittable> object) {this->add(object);}

        void add(shared_ptr<Hittable> object) {objects.push_back(object);}

        bool hit(const Ray& ray, Interval ray_t, HitRecord& rec) const override {
            HitRecord temp_rec;
            bool hit_anything = false;
            double closest = ray_t.max;

            for(const auto& object : objects) {
                if(object->hit(ray,Interval(ray_t.min,closest),temp_rec)) {
                    hit_anything = true;
                    closest = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif