#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include "tgaimage.h"
#include "model.h"
#include "utils.h"

class ImageRenderer {
public:
    ImageRenderer(int width, int height, int bpp);
    ImageRenderer(TGAImage& image);
    ImageRenderer(TGAImage&& image);

    void draw(const Model& model);
    void clear();

    bool save(const char* filename);
 
private:
    ImageRenderer();

    bool check_visible(const Vec3d& norm);
    Point to_screen_coords(const Vec3d& vert);

    TGAImage image_;
    Vec3d cam_dir_;
    Vec3d light_dir_;
};

#endif
