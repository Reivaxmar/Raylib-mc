#ifndef UTILS_MC_H
#define UTILS_MC_H

#include <raylib.h>
#include <vector>
#include <raymath.h>
#include <iostream>
#include <cstring>

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
constexpr Vector3i operator*(const Vector3i& l, const Vector3i& r) {
    return (Vector3i){ l.x * r.x, l.y * r.y, l.z * r.z };
}

constexpr bool operator<(const Vector3i& l, const Vector3i& r) {
    if(l.x != r.x) return l.x < r.x;
    if(l.y != r.y) return l.y < r.y;
    return l.z < r.z;
}

struct Vector2i {
    int x, y;

    constexpr Vector2i()
        : x(0), y(0) {}
    constexpr Vector2i(int x, int y)
        : x(x), y(y) {}

    // Vector2 -> Vector2i
    constexpr Vector2i(const Vector2& v)
        : x(static_cast<int>(v.x)),
          y(static_cast<int>(v.y)) {}
    
    // Vector3i -> Vector2i
    constexpr Vector2i(const Vector3i& v)
        : x(static_cast<int>(v.x)),
          y(static_cast<int>(v.y)) {}

    // Vector2i -> Vector2
    constexpr operator Vector2() const {
        return {
            static_cast<float>(x),
            static_cast<float>(y)
        };
    }
};

constexpr Vector2i operator+(const Vector2i& l, const Vector2i& r) {
    return (Vector2i){ l.x + r.x, l.y + r.y };
}
constexpr Vector2i operator-(const Vector2i& l, const Vector2i& r) {
    return (Vector2i){ l.x - r.x, l.y - r.y };
}

struct MeshData {
    std::vector<Vector3> verts;
    std::vector<Vector3> normals;
    std::vector<Vector2> uvs;
    std::vector<unsigned short> indices;

    MeshData() {}

    void UploadData(Mesh& mesh) {
        mesh.vertexCount = verts.size();
        mesh.triangleCount = indices.size() / 3;

        mesh.vertices = static_cast<float*>(MemAlloc(verts.size() * sizeof(Vector3)));
        memcpy(mesh.vertices, verts.data(), verts.size() * sizeof(Vector3));

        mesh.indices = static_cast<unsigned short*>(MemAlloc(indices.size() * sizeof(unsigned short)));
        memcpy(mesh.indices, indices.data(), indices.size() * sizeof(unsigned short));

        mesh.normals = static_cast<float*>(MemAlloc(normals.size() * sizeof(Vector3)));
        memcpy(mesh.normals, normals.data(), normals.size() * sizeof(Vector3));

        mesh.texcoords = static_cast<float*>(MemAlloc(uvs.size() * sizeof(Vector2)));
        memcpy(mesh.texcoords, uvs.data(), uvs.size() * sizeof(Vector2));
    }
};

inline int Vec3_to_idx(Vector3i v, Vector3i map_size) {
    return v.x + v.y * map_size.x + v.z * map_size.x * map_size.y;
}

inline Vector3i idx_to_Vec3(int idx, Vector3i map_size) {
    return Vector3i {
        idx % map_size.x,
        (idx / map_size.x) % map_size.y,
        idx / (map_size.x * map_size.y)
    };
}

inline int floorDiv(int a, int b) {
    int q = a / b;
    int r = a % b;

    if (r != 0 && r < 0)
        --q;

    return q;
}

#endif // UTILS_MC_H