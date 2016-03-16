uniform sampler2DRect src_tex_unit0;

void main(){
    vec2 tc = gl_TexCoord[0].st;
    vec2 v_texCoord = tc;
    vec4 input0 = texture2DRect(src_tex_unit0,tc);
    
    vec2 x1 = vec2(1.55, 0.0);
    vec2 y1 = vec2(0.0, 1.55);
    
    input0 += texture2DRect(src_tex_unit0, tc+x1); // right
    input0 += texture2DRect(src_tex_unit0, tc-x1); // left
    input0 += texture2DRect(src_tex_unit0, tc+y1); // top
    input0 += texture2DRect(src_tex_unit0, tc-y1); // bottom
    
    input0*= vec4(0.2);

    gl_FragColor = input0;
}