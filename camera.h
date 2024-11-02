#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"

class Camera {
    public:
        //Ratio of image width over height
        double aspect_ratio = 1.0;
        //Rendered image width in pixel count
        int image_width = 100;

        void render(const Hittable& world) {
            init();
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int y = 0; y < image_height; y++) {
                std::clog << "\rScanlines remaining: " << (image_height - y) << ' '<< std::flush;
                for(int x = 0; x < image_width; x++) {
                    auto pixel_center = pixel00_loc + (pixel_delta_u * x) + (pixel_delta_v * y);
                    auto ray_direction = pixel_center - center;

                    Color pixel_color = ray_color(Ray(center,ray_direction),world);
                    write_color(pixel_color);
                }
            }

            std::clog << "\rDone.                 \n";
        }

    private:
        //Rendered image height
        int image_height;
        //Camera center
        Point3 center;
        //Location of the 0,0 pixel
        Point3 pixel00_loc;
        //Offset to pixel to the right
        Vector3 pixel_delta_u;
        //Offset to pixel below
        Vector3 pixel_delta_v;

        void init() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = Point3(0,0,0);
            //determine viewport dimensions
            auto focal_lenght = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width)/image_height);
            //calculate the vectors across the horizontal and down the vertical viewport edges
            auto viewport_u = Vector3(viewport_width,0,0);
            auto viewport_v = Vector3(0,-viewport_height,0);
            //calcultae the horizontal and vertical delta vectors from pixel to pixel
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;
            //calculate the location of the upper left pixel
            auto viewport_upper_left = 
                center - Vector3(0,0,focal_lenght) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * .5;
        }

        Color ray_color(const Ray& r, const Hittable& world) const {
            HitRecord rec;
            if(world.hit(r,Interval(0,HUGE),rec)) {
                return (rec.normal + Color(1,1,1)) * .5;
            }

            Vector3 unit_direction = r.direction().unit();
            auto a = (unit_direction.y() + 1.0) * .5;
            return Color(1.0,1.0,1.0) * (1.0-a) + Color(.5,.7,1.0) * a;
        }
};

#endif