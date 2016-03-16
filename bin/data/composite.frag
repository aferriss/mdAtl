#version 150

uniform sampler2D bumpTex;
uniform sampler2D edgeTex;
uniform sampler2D blurTex;

//uniform sampler2DRect src_tex_unit1;
//uniform sampler2DRect src_tex_unit2;
//varying vec3 h;

out vec4 outputColor;
in vec2 varyingtexcoord;

void main(){
    //vec2 tc = gl_TexCoord[0].st;
    //vec2 v_texCoord = tc;
    vec4 bump = texture(bumpTex,varyingtexcoord);
    vec4 edge = texture(edgeTex, varyingtexcoord);
    vec4 blur = texture(blurTex, varyingtexcoord);
    
    float avg = dot(edge.rgb, vec3(1.0))/3.0;
    //edge *= 50.0;
    vec3 mask = step(0.1, edge.rgb);
    vec4 fc;
    
    
    edge *= blur;
    /*
    if(avg > 0.01){
    
        //edge *= 2.0;
    fc = edge +bump;
    } else{
        fc = bump;
    }
    */
    
    fc = mix(bump, blur, edge.r+0.3);
    
    outputColor = fc;
    
    //vec4 input1 = texture2DRect(src_tex_unit1,tc);
    //vec4 input2 = texture2DRect(src_tex_unit2,tc);
    //vec4 diff = input1 - input0;
    //vec4 fc = diff*1.0 + input2;
    //gl_FragColor = input0*normalize(h.z);
    
    
}