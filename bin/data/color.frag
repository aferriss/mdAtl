uniform sampler2DRect u_image;
varying vec2 v_texCoord;
uniform float time;
uniform vec2 canvas;
uniform vec2 mouse;
float speed = 5.0;
uniform float texelWidth;

vec3 rainbow(float h) {
    h = mod(mod(h, 1.0) + 1.0, 1.0);
    float h6 = h * 6.0;
    float r = clamp(h6 - 4.0, 0.0, 1.0) +
    clamp(2.0 - h6, 0.0, 1.0);
    float g = h6 < 2.0
    ? clamp(h6, 0.0, 1.0)
    : clamp(4.0 - h6, 0.0, 1.0);
    float b = h6 < 4.0
    ? clamp(h6 - 2.0, 0.0, 1.0)
    : clamp(6.0 - h6, 0.0, 1.0);
    return vec3(r, g, b);
}

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
    vec2 tc = v_texCoord.xy + vec2((0.2)*cos((time*0.0005)+5.0*v_texCoord.x*3.14159265359),0.0);
    
    vec4 input0 = texture2DRect(u_image,v_texCoord);
    vec4 orig = texture2DRect(u_image, v_texCoord);
    float co = cos(time*speed);
    float si = sin(time*speed);
    
    mat4 hueRotation =
    mat4(0.299,  0.587,  0.114, 0.0,
         0.299,  0.587,  0.114, 0.0,
         0.299,  0.587,  0.114, 0.0,
         0.000,  0.000,  0.000, 1.0) +
    
    mat4(0.701, -0.587, -0.114, 0.0,
         -0.299,  0.413, -0.114, 0.0,
         -0.300, -0.588,  0.886, 0.0,
         0.000,  0.000,  0.000, 0.0) * co +
    
    mat4(0.168,  0.330, -0.497, 0.0,
         -0.328,  0.035,  0.292, 0.0,
         1.250, -1.050, -0.203, 0.0,
         0.000,  0.000,  0.000, 0.0) * si;
    
    float step = 1.0;
    float tl = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2(-step, -step)).x);   // top left
    float  l = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2(-step,  0.0)).x);   // left
    float bl = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2(-step,  step)).x);   // bottom left
    float  t = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2( 0.0, -step)).x);   // top
    float  b = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2( 0.0,  step)).x);   // bottom
    float tr = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2( step, -step)).x);   // top right
    float  r = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2( step,  0.0)).x);   // right
    float br = abs(texture2DRect(u_image, v_texCoord + texelWidth * vec2( step,  step)).x);   // bottom right
    
    float mult = 1.0;
    
    float dX = tr*mult + 2.0*r*mult + br*mult -tl*mult - 2.0*l*mult - bl*mult;
    float dY = bl*mult + 2.0*b*mult + br*mult -tl*mult - 2.0*t*mult - tr*mult;
    
    vec3 color = normalize(vec3(dX,dY,1.0/1.0)); //the normal map
    //color *= 0.5;
    //color += 0.5;
    
    vec3 lightDir = vec3( vec2(0.5,0.5) - (gl_FragCoord.xy/vec2(canvas.x,canvas.y)) , 0.1 );
    //lightDir.g *= 10.5;
    //lightDir.r *= 3.5;
    
    float D = length(lightDir);
    vec3 N = normalize(color);
    vec3 L = normalize(lightDir);
    
    vec4 lightColor = vec4(0.0,0.0, 0.0,1.0);
    
    lightColor.rgb = rgb2hsv(lightColor.rgb)+rainbow(time*0.25);
    
    vec3 falloff = vec3(0.005,0.5,1.0);
    
    vec3 diffuse = (lightColor.rgb * lightColor.a) * max(dot(N, L), 0.0);
    
    
    float shin = 3.;
    float sf = max(dot(N,L),0.0);
    sf = pow(sf, shin);
    
    
    float attenuation = 1.0 / (falloff.x + (falloff.y*D) + (falloff.z * D * D) );
    
    vec3 col = (diffuse + sf)*attenuation;
    
    vec3 allOnes = vec3(1.0);
    
    vec3 finalColor = rgb2hsv(input0.rgb);
    //finalColor.r += 0.025;
    //finalColor.r = mod(finalColor.r, 1.0);
    //finalColor.g *= 1.1;
    //finalColor.g = normalize(finalColor.g);
    finalColor.b *= 0.99;
    //finalColor.b = mod(finalColor.b,1.0);
    vec3 b2rgb = hsv2rgb(finalColor);
    gl_FragColor =vec4(b2rgb,1.0) ;//+mix(vec4(col, 1.0),input0, 0.0);//*vec4(vec3(rainbow(time*10.0)),1.0);
}






