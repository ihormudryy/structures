#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <GLES3/gl3platform.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <bmp_generator.h>
#include <ShaderManager.h>
#include <BufferManager.h>
#include <TextureManager.h>

namespace supertest
{

#define WIDTH 800
#define HEIGHT 600
#define LINE_RENDERER_MAX_LINES 1024
#define END_OF_PRIMITIVE_ID 9999999
#define LINERENDERER_UNIFORM_ATTR_POSITION 0
#define LINERENDERER_UNIFORM_ATTR_OTHERVERT 1
#define LINERENDERER_UNIFORM_ATTR_OFFSETDIR_UV 2
#define GL_BUFFER_OFFSET(i) ((char*)NULL+(i))

using namespace std;
using namespace testtools;
using namespace opengl;

Display* dpy;
Window xWin;
XVisualInfo* vInfo;
XSetWindowAttributes swa;
GLXFBConfig *fbConfigs;
GLXContext winCtx;
GLXWindow glxWin;
int swaMask;
int numReturned;
Colormap cmap;
ShaderManager program;

const int singleBufferAttributess[] =
{
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_RED_SIZE,      1,
    GLX_GREEN_SIZE,    1,
    GLX_BLUE_SIZE,     1,
    None
};

const int doubleBufferAttributes[] =
{
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE,   GLX_RGBA_BIT,
    GLX_DOUBLEBUFFER,  1,
    GLX_RED_SIZE,      1,
    GLX_GREEN_SIZE,    1,
    GLX_BLUE_SIZE,     1,
    None
};

int context_attribs[] = {
    GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
    GLX_CONTEXT_MINOR_VERSION_ARB, 1,
    GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_DEBUG_BIT_ARB,
    GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
    None
};


void readBufferToFile(char* name)
{
    GLubyte* data = new GLubyte[WIDTH*3*HEIGHT];
    glReadBuffer(GL_FRONT);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glCopyPixels(0, 0, WIDTH, HEIGHT, GL_COLOR);
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, data);

    FILE* filePtr = fopen(name, "wb");
    ASSERT_TRUE(filePtr != NULL);
    BmpGenerator::write_bmp24(filePtr, WIDTH, HEIGHT, data);
    fclose(filePtr);
}

BufferObject initCube()
{
    GLfloat cube_vertices[] = {
        // Front face
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // Back face
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0, -1.0, -1.0,
        // Top face
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0,  1.0,
         1.0,  1.0, -1.0,
        // Bottom face
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,
        // Right face
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0,  1.0,  1.0,
         1.0, -1.0,  1.0,
        // Left face
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0
    };

    GLfloat cube_colors[] = {
        // Front face
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        // Back face
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        // Top face
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        // Bottom face
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        // Right face
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        // Left face
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
    };

    GLfloat cube_normals[] = {
        // Front face
         0.0,  0.0,  1.0,
         0.0,  0.0,  1.0,
         0.0,  0.0,  1.0,
         0.0,  0.0,  1.0,
        // Back face
         0.0,  0.0, -1.0,
         0.0,  0.0, -1.0,
         0.0,  0.0, -1.0,
         0.0,  0.0, -1.0,
        // Top face
         0.0,  1.0,  0.0,
         0.0,  1.0,  0.0,
         0.0,  1.0,  0.0,
         0.0,  1.0,  0.0,
        // Bottom face
         0.0, -1.0,  0.0,
         0.0, -1.0,  0.0,
         0.0, -1.0,  0.0,
         0.0, -1.0,  0.0,
        // Right face
         1.0,  0.0,  0.0,
         1.0,  0.0,  0.0,
         1.0,  0.0,  0.0,
         1.0,  0.0,  0.0,
        // Left face
        -1.0,  0.0,  0.0,
        -1.0,  0.0,  0.0,
        -1.0,  0.0,  0.0,
        -1.0,  0.0,  0.0
    };

    GLushort cube_elements[] = {
        0, 1, 2,      0, 2, 3,    // Front face
        4, 5, 6,      4, 6, 7,    // Back face
        8, 9, 10,     8, 10, 11,  // Top face
        12, 13, 14,   12, 14, 15, // Bottom face
        16, 17, 18,   16, 18, 19, // Right face
        20, 21, 22,   20, 22, 23  // Left face
    };

    BufferObject obj;
    obj.initVBO(cube_vertices, sizeof(cube_vertices));
    obj.initNBO(cube_normals, sizeof(cube_normals));
    obj.initUVBO(cube_colors, sizeof(cube_colors));
    obj.initIBO(cube_elements, sizeof(cube_elements));
    return obj;
}

