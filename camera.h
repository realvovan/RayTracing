#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"
#include "hittable.h"
#include "material.h"

class Camera {
    public:
        //Ratio of image width over height
        double aspect_ratio = 1.0;
        //Rendered image width in pixel count
        int image_width = 100;
        //Count of random samples for each pixel
        int samples_per_pixel = 10;
        //Maximum number of ray bounces into scene
        int max_depth = 10;

        void render(const Hittable& world) {
            init();
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

            for(int y = 0; y < image_height; y++) {
                std::clog << "\rScanlines remaining: " << (image_height - y) << ' '<< std::flush;
                for(int x = 0; x < image_width; x++) {
                    Color pixel_color(0,0,0);
                    for(int sample = 0; sample < samples_per_pixel; sample++) {
                        Ray ray = get_ray(x,y);
                        pixel_color += ray_color(ray,max_depth,world);
                    }
                    write_color(pixel_color * pixel_samples_scale);
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
        //Color scale factor for a sum of pixel samples
        double pixel_samples_scale;

        void init() {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

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

        //Constructs a camera ray originating from the origin and directed at randomly sampled point around the pixel i, j
        Ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc
                                + (pixel_delta_u * (i + offset.x()))
                                + (pixel_delta_v * (j + offset.y()));
            return Ray(center,pixel_sample - center);
        }

        //Returns the vector to a random point in the [-.5, -.5]-[+.5, +.5] unit square
        Vector3 sample_square() const {
            return Vector3(random_double() - .5, random_double() - .5, 0);
        }

        Color ray_color(const Ray& r, int depth, const Hittable& world) const {
            //if we've exceeded the ray bounce limit, no more light is gathered
            if(depth <= 0) return Color(0,0,0);
            
            HitRecord rec;
            if(world.hit(r,Interval(0.001,HUGE),rec)) {
                Ray scattered;
                Color attenuation;
                if(rec.mat->scatter(r,rec,attenuation,scattered))
                    return attenuation * ray_color(scattered,depth-1,world);
                return Color(0,0,0);
            }

            Vector3 unit_direction = r.direction().unit();
            auto a = (unit_direction.y() + 1.0) * .5;
            return Color(1.0,1.0,1.0) * (1.0-a) + Color(.5,.7,1.0) * a;
        }
};

#endif