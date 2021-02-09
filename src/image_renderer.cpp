#include "image_renderer.h"
#include "basic_geometry.h"

#include <vector>

ImageRenderer::ImageRenderer() {
    cam_dir_ = Vec3d(0, 0, -1);
    light_dir_ = Vec3d(0, 0, -1);
}

ImageRenderer::ImageRenderer(int width, int height, int bpp)
    : ImageRenderer() {
    image_ = TGAImage(width, height, bpp);
}

ImageRenderer::ImageRenderer(TGAImage& image)
    : ImageRenderer() {
    image_ = image;
}

ImageRenderer::ImageRenderer(TGAImage&& image)
    : ImageRenderer() {
    image_ = image;
}

void ImageRenderer::draw(const Model& model) {
    const std::vector<Vec3d>& vertices = model.get_verts();
    const std::vector<Vec3i>& faces    = model.get_face_verts();

    for (const auto& face : faces) {
        Vec3d vert_a = vertices[ face[0] ];
        Vec3d vert_b = vertices[ face[1] ];
        Vec3d vert_c = vertices[ face[2] ];

        // If counterclockwise, norm goes inside model
        Vec3d norm = Vec3d::cross_product( (vert_c - vert_a), 
                                           (vert_b - vert_a) );
        norm.normalize();

        if ( !check_visible(norm) ) { continue; }
        
        float intensity = Vec3d::dot_product(norm, light_dir_);
        if (intensity < 0) { intensity = 0; }

        float lights_white = 255 * intensity;

        fill_triangle(to_screen_coords(vert_a),
                      to_screen_coords(vert_b),
                      to_screen_coords(vert_c),
                      image_,
                      TGAColor(lights_white, lights_white, lights_white, 255) );
    }

}

void ImageRenderer::clear() {
    image_.clear();
}

bool ImageRenderer::save(const char* filename) {
    image_.flip_vertically();
    return image_.write_tga_file(filename);    
}

bool ImageRenderer::check_visible(const Vec3d& norm) {
    return Vec3d::dot_product(norm, cam_dir_) > 0;
}

Point ImageRenderer::to_screen_coords(const Vec3d& vert) {
    int x = (vert[0] + 1.0f) * image_.get_width() / 2;
    int y = (vert[1] + 1.0f) * image_.get_height() / 2;
    return { x, y };
}

