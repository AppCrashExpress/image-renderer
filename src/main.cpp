#include <fstream>

#include "tgaimage.h"
#include "utils.h"
#include "model.h"
#include "image_renderer.h"

static const TGAColor white = TGAColor(255, 255, 255, 255);
static const TGAColor red   = TGAColor(255, 0,   0,   255);

int main() {
    ImageRenderer renderer(500, 500, TGAImage::RGB);

    std::ifstream in("models/african_head.obj");
    Model model(in);
    in.close();

    renderer.draw(model);

    renderer.save("output.tga");
    return 0;
}
