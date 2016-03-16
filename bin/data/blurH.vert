#version 150

out vec2 v_blurTexCoords[14];

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;
in vec4 color;
in vec4 normal;

out vec2 varyingtexcoord;

void main()
{
    gl_Position	= modelViewProjectionMatrix * position;
    varyingtexcoord = texcoord;
    
    v_blurTexCoords[ 0] = varyingtexcoord + vec2(-3.0/1024.0, 0.0);
    v_blurTexCoords[ 1] = varyingtexcoord + vec2(-2.5/1024.0, 0.0);
    v_blurTexCoords[ 2] = varyingtexcoord + vec2(-2.0/1024.0, 0.0);
    v_blurTexCoords[ 3] = varyingtexcoord + vec2(-1.5/1024.0, 0.0);
    v_blurTexCoords[ 4] = varyingtexcoord + vec2(-1.0/1024.0, 0.0);
    v_blurTexCoords[ 5] = varyingtexcoord + vec2(-0.5/1024.0, 0.0);
    v_blurTexCoords[ 6] = varyingtexcoord + vec2(-0.1/1024.0, 0.0);
    v_blurTexCoords[ 7] = varyingtexcoord + vec2( 0.1/1024.0, 0.0);
    v_blurTexCoords[ 8] = varyingtexcoord + vec2( 0.5/1024.0, 0.0);
    v_blurTexCoords[ 9] = varyingtexcoord + vec2( 1.0/1024.0, 0.0);
    v_blurTexCoords[10] = varyingtexcoord + vec2( 1.5/1024.0, 0.0);
    v_blurTexCoords[11] = varyingtexcoord + vec2( 2.0/1024.0, 0.0);
    v_blurTexCoords[12] = varyingtexcoord + vec2( 2.5/1024.0, 0.0);
    v_blurTexCoords[13] = varyingtexcoord + vec2( 3.0/1024.0, 0.0);
}