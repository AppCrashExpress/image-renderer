#ifndef MODEL_RENDERER_H
#define MODEL_RENDERER_H

#include <vector>

#include "tgaimage.h"
#include "model.h"
#include "utils.h"

class ImageRenderer {
public:
    ImageRenderer(int width, int height, int bpp);
    ImageRenderer(TGAImage& image);
    ImageRenderer(TGAImage&& image);

    void draw(const Model& model);
    void draw_textured(const Model& model);
    void clear();

    bool save(const char* filename);
 
private:
    ImageRenderer();

    struct ScreenPoint {
        int x, y;
        float z;

        ScreenPoint operator + (const ScreenPoint& other) const {
            return ScreenPoint({
                        x + other.x,
                        y + other.y,
                        z + other.z
                    });
        }

        ScreenPoint operator * (float val) const {
            int   new_x = x * val;
            int   new_y = y * val;
            float new_z = z * val;
            return ScreenPoint( {new_x, new_y, new_z} );
        }
    };

    void resize_z_buffer();
    bool check_visible(const Vec3d& norm);
    ScreenPoint to_screen_coords(const Vec3d& vert);

    Vec3d convert_barycentric(const ScreenPoint& p_a,
                              const ScreenPoint& p_b,
                              const ScreenPoint& p_c,
                              const ScreenPoint& p_current);

    void try_paint(const ScreenPoint& point, const TGAColor& color);

    void fill_triangle(const Vec3d& vert_a,
                       const Vec3d& vert_b,
                       const Vec3d& vert_c,
                       const TGAColor& color);
    
    TGAColor extract_color(const Vec3d& point, TGAImage& texture);
    void draw_textured_triangle(const Vec3d& vert_a, const Vec3d& text_a,
                                const Vec3d& vert_b, const Vec3d& text_b,
                                const Vec3d& vert_c, const Vec3d& text_x,
                                TGAImage& texture, float intensity);

    TGAImage image_;
    int image_height_;
    int image_width_;

    std::vector< std::vector<float> > z_buffer_;

    Vec3d cam_dir_;
    Vec3d light_dir_;
};

#endif
