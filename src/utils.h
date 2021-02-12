#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <stdexcept>

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
        x = y = z = 0;
    }
    Vec3(T a, T b, T c) {
        x = a;
        y = b;
        z = c;
    }

    Vec3<T> operator + (const Vec3<T>& other) const {
        return Vec3<T>(x + other.x,
                       y + other.y,
                       z + other.z);
    }

    Vec3<T> operator - (const Vec3<T>& other) const {
        return Vec3<T>(x - other.x,
                       y - other.y,
                       z - other.z);
    }

    Vec3<T> operator * (T value) const {
        return Vec3<T>(x * value,
                       y * value,
                       z * value);
    }

    T& operator [] (int i) {
        switch (i) {
          case 0:
            return x;
          case 1:
            return y;
          case 2:
            return z;
          default:
            throw std::out_of_range("Vec3::range_more_than_2");
        }
    }

    const T& operator [] (int i) const {
        switch (i) {
          case 0:
            return x;
          case 1:
            return y;
          case 2:
            return z;
          default:
            throw std::out_of_range("Vec3::range_more_than_2");
        }
    }

    float length() {
        return sqrt(dot_product(*this, *this));
    }

    void normalize() {
        float vec_length = length();
        x /= vec_length;
        y /= vec_length;
        z /= vec_length;
    }

    inline static float dot_product(const Vec3<T>& a, const Vec3<T>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline static Vec3<T> cross_product(const Vec3<T>& a, const Vec3<T>& b) {
        return Vec3<T>(a.y * b.z - a.z * b.y,
                       a.z * b.x - a.x * b.z,
                       a.x * b.y - a.y * b.x);
    }

private: 
    T x, y, z;
};

using Vec3i = Vec3<int>;
using Vec3d = Vec3<double>;

#endif
