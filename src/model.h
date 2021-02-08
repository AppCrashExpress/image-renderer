#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <vector>

#include "utils.h"

class Model {
public:
    Model(std::istream& is);
    ~Model() { };

    void draw();

private:
    struct FaceType {
        int vert_i, text_i, norm_i;
    };

    void load_model(std::istream& is);

    std::vector<Vec3d> verts_;
    std::vector<Vec3d> textures_;
    std::vector<Vec3d> norms_;
    std::vector< Vec3<FaceType> > faces_;
};

#endif