struct vertex_line
{
    GLfloat gpupLine_radius;
    GLfloat gpupLine_invScrRatio;
    GLuint gpupLine_lineTexture;
    GLuint linesEABO;
    GLuint vertex0VBO;
    GLuint vertex1VBO;
    GLuint offsetDirUvVBO;
    GLuint lineVA;
    float vertex0[LINE_RENDERER_MAX_LINES*8*3];
    float vertex1[LINE_RENDERER_MAX_LINES*8*3];
    float screenRatio;
};

float lines[33*2*3] =
{
        // Front face
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
        // Back face
        -1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0, -1.0, -1.0,
        // Top face
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0,  1.0,
         1.0,  1.0, -1.0,
        // Bottom face
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
         1.0, -1.0,  1.0,
        -1.0, -1.0,  1.0,
        // Right face
         1.0, -1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0,  1.0,  1.0,
         1.0, -1.0,  1.0,
        // Left face
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0, -1.0
    };
/*{
    ///// basic
    1.0f,0.0f,0.0f,
    10.0f,0.0f,0.0f,
    0.0f,1.0f,0.0f,
    0.0f,10.0f,0.0f,
    0.0f,0.0f,1.0f,
    0.0f,0.0f,10.0f,
    1.0f,1.0f,1.0f,
    10.0f,10.0f,10.0f,


    ///// cube
    2.0f, 2.0f, 2.0f,
    4.0f, 2.0f, 2.0f,
    4.0f, 2.0f, 2.0f,
    4.0f, 4.0f, 2.0f,
    4.0f, 4.0f, 2.0f,
    2.0f, 4.0f, 2.0f,
    2.0f, 4.0f, 2.0f,
    2.0f, 2.0f, 2.0f,

    2.0f, 2.0f, 4.0f,
    4.0f, 2.0f, 4.0f,
    4.0f, 2.0f, 4.0f,
    4.0f, 4.0f, 4.0f,
    4.0f, 4.0f, 4.0f,
    2.0f, 4.0f, 4.0f,
    2.0f, 4.0f, 4.0f,
    2.0f, 2.0f, 4.0f,

    2.0f, 2.0f, 2.0f,
    2.0f, 2.0f, 4.0f,
    4.0f, 2.0f, 2.0f,
    4.0f, 2.0f, 4.0f,
    4.0f, 4.0f, 2.0f,
    4.0f, 4.0f, 4.0f,
    2.0f, 4.0f, 2.0f,
    2.0f, 4.0f, 4.0f,


    ///// pyramid
    -2.0f, 0.0f,-2.0f,
    -4.0f, 0.0f,-2.0f,
    -4.0f, 0.0f,-2.0f,
    -4.0f, 0.0f,-4.0f,
    -4.0f, 0.0f,-4.0f,
    -2.0f, 0.0f,-4.0f,
    -2.0f, 0.0f,-4.0f,
    -2.0f, 0.0f,-2.0f,

    -2.25f, 0.5f,-2.25f,
    -3.75f, 0.5f,-2.25f,
    -3.75f, 0.5f,-2.25f,
    -3.75f, 0.5f,-3.75f,
    -3.75f, 0.5f,-3.75f,
    -2.25f, 0.5f,-3.75f,
    -2.25f, 0.5f,-3.75f,
    -2.25f, 0.5f,-2.25f,

    -2.5f, 1.0f,-2.5f,
    -3.5f, 1.0f,-2.5f,
    -3.5f, 1.0f,-2.5f,
    -3.5f, 1.0f,-3.5f,
    -3.5f, 1.0f,-3.5f,
    -2.5f, 1.0f,-3.5f,
    -2.5f, 1.0f,-3.5f,
    -2.5f, 1.0f,-2.5f,

    -2.75f, 1.5f,-2.75f,
    -3.25f, 1.5f,-2.75f,
    -3.25f, 1.5f,-2.75f,
    -3.25f, 1.5f,-3.25f,
    -3.25f, 1.5f,-3.25f,
    -2.75f, 1.5f,-3.25f,
    -2.75f, 1.5f,-3.25f,
    -2.75f, 1.5f,-2.75f,


    //single line
    -5.0f,0.0f,-3.0f,
    -5.0f,1.5f,-3.0f,

};*/

