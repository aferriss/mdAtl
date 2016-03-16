//setup for 2 texture
varying vec2 texcoord0;
varying vec2 texcoord1;
//varying vec2 texdim0;
//varying vec2 texdim1;
uniform vec2 amt;
//uniform vec4 scale;
//uniform vec4 bias;
//uniform vec2 boundmode;
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;


void main()
{
    vec2 scale = vec2(1.0,1.0);
    vec2 bias = vec2(1.0,1.0);
    
    vec4 look = texture2DRect(tex1,texcoord1);//sample repos texture
    vec2 offs = vec2(look.x-look.y,look.w+look.z)*amt;
    vec2 coord = offs+texcoord0;	//relative coordinates
    //coord = mod(coord,texdim0);
    
    //vec2 centre = vec2((1.0-(1.0/scale))/2.0, (1.0-(1.0/scale))/2.0);
    //vec2 center = vec2( (1.0-(1.0/scale.x) )/2.0,  (1.0-(1.0/scale.y))/2.0 );
    vec4 repos = texture2DRect(tex0,coord);
    
    // output texture
    gl_FragColor = repos;//*scale+bias;
    
    
    //gl_FragColor = texture2DRect(tex0,(coord *scale)+center);
    
}