#pragma once
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include "vertex.hpp"

using namespace std;

struct Cube{
    Vertex center, min, max;
    double half;
};

struct Triangle{
    Vertex p0, p1, p2;
};

struct Face{
    int a, b, c;
};

double min3(double a, double b, double c);
double max3(double a, double b, double c);
bool checkProject(Vertex v0, Vertex v1, Vertex v2, Vertex axis, Vertex half);
bool Intersects(Triangle triangle, Cube aabb);