vertex_line initVertex()
{
    vertex_line m_line_render;
    m_line_render.gpupLine_invScrRatio = (float)WIDTH/HEIGHT;
    m_line_render.gpupLine_radius = 0.01;

    glGenBuffers(1, &m_line_render.vertex0VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_line_render.vertex0VBO);
    glBufferData(GL_ARRAY_BUFFER, LINE_RENDERER_MAX_LINES*3*8*sizeof(float), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glGenBuffers(1, &m_line_render.vertex1VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_line_render.vertex1VBO);
    glBufferData(GL_ARRAY_BUFFER, LINE_RENDERER_MAX_LINES*3*8*sizeof(float), NULL, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    float* offsetDirUv = new float[LINE_RENDERER_MAX_LINES*4*8];
    for(int v=0; v<LINE_RENDERER_MAX_LINES*4*8; v+=4*8)
    {
        offsetDirUv[v   ] = 1.0f;		offsetDirUv[v+1 ] = 1.0f;		offsetDirUv[v+2 ] = 1.0f;		offsetDirUv[v+3 ] = 0.0f;
        offsetDirUv[v+4 ] = 1.0f;		offsetDirUv[v+5 ] =-1.0f;		offsetDirUv[v+6 ] = 1.0f;		offsetDirUv[v+7 ] = 1.0f;
        offsetDirUv[v+8 ] = 0.0f;		offsetDirUv[v+9 ] = 1.0f;		offsetDirUv[v+10] = 0.5f;		offsetDirUv[v+11] = 0.0f;
        offsetDirUv[v+12] = 0.0f;		offsetDirUv[v+13] =-1.0f;		offsetDirUv[v+14] = 0.5f;		offsetDirUv[v+15] = 1.0f;
        offsetDirUv[v+16] = 0.0f;		offsetDirUv[v+17] =-1.0f;		offsetDirUv[v+18] = 0.5f;		offsetDirUv[v+19] = 0.0f;
        offsetDirUv[v+20] = 0.0f;		offsetDirUv[v+21] = 1.0f;		offsetDirUv[v+22] = 0.5f;		offsetDirUv[v+23] = 1.0f;
        offsetDirUv[v+24] = 1.0f;		offsetDirUv[v+25] =-1.0f;		offsetDirUv[v+26] = 0.0f;		offsetDirUv[v+27] = 0.0f;
        offsetDirUv[v+28] = 1.0f;		offsetDirUv[v+29] = 1.0f;		offsetDirUv[v+30] = 0.0f;		offsetDirUv[v+31] = 1.0f;
    }
    glGenBuffers(1, &m_line_render.offsetDirUvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_line_render.offsetDirUvVBO);
    glBufferData(GL_ARRAY_BUFFER, LINE_RENDERER_MAX_LINES*4*8*sizeof(float), offsetDirUv, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    delete [] offsetDirUv;

    GLuint* trisStripElements = new GLuint[LINE_RENDERER_MAX_LINES*8 + LINE_RENDERER_MAX_LINES];
    glGenBuffers(1, &m_line_render.linesEABO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_line_render.linesEABO);
    GLuint lineID=0;
    for(int t=0; t<(LINE_RENDERER_MAX_LINES*8 + LINE_RENDERER_MAX_LINES); t+=(8+1), lineID+=8)
    {
        trisStripElements[t  ] = lineID;
        trisStripElements[t+1] = lineID+1;
        trisStripElements[t+2] = lineID+2;
        trisStripElements[t+3] = lineID+3;
        trisStripElements[t+4] = lineID+4;
        trisStripElements[t+5] = lineID+5;
        trisStripElements[t+6] = lineID+6;
        trisStripElements[t+7] = lineID+7;
        trisStripElements[t+8] = END_OF_PRIMITIVE_ID;
    }
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (LINE_RENDERER_MAX_LINES*8 + LINE_RENDERER_MAX_LINES)*sizeof(float), trisStripElements, GL_STATIC_DRAW);
    delete [] trisStripElements;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_line_render.linesEABO);
    glGenVertexArrays(1, &m_line_render.lineVA);
    glBindVertexArray(m_line_render.lineVA);
        glBindBuffer(GL_ARRAY_BUFFER, m_line_render.vertex0VBO);
        glVertexAttribPointer(LINERENDERER_UNIFORM_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 0, GL_BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, m_line_render.vertex1VBO);
        glVertexAttribPointer(LINERENDERER_UNIFORM_ATTR_OTHERVERT, 3, GL_FLOAT, GL_FALSE, 0, GL_BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, m_line_render.offsetDirUvVBO);
        glVertexAttribPointer(LINERENDERER_UNIFORM_ATTR_OFFSETDIR_UV, 4, GL_FLOAT, GL_FALSE, 0, GL_BUFFER_OFFSET(0));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glEnableVertexAttribArray(LINERENDERER_UNIFORM_ATTR_POSITION);
        glEnableVertexAttribArray(LINERENDERER_UNIFORM_ATTR_OTHERVERT);
        glEnableVertexAttribArray(LINERENDERER_UNIFORM_ATTR_OFFSETDIR_UV);
    glBindVertexArray(0);

    return m_line_render;
}

void renderVertex(vertex_line& object, int i)
{
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.5);

    //mat4 model = translate(mat4(1.0f), vec3(cos(i*.05), sin(i*.05), -4.0));
    mat4 model = translate(mat4(1.0f), vec3(0, 0, -3.0));
    mat4 view = lookAt(vec3(0.0, 2.0, 0.0), vec3(0.0, 0.0, -4.0), vec3(0.0, 1.0, 0.0));
    mat4 projection = perspective(45.0f, (float)WIDTH/HEIGHT, 0.1f, 10.0f);
    mat4 MVP = projection * view * model;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //int l=1;
    for(unsigned int l=0; l < LINE_RENDERER_MAX_LINES; ++l)
    {
        const int lA = l*6;
        const int lB = l*6 + 3;
        const int l24 = l*24;
        object.vertex0[l24   ] = lines[lA];		object.vertex0[l24+1 ] = lines[lA+1];		object.vertex0[l24+2 ] = lines[lA+2];
        object.vertex0[l24+3 ] = lines[lA];		object.vertex0[l24+4 ] = lines[lA+1];		object.vertex0[l24+5 ] = lines[lA+2];
        object.vertex0[l24+6 ] = lines[lA];		object.vertex0[l24+7 ] = lines[lA+1];		object.vertex0[l24+8 ] = lines[lA+2];
        object.vertex0[l24+9 ] = lines[lA];		object.vertex0[l24+10] = lines[lA+1];		object.vertex0[l24+11] = lines[lA+2];

        object.vertex0[l24+12] = lines[lB];		object.vertex0[l24+13] = lines[lB+1];		object.vertex0[l24+14] = lines[lB+2];
        object.vertex0[l24+15] = lines[lB];		object.vertex0[l24+16] = lines[lB+1];		object.vertex0[l24+17] = lines[lB+2];
        object.vertex0[l24+18] = lines[lB];		object.vertex0[l24+19] = lines[lB+1];		object.vertex0[l24+20] = lines[lB+2];
        object.vertex0[l24+21] = lines[lB];		object.vertex0[l24+22] = lines[lB+1];		object.vertex0[l24+23] = lines[lB+2];
    }

    for(unsigned int l=0; l < LINE_RENDERER_MAX_LINES; ++l)
    {
        const int lA = l*6;
        const int lB = l*6 + 3;
        const int l24 = l*24;
        object.vertex1[l24   ] = lines[lB];		object.vertex1[l24+1 ] = lines[lB+1];		object.vertex1[l24+2 ] = lines[lB+2];
        object.vertex1[l24+3 ] = lines[lB];		object.vertex1[l24+4 ] = lines[lB+1];		object.vertex1[l24+5 ] = lines[lB+2];
        object.vertex1[l24+6 ] = lines[lB];		object.vertex1[l24+7 ] = lines[lB+1];		object.vertex1[l24+8 ] = lines[lB+2];
        object.vertex1[l24+9 ] = lines[lB];		object.vertex1[l24+10] = lines[lB+1];		object.vertex1[l24+11] = lines[lB+2];

        object.vertex1[l24+12] = lines[lA];		object.vertex1[l24+13] = lines[lA+1];		object.vertex1[l24+14] = lines[lA+2];
        object.vertex1[l24+15] = lines[lA];		object.vertex1[l24+16] = lines[lA+1];		object.vertex1[l24+17] = lines[lA+2];
        object.vertex1[l24+18] = lines[lA];		object.vertex1[l24+19] = lines[lA+1];		object.vertex1[l24+20] = lines[lA+2];
        object.vertex1[l24+21] = lines[lA];		object.vertex1[l24+22] = lines[lA+1];		object.vertex1[l24+23] = lines[lA+2];
    }

    glUseProgram(program.id);
    {
        glBindBuffer(GL_ARRAY_BUFFER, object.vertex0VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0, LINE_RENDERER_MAX_LINES*8*3*sizeof(float), object.vertex0);
        glBindBuffer(GL_ARRAY_BUFFER, object.vertex1VBO);
        glBufferSubData(GL_ARRAY_BUFFER,0, LINE_RENDERER_MAX_LINES*8*3*sizeof(float), object.vertex1);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDisable(GL_CULL_FACE);
        program.setMatrixUniform("MVP", MVP);
        program.setUniform1f("radius", object.gpupLine_radius + i*0.0005);
        program.setUniform1f("invScrRatio", 1.0f/object.gpupLine_invScrRatio);
        program.setUniform1i("lineTexture", 0);
        glEnable(GL_TEXTURE_2D);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, object.gpupLine_lineTexture);
        glEnable(GL_PRIMITIVE_RESTART);
        glPrimitiveRestartIndex(END_OF_PRIMITIVE_ID);
        glBindVertexArray(object.lineVA);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.linesEABO);
        glDrawElements(GL_TRIANGLE_STRIP, LINE_RENDERER_MAX_LINES*(8+1), GL_UNSIGNED_INT, GL_BUFFER_OFFSET(0));
        glXSwapBuffers(dpy, glxWin);
        glBindVertexArray(0);
        glDisable(GL_PRIMITIVE_RESTART);
    }
    glUseProgram(0);
}

