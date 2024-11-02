#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

Color ray_color(const Ray& r, const Hittable& wolrd) {
    HitRecord rec;
    if(wolrd.hit(r,Interval(0,HUGE),rec)) {
        return (rec.normal + Color(1,1,1)) * .5;
    }

    Vector3 unit_direction = r.direction().unit();
    auto a = (unit_direction.y() + 1.0) * .5;
    return Color(1.0,1.0,1.0) * (1.0-a) + Color(.5,.7,1.0) * a;
}

int main() {
    //image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    //calculate the image height and ensure that it's at least 1
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    //world
    HittableList world;
    world.add(make_shared<Sphere>(Point3(0,0,-1),.5));
    world.add(make_shared<Sphere>(Point3(0,-100.5,-1),100));
    //camera
    auto focal_lenght = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = Point3(0,0,0);
    //calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = Vector3(viewport_width,0,0);
    auto viewport_v = Vector3(0,-viewport_height,0);
    //calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    //calculate the location of the upper left pixel
    auto viewport_upper_left = camera_center
        - Vector3(0,0,focal_lenght) - viewport_u/2 - viewport_v/2;
    auto pixel100_loc = viewport_upper_left + (pixel_delta_u+pixel_delta_v) * .5;
    //render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for(int y = 0; y < image_height; y++) {
        std::clog << "\rScanlines remaining: " << (image_height - y) << " " << std::flush;
        for(int x = 0; x < image_width; x++) {
            auto pixel_center = pixel100_loc + (pixel_delta_u * x) + (pixel_delta_v * y);
            auto ray_direction = pixel_center - camera_center;
            Ray r(camera_center, ray_direction);

            Color pixel_color = ray_color(r,world);
            write_color(pixel_color);
        }
    }
    std::clog << "\rDone\n";
    return 0;
}