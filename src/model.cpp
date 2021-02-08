#include "model.h"

#include <string>
#include "utils.h"
#include "basic_geometry.h"

Model::Model(std::istream& is) {
    load_model(is);
}

void Model::load_model(std::istream& is) {
    std::string tag;
    is >> tag;

    double a, b, c;

    while (tag == "v") {
        is >> a >> b >> c;
        verts_.push_back( Vec3d(a, b, c) );
        if ( !(is >> tag) ) { break; }
    }
    
    while ( tag != "vt" ) {
        is >> tag;
    }

    while (tag == "vt") {
        is >> a >> b >> c;
        textures_.push_back( Vec3d(a, b, c) );
        if ( !(is >> tag) ) { break; }
    }

    while ( tag != "vn" ) {
        is >> tag;
    }

    while (tag == "vn") {
        is >> a >> b >> c;
        norms_.push_back( Vec3d(a, b, c) );
        if ( !(is >> tag) ) { break; }
    }

    while ( tag != "f" ) {
        is >> tag;
    }

    int i_vert, i_text, i_norm;
    char sep;
    while (tag == "f") {
        FaceType points[3];
        for (short i = 0; i < 3; ++i) {
            is >> i_vert >> sep 
               >> i_text >> sep 
               >> i_norm;
            // Reduce by one before putting since 
            // incdecies start from one
            points[i] = { --i_vert, --i_text, --i_norm };
        }

        faces_.push_back( Vec3<FaceType>(points[0], points[1], points[2]) );

        if ( !(is >> tag) ) { break; }
    }
}

void Model::draw(TGAImage& image, const TGAColor& color) {
    int height = image.get_height();
    int width  = image.get_width();

    for (const auto& face : faces_) {
        for (int i = 0; i < 3; ++i) {
            const Vec3d& vert_a = verts_[face[i].vert_i];
            const Vec3d& vert_b = verts_[face[(i + 1) % 3].vert_i];
            
            int x0 = (vert_a[0] + 1.0f) * width / 2;
            int y0 = (vert_a[1] + 1.0f) * height / 2;
            int x1 = (vert_b[0] + 1.0f) * width / 2;
            int y1 = (vert_b[1] + 1.0f) * height / 2;
           
            draw_line(x0, y0, x1, y1, image, color); 
        }
    }
}
