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

template <typename T>
class Vec3 {
public:
    Vec3() {
        values_[0] = 0;
        values_[1] = 0;
        values_[2] = 0;
    }
    Vec3(T a, T b, T c) {
        values_[0] = a;
        values_[1] = b;
        values_[2] = c;
    }

    Vec3<T> operator + (const Vec3<T>& other) const {
        return Vec3<T>(values_[0] + other.values_[0],
                       values_[1] + other.values_[1],
                       values_[2] + other.values_[2]);
    }

    Vec3<T> operator - (const Vec3<T>& other) const {
        return Vec3<T>(values_[0] - other.values_[0],
                       values_[1] - other.values_[1],
                       values_[2] - other.values_[2]);
    }

    T& operator [] (int i) {
        return values_[i];
    }

    const T& operator [] (int i) const {
        return values_[i];
    }

private: 
    T values_[3];
};

using Vec3i = Vec3<int>;
using Vec3d = Vec3<double>;

#endif
