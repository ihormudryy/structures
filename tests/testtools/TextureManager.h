
#ifdef __linux__

#ifndef TEXTURE_H
#define TEXTURE_H
#endif

#include <glm/glm.hpp>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glx.h>

namespace opengl
{

class Texture
{

public:
    Texture(){};
    Texture(char* path, GLuint mipmapLevels = 4);
    ~Texture();
    GLuint textureID;
    GLuint numberOfMipMapLevels;
};

}

#endif // LINUX
