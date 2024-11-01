#include "iostream"
#include "vector3.h"
#include "color.h"
#include "ray.h"

int main() {
    const int IMAGE_HEIGHT = 256;
    const int IMAGE_WIDTH = 256;
    
    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    for(int y = 0; y < IMAGE_HEIGHT; y++) {
        std::clog << "\rScanlines remaining: " << (IMAGE_HEIGHT - y) << " " << std::flush;
        for(int x = 0; x < IMAGE_WIDTH; x++) {
            Color pixel_color(
                double(x)/(IMAGE_WIDTH-1),
                double(y)/(IMAGE_HEIGHT-1),
                0.0
            );
            write_color(pixel_color);
        }
    }
    std::clog << "\rDone\n";
    return 0;
}