void draw(BufferObject& object, Texture& texture, int i)
{
    glViewport(0, 0, WIDTH, HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 0.5);
    glUseProgram(program.id);
    glPushMatrix();

    //mat4 model = translate(mat4(1.0f), vec3(cos(i*.05), sin(i*.05), -4.0));
    mat4 model = translate(mat4(1.0f), vec3(0, 0, -3.0));
    mat4 view = lookAt(vec3(0.0, 2.0, 0.0), vec3(0.0, 0.0, -4.0), vec3(0.0, 1.0, 0.0));
    mat4 projection = perspective(45.0f, (float)WIDTH/HEIGHT, 0.1f, 10.0f);
    mat4 mvp = projection * view * model;

    program.setMatrixUniform("uMVP", mvp);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnableVertexAttribArray(program.getAttribute("aVertexPosition"));
    glBindBuffer(GL_ARRAY_BUFFER, object.vbo_vertices);
    program.setAttributePointer("aVertexPosition", 3);

    glEnableVertexAttribArray(program.getAttribute("aNormals"));
    glBindBuffer(GL_ARRAY_BUFFER, object.vbo_normals);
    program.setAttributePointer("aNormals", 3);

    glEnableVertexAttribArray(program.getAttribute("aTextureUv"));
    glBindBuffer(GL_ARRAY_BUFFER, object.vbo_uv);
    program.setAttributePointer("aTextureUv", 2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object.ibo_elements);

    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(program.getUniform("textureMap"), 0);
    glBindTexture(GL_TEXTURE_2D, texture.textureID);

    glDrawElements(GL_TRIANGLES, object.num_indices, GL_UNSIGNED_SHORT, 0);

    glXSwapBuffers(dpy, glxWin);

    glPopMatrix();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDisableVertexAttribArray(program.getAttribute("aVertexPosition"));
    glDisableVertexAttribArray(program.getAttribute("aVertexColor"));
    glUseProgram(0);
}

