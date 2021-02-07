#ifndef UTILS_H
#define UTILS_H

template <typename T>
inline short sign(T value) {
    return (T(0) < value) - (T(0) > value);
}

struct Point {
    int x, y;
};

struct Triangle {
    Point vert[3];
};

#endif
