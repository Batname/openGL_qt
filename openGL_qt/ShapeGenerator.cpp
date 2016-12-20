
#include "ShapeGenerator.hpp"

ShapeData ShapeGenerator::makeTrianle()
{
    ShapeData ret;
    Vertex verts[] = {
        glm::vec3(+0.0f, +1.0f, +0.5),
        glm::vec3(+1.0f, +0.0f, +0.0f),
        
        glm::vec3(+1.0f, -1.0f, +0.5),
        glm::vec3(+0.0f, +1.0f, +0.0f),
        
        glm::vec3(-1.0f, -1.0f, +0.5),
        glm::vec3(+0.0f, +0.0f, +1.0f)
    };
    
    ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
    
    GLushort indices[] = { 0, 1, 2 };
    
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, verts, sizeof(verts));

    ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
    ret.indices = new GLushort[ret.numIndices];
    memcmp(ret.indices, indices, sizeof(indices));
    
    return ret;
}
