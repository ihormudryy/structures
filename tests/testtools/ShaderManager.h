#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#ifdef __linux__

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#endif

#include <glm.hpp>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>

namespace opengl
{

using namespace glm;

class ShaderManager
{
public:
    ShaderManager();
    ShaderManager(std::string, std::string);
    ~ShaderManager();
    void linkProgram();
    void init(std::string, std::string);
    void setMatrixUniform(char*, mat4);
    void setAttributePointer(char*, GLint = 3, GLsizei = 0, GLint = 0);
    void setUniform1i(char*, bool);
    void setUniform1i(char*, int);
    void setUniform1f(char*, float);
    GLint getAttribute(char*);
    GLint getUniform(char*);
    int id;

protected:
    GLint compileFromSourceAndAttach(std::string, int);
    void activateUniforms();
    void activateAttributes();
    bool initialised;

private:
    GLint m_vs;
    GLint m_fs;
};

}
#endif // Linux
