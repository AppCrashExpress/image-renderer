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
    for (int x = x0; x <= x1; ++x) {
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
    draw_line(p0, p1, image, color);
    draw_line(p1, p2, image, color);
    draw_line(p2, p0, image, color);
}

void draw_triangle(const Triangle& tri,
        TGAImage& image, const TGAColor& color) {
    draw_triangle(tri.vert[0], tri.vert[1], tri.vert[2], image, color);
}

void fill_y_line(int x_begin, int x_end, int y, 
        TGAImage& image, const TGAColor& color) {
    for (int x = x_begin; x <= x_end; ++x) {
        image.set(x, y, color);
    }
}

void fill_triangle(Point p0, Point p1, Point p2, 
        TGAImage& image, const TGAColor& color) {
    if (p0.y > p1.y) { std::swap(p0, p1); }
    if (p0.y > p2.y) { std::swap(p0, p2); }
    if (p1.y > p2.y) { std::swap(p1, p2); }

    int total_height = p2.y - p0.y + 1;
    int segment_height = 0;

    segment_height = p1.y - p0.y + 1;
    for (int y = p0.y; y <= p1.y; ++y) {
        float t_short = (float) (y - p0.y) / segment_height;
        float t_long  = (float) (y - p0.y) / total_height;

        int x_begin = p0.x * (1 - t_short) + p1.x * t_short;
        int x_end   = p0.x * (1 - t_long) + p2.x * t_long;

        if (x_end < x_begin) { std::swap(x_end, x_begin); }
        fill_y_line(x_begin, x_end, y, image, color);
    }

    segment_height = p2.y - p1.y + 1;
    for (int y = p1.y; y <= p2.y; ++y) {
        float t_short = (float) (y - p1.y) / segment_height;
        float t_long  = (float) (y - p0.y) / total_height;

        int x_begin = p1.x * (1 - t_short) + p2.x * t_short;
        int x_end   = p0.x * (1 - t_long) + p2.x * t_long;

        if (x_end < x_begin) { std::swap(x_end, x_begin); }
        fill_y_line(x_begin, x_end, y, image, color);
    }
}

void fill_triangle(const Triangle& tri,
        TGAImage& image, const TGAColor& color) {
    fill_triangle(tri.vert[0], tri.vert[1], tri.vert[2], image, color);
}
