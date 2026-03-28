#pragma once
#include <vector>
#include <unordered_map>
#include <cmath>
#include "helper.hpp"

using namespace std;

// Spatial Hashing (masih buruk untuk world yang kecil, misalnya object cow, akibat floating precision)
// Pakai bilangan prima yang besar lalu di or kan, untuk dapat key nya
struct GridKey{
    int x, y, z;

    bool operator==(const GridKey& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct GridHash{
    size_t operator()(const GridKey& k) const {
        return ((k.x * 73856093) ^ (k.y * 19349663) ^ (k.z * 83492791));
    }
};

class FaceBuilder{
    private:
        double voxelSize;

        vector<Vertex> vertices;
        vector<Face> faces;
        unordered_map<GridKey, int, GridHash> vertexMap;

    public:
        FaceBuilder(double size) : voxelSize(size) {}
        
        // convert vertex jadi grid (jadi integer satuan)
        GridKey toGrid(const Vertex& v){
            return{
                (int)round(v.x / voxelSize),
                (int)round(v.y / voxelSize),
                (int)round(v.z / voxelSize)
            };
        }

        // index mapping
        int getIndex(const Vertex& v){
            GridKey key = toGrid(v);

            auto it = vertexMap.find(key);
            if (it != vertexMap.end()) {
                return it->second;
            }

            vertices.push_back(v);
            int idx = vertices.size(); // index mulai dari 1
            vertexMap[key] = idx;

            return idx;
        }


        // add triangle
        void addTriangle(const Vertex& a, const Vertex& b, const Vertex& c) {
            int ia = getIndex(a);
            int ib = getIndex(b);
            int ic = getIndex(c);

            faces.push_back({ia, ib, ic});
        }

        const vector<Vertex>& getVertices() const { return vertices; }
        const vector<Face>& getFaces() const { return faces; }
};

void addVoxelCube(const Vertex& min, const Vertex& max, FaceBuilder& face);