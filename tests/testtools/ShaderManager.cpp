#include "ShaderManager.h"

#include <iostream>
#include <string>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <gtc/type_ptr.hpp>

namespace opengl
{

using namespace std;

ShaderManager::ShaderManager()
    : initialised(false)
{
}

ShaderManager::~ShaderManager()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteShader(m_vs);
    glDeleteShader(m_fs);
    glDeleteProgram(id);
}

ShaderManager::ShaderManager(string vertex, string fragment)
{
    init(vertex, fragment);
}

void ShaderManager::init(string vertex, string fragment)
{
    if (!initialised)
    {
        id = glCreateProgram();
        m_vs = compileFromSourceAndAttach(vertex, GL_VERTEX_SHADER);
        m_fs = compileFromSourceAndAttach(fragment, GL_FRAGMENT_SHADER);
        linkProgram();
        activateUniforms();
        activateAttributes();
        glClear(GL_COLOR_BUFFER_BIT);
        glDepthMask(true);
        glFrontFace(GL_CCW);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_STENCIL_TEST);
        glEnable(GL_DITHER);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        initialised = true;
    }
}

char* parseFile(ifstream& file)
{
    string src = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    char *shaderSrc = new char[src.size()+1];
    shaderSrc[src.size()]=0;
    memcpy(shaderSrc, src.c_str(), src.size());
    return shaderSrc;
}

void ShaderManager::activateUniforms() {
    GLint infoLen = -1;
    GLint strLen = -1;
    glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &infoLen);
    glGetProgramiv(id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &strLen);
    char* nameBuffer = new char[strLen];
    int* sizeBuffer = new int[1];
    unsigned int* typeBuffer = new unsigned int[1];
    int* nameLenBuffer = new int[1];
    for (int i = 0; i < infoLen; i++) {
        glGetActiveUniform(id, i, strLen, nameLenBuffer, sizeBuffer, typeBuffer, nameBuffer);
        glBindAttribLocation(id, i, nameBuffer);
    }
}

void ShaderManager::activateAttributes() {
    GLint count = 0;
    GLint strLen = 0;
    glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &count);
    glGetProgramiv(id, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &strLen);
    char* nameBuffer = new char[strLen];
    int* sizeBuffer = new int[1];
    unsigned int* typeBuffer = new unsigned int[1];
    int* nameLenBuffer = new int[1];
    for (int i = 0; i < count; i++) {
        glGetActiveAttrib(id, i, strLen, nameLenBuffer, sizeBuffer, typeBuffer, nameBuffer);
        glBindAttribLocation(id, i, nameBuffer);
    }
}

GLint ShaderManager::compileFromSourceAndAttach(string shader_name, int type)
{
    ifstream inputStream(shader_name);

    if(!inputStream.is_open())
    {
        throw "Error opening shader file " + shader_name;
    }

    GLchar* shaderSrc = parseFile(inputStream);

    cout << "Complinig shader " << shader_name << " ... " << endl;

    GLint shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &shaderSrc, NULL);
    glCompileShader(shaderId);

    GLint compiled = GL_FALSE;
    GLint info = 0;

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &info);
    if( compiled != GL_TRUE || info > 1 )
    {
        char* infoLog = (char*)malloc(sizeof(char) * info);
        glGetShaderInfoLog(shaderId, info, NULL, infoLog);
        cerr <<  "Error compiling shader: " << infoLog << endl;
        free(infoLog);
        glDeleteShader(shaderId);
        throw "Error compiling shader";
    }

    glAttachShader(id, shaderId);
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &info);
    if (info > 1)
    {
        char* infoLog = (char*) malloc (sizeof (char) * info);
        glGetProgramInfoLog (id, info, NULL, infoLog);
        cerr << "Error linking program: " << infoLog << endl;
        free (infoLog);
    }

    cout << "Successfully compiled and linked " << shader_name << endl;
    inputStream.close();

    return shaderId;
}


void ShaderManager::linkProgram()
{
    GLint status = GL_FALSE;
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
    {
        GLint logLength = 1;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        char* infoLog = (char*)malloc(logLength+1);
        glGetProgramInfoLog(id, logLength, &logLength, infoLog);
        cerr << "Failed to link the shader: " << infoLog;
        free(infoLog);
    }

    glValidateProgram(id);
    glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
    if (status != GL_TRUE) {
        cerr << "Shader program will not run in this OpenGL environment!" << endl;
    }
}

GLint ShaderManager::getAttribute(char* name){
    GLint maPositionHandle = glGetAttribLocation(id, name);
    if (maPositionHandle == -1) {
        cerr << "Could not get attrib location for " << name << endl;
    } else
        return maPositionHandle;
}

GLint ShaderManager::getUniform(char* name){
    GLint maPositionHandle = glGetUniformLocation(id, name);
    if (maPositionHandle == -1) {
        cerr << "Could not get uniform location for " << name << endl;
    } else
        return maPositionHandle;
}


void ShaderManager::setMatrixUniform(char* name, mat4 matrix){
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, value_ptr(matrix));
}

void ShaderManager::setUniform1i(char* name, bool val){
    glUniform1i(getUniform(name), (val == true) ? 1 : 0);
}

void ShaderManager::setUniform1i(char* name, int val){
    glUniform1i(getUniform(name), val);
}

void ShaderManager::setUniform1f(char* name, float val){
    glUniform1f(getUniform(name), val);
}

void ShaderManager::setAttributePointer(char* name, GLint elemPerVertex, GLsizei size, GLint offset)
{
    glVertexAttribPointer(
        getAttribute(name),
        elemPerVertex,
        GL_FLOAT,
        GL_FALSE,
        size,
        ((char *)NULL + offset)
    );
}

}
