#include "model.h"

#include <string>
#include "utils.h"

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
            points[i] = { i_vert, i_text, i_norm };
        }

        faces_.push_back( Vec3<FaceType>(points[0], points[1], points[2]) );

        if ( !(is >> tag) ) { break; }
    }
}
