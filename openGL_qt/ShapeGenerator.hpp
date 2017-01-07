
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
    static void moveLid(int grid, float *v, glm::mat4 lidTransform);
    static void generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid);
    static void computeBasisFunctions(float * B, float * dB, int grid);
    static void buildPatchReflect(int patchNum,
                                  float *B, float *dB,
                                  float *v, float *n,
                                  float *tc, unsigned short *el,
                                  int &index, int &elIndex, int &tcIndex, int grid,
                                  bool reflectX, bool reflectY);
    static void buildPatch(glm::vec3 patch[][4],
                           float *B, float *dB,
                           float *v, float *n, float *tc,
                           unsigned short *el,
                           int &index, int &elIndex, int &tcIndex,
                           int grid, glm::mat3 reflect,
                           bool invertNormal);
    static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);
    
    static glm::vec3 evaluate(int gridU, int gridV, float *B, glm::vec3 patch[][4]);
    static glm::vec3 evaluateNormal(int gridU, int gridV,
                                    float *B, float *dB, glm::vec3 patch[][4]);


public:
    static ShapeData makeTrianle();
    static ShapeData makeCube();
    static ShapeData makeArrow();
    static ShapeData makePlane(uint dimensions = 10);
    static ShapeData makeTeapot(uint tesselation = 10, const glm::mat4& lidTransform = glm::mat4());

};

#endif /* ShapeGenerator_hpp */
