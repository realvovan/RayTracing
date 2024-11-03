#include "rtweekend.h"
#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"

int main() {
    HittableList world;

    auto material_ground = make_shared<Lambertian>(Color(.8,.8,0.0));
    auto material_center = make_shared<Lambertian>(Color(.1,.2,.5));
    auto material_left = make_shared<Metal>(Color(.8,.8,.8),.3);
    auto material_right = make_shared<Metal>(Color(.8,.6,.2),1.0);

    world.add(make_shared<Sphere>(Point3(0.0,-100.5,-1.0),100.0,material_ground));
    world.add(make_shared<Sphere>(Point3(0.0,0.0,-1.2),.5,material_center));
    world.add(make_shared<Sphere>(Point3(-1.0,0.0,-1.0),.5,material_left));
    world.add(make_shared<Sphere>(Point3(1.0,0.0,-1.0),.5,material_right));

    Camera cam;

    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);
    return 0;
}