#include "faceBuilder.hpp"

void addVoxelCube(const Vertex& min, const Vertex& max, FaceBuilder& face) {
// Ini untuk ubah dari Voxel cube ke face segitiga

    // 8 titik cube
    Vertex v000 = {min.x, min.y, min.z};
    Vertex v001 = {min.x, min.y, max.z};
    Vertex v010 = {min.x, max.y, min.z};
    Vertex v011 = {min.x, max.y, max.z};
    Vertex v100 = {max.x, min.y, min.z};
    Vertex v101 = {max.x, min.y, max.z};
    Vertex v110 = {max.x, max.y, min.z};
    Vertex v111 = {max.x, max.y, max.z};

    // +X
    face.addTriangle(v100, v110, v111);
    face.addTriangle(v100, v111, v101);

    // -X
    face.addTriangle(v000, v011, v010);
    face.addTriangle(v000, v001, v011);

    // +Y
    face.addTriangle(v010, v111, v110);
    face.addTriangle(v010, v011, v111);

    // -Y
    face.addTriangle(v000, v100, v101);
    face.addTriangle(v000, v101, v001);

    // +Z
    face.addTriangle(v001, v101, v111);
    face.addTriangle(v001, v111, v011);

    // -Z
    face.addTriangle(v000, v110, v100);
    face.addTriangle(v000, v010, v110);
}