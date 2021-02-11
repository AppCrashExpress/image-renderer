#include "image_renderer.h"
#include "basic_geometry.h"

#include <vector>
#include <algorithm>

ImageRenderer::ImageRenderer() {
    cam_dir_ = Vec3d(0, 0, -1);
    light_dir_ = Vec3d(0, 0, -1);
}

ImageRenderer::ImageRenderer(int width, int height, int bpp)
    : ImageRenderer() {
    image_ = TGAImage(width, height, bpp);
    
    image_width_  = width;
    image_height_ = height;
    resize_z_buffer();
}

ImageRenderer::ImageRenderer(TGAImage& image)
    : ImageRenderer() {
    image_ = image;

    image_width_  = image.get_width();
    image_height_ = image.get_height();
    resize_z_buffer();
}

ImageRenderer::ImageRenderer(TGAImage&& image)
    : ImageRenderer() {
    image_ = image;

    image_width_  = image.get_width();
    image_height_ = image.get_height();
    resize_z_buffer();
}

void ImageRenderer::draw(const Model& model) {
    const std::vector<Vec3d>& vertices = model.get_verts();
    const std::vector<Vec3i>& faces    = model.get_face_verts();

//    const std::vector<Vec3d>& vertices = {
//        { 0.0f, -0.5f,  0.0f},
//        { 0.5f,  0.5f,  0.5f},
//        {-0.5f,  0.5f,  0.5f},
//        {-0.5f,  0.5f, -0.5f},
//        { 0.5f,  0.5f, -0.5f},
//    };
//    const std::vector<Vec3i>& faces = {
//        {0, 1, 3},
//        {0, 4, 2}
//    };


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

        fill_triangle(vert_a, vert_b, vert_c,
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

void ImageRenderer::resize_z_buffer() {
    z_buffer_ = std::vector< std::vector<float> > (
                image_width_,
                std::vector<float> (image_height_, -2.0f)
            );
}

bool ImageRenderer::check_visible(const Vec3d& norm) {
    return Vec3d::dot_product(norm, cam_dir_) > 0;
}

ImageRenderer::ScreenPoint
ImageRenderer::to_screen_coords(const Vec3d& vert) {
    int x = (vert[0] + 1.0f) * image_.get_width() / 2;
    int y = (vert[1] + 1.0f) * image_.get_height() / 2;
    float z = vert[2];
    return { x, y, z };
}

Vec3d ImageRenderer::convert_barycentric(const ScreenPoint& p_a,
                                         const ScreenPoint& p_b,
                                         const ScreenPoint& p_c,
                                         const ScreenPoint& p_current) {
    const Vec3d x_side = Vec3d(p_c.x - p_a.x,
                               p_b.x - p_a.x,
                               p_a.x - p_current.x);
    const Vec3d y_side = Vec3d(p_c.y - p_a.y,
                               p_b.y - p_a.y,
                               p_a.y - p_current.y);
    const Vec3d params = Vec3d::cross_product(x_side, y_side);
    
    if (std::abs(params[2]) < 1.0f) { Vec3d(-1, -1, -1); }
    return Vec3d(1.0f - (params[0] + params[1]) / params[2],
                 params[1] / params[2],
                 params[0] / params[2]);
}

void ImageRenderer::try_paint(const ScreenPoint& point, const TGAColor& color) {
    if (z_buffer_[point.x][point.y] < point.z) {
        z_buffer_[point.x][point.y] = point.z;
        image_.set(point.x, point.y, color);
    }
}

void ImageRenderer::fill_triangle(const Vec3d& vert_a,
                                  const Vec3d& vert_b,
                                  const Vec3d& vert_c,
                                  const TGAColor& color) {
    ScreenPoint p_a = to_screen_coords(vert_a);
    ScreenPoint p_b = to_screen_coords(vert_b);
    ScreenPoint p_c = to_screen_coords(vert_c);

    ScreenPoint low_bound  = {
        std::min( {p_a.x, p_b.x, p_c.x} ),
        std::min( {p_a.y, p_b.y, p_c.y} ),
        0
    };
    ScreenPoint high_bound = {
        std::max( {p_a.x, p_b.x, p_c.x} ),
        std::max( {p_a.y, p_b.y, p_c.y} ),
        0
    };

    if (low_bound.x < 0) { low_bound.x = 0; }
    if (low_bound.y < 0) { low_bound.y = 0; }
    if (high_bound.x > image_width_)  { high_bound.x = image_width_; }
    if (high_bound.y > image_height_) { high_bound.y = image_height_; }

    for (int w = low_bound.x; w < high_bound.x; ++w) {
        for (int h = low_bound.y; h < high_bound.y; ++h) {
            ScreenPoint current = {w, h, 0};
            Vec3d params = convert_barycentric(p_a, p_b, p_c, current);
            
            if (params[0] < 0 || params[1] < 0 || params[2] < 0) {
                continue;
            }

            current.z += params[0] * p_a.z;
            current.z += params[1] * p_b.z;
            current.z += params[2] * p_c.z;

            try_paint(current, color);
        }
    }
}