TEST(TestAntialiasedVolumetricLines, Test1)
{
    dpy = XOpenDisplay(NULL);

    if (dpy == NULL)
    {
        printf( "Unable to open a connection to the X server\n" );
        exit(EXIT_FAILURE);
    }

    fbConfigs = glXChooseFBConfig(dpy,
                                  DefaultScreen(dpy),
                                  doubleBufferAttributes,
                                  &numReturned);

    if (fbConfigs == NULL)
    {
        fbConfigs = glXChooseFBConfig(dpy,
                                      DefaultScreen(dpy),
                                      singleBufferAttributess,
                                      &numReturned);
    }

    vInfo = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);

    ASSERT_TRUE(vInfo != NULL);

    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;
    cmap = XCreateColormap(dpy, RootWindow(dpy, vInfo->screen), vInfo->visual, AllocNone);
    swa.colormap = cmap;

    swaMask = CWBorderPixel | CWColormap | CWEventMask;
    swa.event_mask = ExposureMask | KeyPressMask;

    xWin = XCreateWindow( dpy, RootWindow(dpy, vInfo->screen), 0, 0, WIDTH, HEIGHT,
                              0, vInfo->depth, InputOutput, vInfo->visual,
                              swaMask, &swa );

    winCtx = glXCreateNewContext(dpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, True);
    glxWin = glXCreateWindow(dpy, fbConfigs[0], xWin, NULL);
    XMapWindow(dpy, xWin);
    glXMakeContextCurrent(dpy, glxWin, glxWin, winCtx);
    program.init("./data/shaders/vertex330.shader", "./data/shaders/fragment330.shader");

    //BufferObject cube = initCube();
    vertex_line vert = initVertex();
    Texture texture("./data/textures/grap0.bmp");
    vert.gpupLine_lineTexture = texture.textureID;
    for(int i = 0; i < 1000; i++)
        renderVertex(vert, i);

    readBufferToFile("test_image_antialiased.bmp");
    glXMakeCurrent(dpy, None, NULL);
    glXDestroyContext(dpy, winCtx);
    XDestroyWindow(dpy, xWin);
    XCloseDisplay(dpy);
}

} // supertest
