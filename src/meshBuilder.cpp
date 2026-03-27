#include "meshBuilder.hpp"

void addVoxelCube(const Vertex& min, const Vertex& max, MeshBuilder& mesh) {

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
    mesh.addTriangle(v100, v110, v111);
    mesh.addTriangle(v100, v111, v101);

    // -X
    mesh.addTriangle(v000, v011, v010);
    mesh.addTriangle(v000, v001, v011);

    // +Y
    mesh.addTriangle(v010, v111, v110);
    mesh.addTriangle(v010, v011, v111);

    // -Y
    mesh.addTriangle(v000, v100, v101);
    mesh.addTriangle(v000, v101, v001);

    // +Z
    mesh.addTriangle(v001, v101, v111);
    mesh.addTriangle(v001, v111, v011);

    // -Z
    mesh.addTriangle(v000, v110, v100);
    mesh.addTriangle(v000, v010, v110);
}