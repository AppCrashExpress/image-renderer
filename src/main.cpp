#include "tgaimage.h"
#include "basic_geometry.h"
#include "utils.h"

static const TGAColor white = TGAColor(255, 255, 255, 255);
static const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);

    Point p0 = {20, 30};
    Point p1 = {50, 40};

    Triangle tri = {{
        {50, 50},
        {50, 30},
        {70, 40}
    }};

    draw_line(p0, p1, image, white);
    draw_triangle(tri, image, white);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
