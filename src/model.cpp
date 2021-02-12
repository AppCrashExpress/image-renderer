#include "model.h"

#include <string>
#include "utils.h"

Model::Model(std::istream& is) {
    has_texture_ = false;

    load_model(is);
}

Model::Model(std::istream& is, const TGAImage& texture) {
    has_texture_ = true;

    load_model(is);
    texture_ = texture;
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
    
    if (has_texture_) {
        while ( tag != "vt" ) {
            is >> tag;
        }

        while (tag == "vt") {
            is >> a >> b >> c;
            textures_.push_back( Vec3d(a, b, c) );
            if ( !(is >> tag) ) { break; }
        }
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

    Vec3i i_vert, i_text, i_norm;
    char sep;
    while (tag == "f") {
        for (short i = 0; i < 3; ++i) {
            is >> i_vert[i] >> sep 
               >> i_text[i] >> sep 
               >> i_norm[i];
            // Reduce by one before putting since 
            // incdecies start from one
            --i_vert[i];
            --i_text[i];
            --i_norm[i];
        }

        face_verts_.push_back(i_vert);
        face_textures_.push_back(i_text);
        face_norms_.push_back(i_norm);

        if ( !(is >> tag) ) { break; }
    }
}


const std::vector<Vec3i> Model::get_face_verts() const {
    return face_verts_;
}

const std::vector<Vec3i> Model::get_face_textures() const {
    return face_textures_;
}
