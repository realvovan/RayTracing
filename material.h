#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"

class Material {
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
            return false;
        }
};

class Lambertian : public Material {
    private:
        Color albedo;

    public:
        Lambertian(const Color& albedo) : albedo(albedo) {}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
            auto scatter_dir = rec.normal + Vector3::random_unit_vector();

            //catch degenerate scatter direction
            if(scatter_dir.near_zero()) scatter_dir = rec.normal;

            scattered = Ray(rec.p,scatter_dir);
            attenuation = albedo;
            return true;
        }
};

class Metal : public Material {
    private:
        Color albedo;
        double fuzz;
    
    public:
        Metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
            Vector3 reflected = r_in.direction().reflect(rec.normal);
            reflected = reflected.unit() + (Vector3::random_unit_vector() * fuzz);
            scattered = Ray(rec.p,reflected);
            attenuation = albedo;
            return scattered.direction().dot(rec.normal) > 0;
        }
};

#endif