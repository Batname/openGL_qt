#ifndef ShapeData_h
#define ShapeData_h

#include <GL/glew.h>
#include "Vertex.h"

struct ShapeData
{
    ShapeData() :
        vertices(nullptr), numVertices(0),
    indices(0), numIndices(0) {}
    Vertex *vertices;
    GLuint numVertices;
    GLushort *indices;
    GLuint numIndices;
    
    GLuint vertexBufferSize() const
    {
        return numVertices * sizeof(Vertex);
    }
    
    GLuint indexBufferSize() const
    {
        return numIndices * sizeof(GLushort);
    }
    
    void clean()
    {
        free(vertices);
        free(indices);
        
        numVertices = numIndices = 0;
    }
};


#endif /* ShapeData_h */
