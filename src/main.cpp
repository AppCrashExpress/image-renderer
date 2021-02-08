#include "tgaimage.h"
#include "basic_geometry.h"
#include "model.h"

#include <fstream>

static const TGAColor white = TGAColor(255, 255, 255, 255);
static const TGAColor red   = TGAColor(255, 0,   0,   255);

int main(int argc, char** argv) {
    TGAImage image(500, 500, TGAImage::RGB);

    std::ifstream in("models/african_head.obj");
    Model model(in);
    in.close();

    model.draw(image, white);

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}
