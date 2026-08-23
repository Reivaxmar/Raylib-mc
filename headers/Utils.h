#ifndef UTILS_H
#define UTILS_H

#include <raylib.h>

struct Vector3i {
    int x, y, z;

    constexpr Vector3i()
        : x(0), y(0), z(0) {}
    constexpr Vector3i(int x, int y, int z)
        : x(x), y(y), z(z) {}

    // Vector3 -> Vector3i
    constexpr Vector3i(const Vector3& v)
        : x(static_cast<int>(v.x)),
          y(static_cast<int>(v.y)),
          z(static_cast<int>(v.z)) {}

    // Vector3i -> Vector3
    constexpr operator Vector3() const {
        return {
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(z)
        };
    }
};

constexpr Vector3i operator+(const Vector3i& l, const Vector3i& r) {
    return (Vector3i){ l.x + r.x, l.y + r.y, l.z + r.z };
}
constexpr Vector3i operator-(const Vector3i& l, const Vector3i& r) {
    return (Vector3i){ l.x - r.x, l.y - r.y, l.z - r.z };
}

// constexpr Vector3 operator+(const Vector3& l, const Vector3& r) {
//     return (Vector3){ l.x + r.x, l.y + r.y, l.z + r.z };
// }
// constexpr Vector3 operator-(const Vector3& l, const Vector3& r) {
//     return (Vector3){ l.x - r.x, l.y - r.y, l.z - r.z };
// }

int Vec3_to_idx(Vector3i v, Vector3i map_size) {
    return v.x + v.y * map_size.x + v.z * map_size.x * map_size.y;
}

Vector3i idx_to_Vec3(int idx, Vector3i map_size) {
    return Vector3i {
        idx % map_size.x,
        (idx / map_size.x) % map_size.y,
        idx / (map_size.x * map_size.y)
    };
}

#endif // UTILS_H