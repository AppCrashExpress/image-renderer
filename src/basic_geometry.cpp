#include "basic_geometry.h"

#include <utility>
#include "utils.h"

void draw_line(int x0, int y0, int x1, int y1,
               TGAImage& image, const TGAColor& color) {
    bool steep = std::abs(x1 - x0) < std::abs(y1 - y0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if ((x1 - x0) < 0) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    float d_error = std::abs((float) dy / dx);

    float error = 0;
    int   y = y0;
    for (int x = x0; x < x1; ++x) {
        image.set(x * (!steep) + y * steep, 
                  y * (!steep) + x * steep, 
                  color);
        error += d_error;
        if (error > 0.5) {
            y += sign(dy);
            error -= 1;
        }
    }
}

void draw_line(const Point& p0, const Point& p1,
               TGAImage& image, const TGAColor& color) {
    draw_line(p0.x, p0.y, p1.x, p1.y, image, color);
}

void draw_triangle(Point p0, Point p1, Point p2, 
        TGAImage& image, const TGAColor& color) {
    if (p0.y > p1.y) { std::swap(p0, p1); }
    if (p0.y > p2.y) { std::swap(p0, p2); }
    if (p1.y > p2.y) { std::swap(p1, p2); }

    draw_line(p0, p1, image, color);
    draw_line(p1, p2, image, color);
    draw_line(p2, p0, image, color);
}

void draw_triangle(const Triangle& tri,
        TGAImage& image, const TGAColor& color) {
    draw_triangle(tri.vert[0], tri.vert[1], tri.vert[2], image, color);
}
