#version 150

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;
in vec4 color;
in vec4 normal;

out vec2 varyingtexcoord;

void main() {
    gl_Position	= modelViewProjectionMatrix * position;
    //gl_FrontColor = gl_Color;
    varyingtexcoord = texcoord;
}