
#ifndef ShapeGenerator_hpp
#define ShapeGenerator_hpp

#include <iostream>

#include "Vertex.h"
#include "ShapeData.h"

#include <glm/glm.hpp>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

class ShapeGenerator
{
private:
    static ShapeData makePlaneVerts(uint dimensions);
    static ShapeData makePlaneIndices(uint dimensions);

public:
    static ShapeData makeTrianle();
    static ShapeData makeCube();
    static ShapeData makeArrow();
    static ShapeData makePlane(uint dimensions = 10);
};

#endif /* ShapeGenerator_hpp */
