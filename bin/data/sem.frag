#version 150

uniform sampler2D u_image;
//uniform sampler2DRect src_tex_unit1;
//uniform sampler2DRect src_tex_unit2;
//varying vec3 h;

out vec4 outputColor;
in vec2 varyingtexcoord;

void main(){
    //vec2 tc = gl_TexCoord[0].st;
    //vec2 v_texCoord = tc;
    vec4 input0 = texture(u_image,varyingtexcoord);
    //vec4 input1 = texture2DRect(src_tex_unit1,tc);
    //vec4 input2 = texture2DRect(src_tex_unit2,tc);
    //vec4 diff = input1 - input0;
    //vec4 fc = diff*1.0 + input2;
    //gl_FragColor = input0*normalize(h.z);
    outputColor = input0;
}