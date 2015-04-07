#version 120
attribute vec3 aVertexPosition;
attribute vec3 aNormals;
attribute vec2 aTextureUv;
uniform mat4 uMVP;
varying vec2 uvTexture;
varying vec3 vNormals;
void main(void)
{
    gl_Position = uMVP*vec4(aVertexPosition, 1.0);
    uvTexture = aTextureUv.xy;
}