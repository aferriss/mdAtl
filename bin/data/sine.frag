uniform sampler2DRect src_tex_unit0;
uniform float imgWidth;
uniform float imgHeight;
uniform float time;
uniform float freq1;
uniform float freq2;
uniform float amp1;
uniform float amp2;
uniform float steps;

vec2 checkerboard(vec2 p, float steps) {
    float x = floor(p.x * steps);
    float y = floor(p.y * steps);
    return vec2(x,y);//mod(x + y, 2.);
}

void main() {
    
    vec2 pos = gl_TexCoord[0].st;
    
    vec2 tc = pos;//checkerboard(pos, steps);//gl_TexCoord[0].st;
    vec4 input0 = texture2DRect(src_tex_unit0,tc + vec2(sin(time+tc.x*freq1)*amp1,0.0)) /*+ vec2(0.0,sin(time*1.5+tc.x*freq1)*amp1))*/;
    
    
    gl_FragColor = input0;
    //gl_FragColor =  texture2DRect(src_tex_unit0, gl_TexCoord[0].st);
}