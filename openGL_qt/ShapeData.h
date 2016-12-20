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
    
    GLsizeiptr vertexBufferSize() const
    {
        return numVertices * sizeof(Vertex);
    }
    
    GLsizeiptr indexBufferSize() const
    {
        return numIndices * sizeof(GLushort);
    }
    
    void clean()
    {
        free(vertices);
        free(indices);
    }
};


#endif /* ShapeData_h */
