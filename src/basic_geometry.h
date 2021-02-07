#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "tgaimage.h"
#include "utils.h"

void draw_line(int x0, int y0, int x, int y, 
        TGAImage& image, const TGAColor& color);
void draw_line(const Point& p0, const Point& p1, 
        TGAImage& image, const TGAColor& color);

void draw_triangle(Point p0, Point p1, Point p2, 
        TGAImage& image, const TGAColor& color);
void draw_triangle(const Triangle& tri,
        TGAImage& image, const TGAColor& color);


#endif
