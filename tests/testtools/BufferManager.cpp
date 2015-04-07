#include "BufferManager.h"

#include <iostream>
#include <string>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <gtc/type_ptr.hpp>

namespace opengl {

BufferObject::BufferObject()
{
}

BufferObject::~BufferObject()
{
    //if(vbo_vertices) glDeleteVertexArrays(1, &vbo_vertices);
    //if(vbo_uv) glDeleteVertexArrays(1, &vbo_uv);
    //if(vbo_normals) glDeleteVertexArrays(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   
}

void BufferObject::initVBO(GLfloat vert[], int size)
{
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, size, vert, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::initUVBO(GLfloat texuv[], int size)
{
    glGenBuffers(1, &vbo_uv);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, size, texuv, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::initNBO(GLfloat norm[], int size)
{
    glGenBuffers(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, size, norm, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BufferObject::initIBO(GLushort ind[], int size)
{
    glGenBuffers(1, &ibo_elements);
    num_indices = size/sizeof(*ind);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_elements);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, ind, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
