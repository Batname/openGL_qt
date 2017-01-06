
#ifndef ShapeGenerator_hpp
#define ShapeGenerator_hpp

#include <iostream>

#include "Vertex.h"
#include "ShapeData.h"

#include <glm/glm.hpp>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

class ShapeGenerator
{
public:
    static ShapeData makeTrianle();
    static ShapeData makeCube();
    static ShapeData makeArrow();
};

#endif /* ShapeGenerator_hpp */
