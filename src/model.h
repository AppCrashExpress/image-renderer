#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include "utils.h"
#include "tgaimage.h"

class Model {
public:
    Model(std::istream& is);
    Model(std::istream& is, const TGAImage& texture);
    ~Model() { };

    TGAImage get_texture() const {
        return texture_;
    }

    const std::vector<Vec3d>& get_verts() const {
        return verts_;
    }
    const std::vector<Vec3d>& get_texture_coords() const {
        return textures_;
    }

    const std::vector<Vec3i> get_face_verts() const;
    const std::vector<Vec3i> get_face_text_coords() const;

    bool has_texture() {
        return has_texture_;
    }
    

private:
    void load_model(std::istream& is);

    TGAImage texture_;
    bool has_texture_;

    std::vector<Vec3d> verts_;
    std::vector<Vec3d> textures_;
    std::vector<Vec3d> norms_;

    std::vector<Vec3i> face_verts_;
    std::vector<Vec3i> face_textures_;
    std::vector<Vec3i> face_norms_;
};

#endif
