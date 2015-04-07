#version 120
uniform sampler2D textureMap;
varying vec2 uvTexture;
varying vec3 vNormals;
void main(void)
{
    gl_FragColor = texture2D(textureMap, uvTexture);
}