#version 150

uniform sampler2D s_texture;

in vec2 v_blurTexCoords[14];

in vec2 varyingtexcoord;

out vec4 outputcolor;

void main()
{
    outputcolor = vec4(0.0);
    outputcolor += texture(s_texture, v_blurTexCoords[ 0])*0.0044299121055113265;
    outputcolor += texture(s_texture, v_blurTexCoords[ 1])*0.00895781211794;
    outputcolor += texture(s_texture, v_blurTexCoords[ 2])*0.0215963866053;
    outputcolor += texture(s_texture, v_blurTexCoords[ 3])*0.0443683338718;
    outputcolor += texture(s_texture, v_blurTexCoords[ 4])*0.0776744219933;
    outputcolor += texture(s_texture, v_blurTexCoords[ 5])*0.115876621105;
    outputcolor += texture(s_texture, v_blurTexCoords[ 6])*0.147308056121;
    outputcolor += texture(s_texture, varyingtexcoord  )*0.159576912161;
    outputcolor += texture(s_texture, v_blurTexCoords[ 7])*0.147308056121;
    outputcolor += texture(s_texture, v_blurTexCoords[ 8])*0.115876621105;
    outputcolor += texture(s_texture, v_blurTexCoords[ 9])*0.0776744219933;
    outputcolor += texture(s_texture, v_blurTexCoords[10])*0.0443683338718;
    outputcolor += texture(s_texture, v_blurTexCoords[11])*0.0215963866053;
    outputcolor += texture(s_texture, v_blurTexCoords[12])*0.00895781211794;
    outputcolor += texture(s_texture, v_blurTexCoords[13])*0.0044299121055113265;
}