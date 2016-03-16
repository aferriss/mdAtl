#version 150

uniform sampler2D u_image;
uniform sampler2D bump2;

uniform vec2 res;
uniform float time;
uniform float colorMix;
uniform float fadeToBlack;
uniform float fadeInColor;
uniform float hueCycle;
uniform float colorSlider;

out vec4 outputColor;
in vec2 varyingtexcoord;

uniform float fogOsc;


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


vec3 makeNormalMap( sampler2D u){
    vec2 step = res*10.15;
    vec2 texelWidth = res*10.15;
    vec2 tc = varyingtexcoord;
    
    //vec4 input0 = texture(u_image,tc);
    float tl = abs(texture(u, tc + texelWidth * vec2(-step.x, -step.y)).x);   // top left
    float  l = abs(texture(u, tc + texelWidth * vec2(-step.x,  0.0)).x);   // left
    float bl = abs(texture(u, tc + texelWidth * vec2(-step.x,  step.y)).x);   // bottom left
    float  t = abs(texture(u, tc + texelWidth * vec2( 0.0, -step.y)).x);   // top
    float  b = abs(texture(u, tc + texelWidth * vec2( 0.0,  step.y)).x);   // bottom
    float tr = abs(texture(u, tc + texelWidth * vec2( step.x, -step.y)).x);   // top right
    float  r = abs(texture(u, tc + texelWidth * vec2( step.x,  0.0)).x);   // right
    float br = abs(texture(u, tc + texelWidth * vec2( step.x,  step.y)).x);   // bottom right

    float mult = 0.045;

    float blur = (tl+l+bl+t+b+tr+r+br)/8.0;
    
    float dX = (tr*mult + 2.0*r*mult + br*mult -tl*mult - 2.0*l*mult - bl*mult);//*blur;
    float dY = (bl*mult + 2.0*b*mult + br*mult -tl*mult - 2.0*t*mult - tr*mult);//*blur;
    
    
    
    vec3 normalMap = normalize(vec3(dX, dY, 1.0/500.0));
    normalMap *= 0.5;
    normalMap += 0.5;
    
    return vec3(normalMap);
    
    

}

void main(){
    
    vec3 nM = makeNormalMap(u_image);
    //vec3 bM = makeNormalMap(bump2);
    vec2 tc = varyingtexcoord;
    
    vec4 diffuseColor = texture(u_image, tc);
    float dAvg = dot(diffuseColor.rgb, vec3(1.0))/3.0;
    
    vec3 lightDirection = vec3( vec2(0.5)  , 0.025);
    lightDirection.x *= res.x/res.y;
    
    float D = length(lightDirection);
    
    vec3 N = normalize(nM);
    vec3 L = normalize(lightDirection);
    vec3 H = normalize(L);
    
    //vec4 lightColor = vec4(0.5,0.5,0.5,1.0);//diffuseColor;
    vec4 lightColor = diffuseColor;
    vec4 ambientColor = vec4(diffuseColor.rgb, 0.5);
    
    vec3 falloff = vec3(0.01, 3.1, 20.5);
    
    vec3 diffuse = lightColor.rgb * max(dot(N, L), 0.0);
    vec3 ambient = ambientColor.rgb * ambientColor.a;
    
    float shin = 200.0;
    float sf = max(0.0, dot(N, H));
    sf = pow(sf, shin);
    
    float attenuation = 1.0 / (falloff.x + (falloff.y *D) + (falloff.z * D * D) );
    vec3 intensity = ambient + (diffuse + sf) ;//* attenuation;
    vec3 finalColor = (diffuse.rgb * intensity);
    vec3 col = ambient + finalColor + sf*0.95;
    
    float  avg = dot(col.rgb, vec3(1.0))/3.0;
    
    //vec4 fc = mix(vec4(vec3(1.15), 2.0) - vec4(vec3(avg+0.05, avg+0.05, avg) + (col.rgb*0.00004), 1.0), vec4(vec3(avg, avg, avg+0.1) + (col.rgb*0.00005), 1.0) - vec4(vec3(0.5),0.0), mix(0.0,0.8,(sin(time*0.1)+1.0)/2.0));
    
    vec4 fc = mix( vec4( vec3(0.85), 2.0) -  vec4(vec3(avg+colorSlider, avg+colorSlider, avg) + (col.rgb*0.065), 1.0), // darks
                   vec4(vec3(avg+0.1, avg+0.2, avg+0.3) + (col.rgb*0.065), 1.0) - vec4(vec3(0.75),0.0),  //lights
                   mix(0.8,0.0,fogOsc));  // alpha
    
    
    
    /*
    vec4 fc = mix( vec4( vec3(0.85), 2.0) -  vec4(vec3(avg+0.05, avg+0.05, avg) + (col.rgb*0.065), 1.0), // darks
                  vec4(vec3(avg, avg, avg+0.1) + (col.rgb*0.065), 1.0) - vec4(vec3(0.75),0.0),  //lights
                  mix(0.8,0.0,fogOsc));  // alpha
    */
    
    //vec4 fc = mix(vec4(vec3(avg, avg, avg+0.1) + (col.rgb*0.00005), 1.0) - vec4(vec3(0.5),0.0),vec4(vec3(1.15), 2.0) - vec4(vec3(avg+0.05, avg+0.05, avg) + (col.rgb*0.00004), 1.0), mix(0.0,0.8,(sin(time*1.1)+1.0)/2.0));
    
    //vec4 fc = vec4(vec3(1.15), 2.0) - vec4(vec3(avg+0.05, avg+0.05, avg) + (col.rgb*0.00004), 1.0);
    
    //vec4 fc = mix(vec4(vec3(avg+0.05, avg+0.05, avg) + (col.rgb*0.04), 1.0), vec4(vec3(avg, avg, avg+0.1) + (col.rgb*0.015), 1.0) - vec4(vec3(0.5),0.0), mix(0.0,0.8,(sin(time*0.1)+1.0)/2.0));
    
    fc.rgb *= 3.0;
    
    
    vec3 finalMix = mix(fc.rgb, fc.rgb+(col.rgb*0.1), colorMix);
    finalMix.r = mix(finalMix.r, finalMix.r + 0.3, colorMix);
    finalMix.g = mix(finalMix.g, finalMix.g + 0.1, colorMix);
    
    finalMix.rgb = mix(finalMix.rgb, clamp(finalMix.rgb+0.1, 0.0,1.0), colorMix);
    
    vec3 hsv = rgb2hsv(finalMix);
    
    //hsv.r += hueCycle;
    //hsv.r = mod(hsv.r, 1.0);
    
    hsv.g *= 0.5;
    hsv.g = clamp(hsv.g, 0.0,1.0);
    //hsv.b*= 1.5;
    //hsv.b = clamp(hsv.b, 0.0,1.0);
    vec3 rgb = hsv2rgb(hsv);
    
    finalMix = mix(finalMix, rgb, colorMix);
    
    //finalMix *= finalMix+0.01;
    
    //fc.g *= 1.1;
    outputColor = vec4(finalMix, 1.0);// vec4(vec3(avg+0.05, avg+0.05, avg) + (col.rgb*0.01), 1.0);
    //outputColor = vec4(col.rgb, 1.0);
    //outputColor = vec4(nM, 1.0);
}