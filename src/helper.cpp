#include "helper.hpp"


double min3(double a, double b, double c){
    return min(min(a,b), c);
}
double max3(double a, double b, double c){
    return max(max(a,b), c);
}

bool checkProject(Vertex v0, Vertex v1, Vertex v2, Vertex axis, Vertex half){
    double p0 = v0.dot(axis);
    double p1 = v1.dot(axis);
    double p2 = v2.dot(axis);

    Vertex u0(1.0, 0.0, 0.0);
    Vertex u1(0.0, 1.0, 0.0);
    Vertex u2(0.0, 0.0, 1.0);
    
    double r = half.x * abs(u0.dot(axis)) + half.y * abs(u1.dot(axis)) + half.z * abs(u2.dot(axis));
    
    return (max(-max3(p0, p1, p2), min3(p0, p1, p2)) > r);
}

bool Intersects(Triangle triangle, Cube aabb) {
    Vertex v0 = triangle.p0;
    Vertex v1 = triangle.p1;
    Vertex v2 = triangle.p2;

    Vertex c = aabb.center;
    Vertex half(aabb.half, aabb.half, aabb.half);

    // Asumsikan kita menggeser kedua objek sejauh c, sehingga center kubus saat ini ada di (0,0)
    v0 = v0 - c;
    v1 = v1 - c;
    v2 = v2 - c;

    // Faces segitiga dalam bentuk vektor
    vector<Vertex> face = {
        v1 - v0,
        v2 - v1,
        v0 - v2
    };

    // Normal satuan bidang kubus
    Vertex u0(1.0, 0.0, 0.0);
    Vertex u1(0.0, 1.0, 0.0);
    Vertex u2(0.0, 0.0, 1.0);

    // Total 13 axis yang harus diuji

    /*~~~~~~~~ 9 Triangle Pojected Axis ~~~~~~~~~~*/
    Vertex axis(0, 0, 0);
    for(int i = 0; i < 3; i++){
        axis = u0 * face[i];
        if(checkProject(v0, v1, v2, axis, half)) return false;
    }
    for(int i = 0; i < 3; i++){
        axis = u1 * face[i];
        if(checkProject(v0, v1, v2, axis, half)) return false;
    }
    for(int i = 0; i < 3; i++){
        axis = u2 * face[i];
        if(checkProject(v0, v1, v2, axis, half)) return false;
    }

    /*~~~~~~~~ 3 Normal Cube Axis ~~~~~~~~~~*/
    /*
    intinya sih cek apakah bounding box segitiga intersect kubus atau tidak
    */
   
    if (max3(v0.x, v1.x, v2.x) < -half.x || min3(v0.x, v1.x, v2.x) > half.x) return false;
    if (max3(v0.y, v1.y, v2.y) < -half.y || min3(v0.y, v1.y, v2.y) > half.y) return false;
    if (max3(v0.z, v1.z, v2.z) < -half.z || min3(v0.z, v1.z, v2.z) > half.z) return false;
   
   
    /*~~~~~~~~ 1 Normal Triangle Axis ~~~~~~~~~~*/
   
    axis = face[0] * face[1];
    if(checkProject(v0, v1, v2, axis, half)) return false;

    // Kalau tidak ada axis yang dapat memisahkan kedua bangunan, maka bangunan tersebut tidak saling berpotongan
    return true;
}
