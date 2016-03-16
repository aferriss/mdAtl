#version 150

uniform sampler2D src_tex_unit0;
uniform float imgWidth;
uniform float imgHeight;

float kernel[9];
vec2 offset[9];

uniform float step_w ;
uniform float step_h ;
uniform float texelWidth;
uniform float angry;
in vec2 varyingtexcoord;
out vec4 outputcolor;


vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));
    
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(( (q.z + (q.w - q.y) / (6.0 * d + e))) ), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main() {
    
    
    vec2 tc = varyingtexcoord;
    vec2 v_texCoord = tc;
    vec4 input0 = texture(src_tex_unit0,tc);
    
    
    vec2 x1 = vec2(1.0/imgWidth * 0.0028, 0.0);
    vec2 y1 = vec2(0.0, 1.0/imgHeight * 0.0028);
    
    /*
    input0 += texture(src_tex_unit0, tc+x1); // right
    input0 += texture(src_tex_unit0, tc-x1); // left
    input0 += texture(src_tex_unit0, tc+y1); // top
    input0 += texture(src_tex_unit0, tc-y1); // bottom
    
    input0*= vec4(0.2);
    */
    
    offset[0] = vec2(-step_w, -step_h);
    offset[1] = vec2(0.0, -step_h);
    offset[2] = vec2(step_w, -step_h);
    offset[3] = vec2(-step_w, 0.0);
    offset[4] = vec2(0.0, 0.0);
    offset[5] = vec2(step_w, 0.0);
    offset[6] = vec2(-step_w, step_h);
    offset[7] = vec2(0.0, step_h);
    offset[8] = vec2(step_w, step_h);
    
    kernel[0] =  0.001; kernel[1] =  0.00;  kernel[2] = 0.0;
    kernel[3] =  0.023; kernel[4] =  0.025; kernel[5] = -0.05;
    kernel[6] =  0.001; kernel[7] =  0.00; kernel[8] = 0.0;
    
    vec4 sum = input0;

    int i;
    
    for (i = 0; i < 9; i++) {
        vec4 color = texture(src_tex_unit0, tc + offset[i]);
        sum += color * kernel[i];
    }
    
    vec3 rgb = sum.rgb;
    float g = rgb.g;
    
    vec3 rgbMod = vec3(0.000125,0.000225,0.000325) ;
    vec3 angryRgb = rgb;
    angryRgb.r += rgbMod.r;
    angryRgb.g += rgbMod.g;
    angryRgb.b += rgbMod.b;
    
    angryRgb =  mod(angryRgb, vec3(1.0));
//
//    rgb.r += (g*0.001);
//    rgb.g += (g*0.001);
//    rgb.b += (g*0.001);
    
    vec4 final = vec4(sum.rgb, 1.0) ;
    
    rgb = mix(rgb, angryRgb, angry);
    
    outputcolor.rgb = rgb ;
    outputcolor.a = 1.0;

}