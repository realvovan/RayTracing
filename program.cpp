#include "iostream"
#include "vector3.h"
#include "color.h"
#include "ray.h"

Color ray_color(const Ray& r) {
    Vector3 unit_direction = r.direction().unit();
    auto a = (unit_direction.y() + 1.0) * .5;
    return Color(1.0,1.0,1.0) * (1.0-a) + Color(.5,.7,1.0) * a;
}

int main() {
    //image
    const auto ASPECT_RATIO = 16.0/9.0;
    const int IMAGE_WIDTH = 400;
    //calculate the image height
    int image_height = int(IMAGE_WIDTH / ASPECT_RATIO);
    image_height = (image_height < 1) ? 1 : image_height;
    //camera
    const auto FOCAL_LENGTH = 1.0;
    const auto VIEWPORT_HEIGHT = 2.0;
    const auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * (double(IMAGE_WIDTH)/image_height);
    const auto CAMERA_CENTER = Point3(0,0,0);
    //calculate the vectors across the horizontal and down the vectical viewport edges
    auto viewport_u = Vector3(VIEWPORT_WIDTH,0,0);
    auto viewport_v = Vector3(0,-VIEWPORT_WIDTH,0);
    //calculate the horizontal and vertical delta vectors from pixel to pixel
    auto pixel_delta_u = viewport_u / IMAGE_WIDTH;
    auto pixel_delta_v = viewport_v / image_height;
    //calculate the location of the upper left pixel
    auto viewport_upper_left = CAMERA_CENTER
        -Vector3(0,0,FOCAL_LENGTH) - viewport_u/2 - viewport_v/2;
    auto pixel100_loc = viewport_upper_left + (pixel_delta_u + pixel_delta_v) * .5;
    //render
    std::cout << "P3\n" << IMAGE_WIDTH << " " << image_height << "\n255\n";

    for(int y = 0; y < image_height; y++) {
        std::clog << "\rScanlines remaining: " << (image_height - y) << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++) {
            auto pixel_center = pixel100_loc + (pixel_delta_u * x) + (pixel_delta_v * y);
            auto ray_direction = pixel_center - CAMERA_CENTER;
            Ray r(CAMERA_CENTER, ray_direction);

            Color pixel_color = ray_color(r);
            write_color(pixel_color);
        }
    }
    std::clog << "\rDone\n";
    return 0;
}