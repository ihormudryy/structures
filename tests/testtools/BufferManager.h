#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef __linux__

#ifndef VBO_H
#define VBO_H
#endif

#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>

namespace opengl
{

class BufferObject
{

public:
    BufferObject();
    ~BufferObject();
    GLuint vbo_vertices;
    GLuint vbo_uv;
    GLuint vbo_normals;
    GLuint ibo_elements;
    GLuint num_indices;
    void initUVBO(GLfloat texuv[], int size);
    void initNBO(GLfloat vert[], int size);
    void initIBO(GLushort ind[], int size);
    void initVBO(GLfloat vert[], int size);
};

}

#endif // LINUX
