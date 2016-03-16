#version 150

uniform sampler2D baseMap;
uniform sampler2D angryTex;
uniform sampler2D noise;
uniform vec4 fogColor;
uniform float density;
uniform float time;
uniform float angryMix;
uniform float texScale;

uniform float fadeToBlack;
uniform float fadeInColor;
//in float fogFactor;
in vec2 varyingtexcoord;
//in vec4 gl_FragCoord;
in vec4 col;
in float depth;

out vec4 outputcolor;

in vec3 N;
in vec3 V;
in float avgLuma;


in float fogAmt;

float fogFactorExp2( const float dist, const float dens) {
    const float LOG2 = -1.442695;
    float d = dens * dist;
    return 1.0 - clamp(exp2(d * d * LOG2), 0.0, 1.0);
}


float fog_linear(
                 const float dist,
                 const float start,
                 const float end
                 ) {
    return 1.0 - clamp((end - dist) / (end - start), 0.0, 1.0);
}



void main( void ){
    vec4 baseColor = texture( baseMap, varyingtexcoord );
    vec4 angryColor = texture( angryTex, varyingtexcoord);
    
    //baseColor += angryColor;
    //baseColor /= 2.0;
    
    float al = avgLuma;
    al = fog_linear(20.0, 0.0,1.0);
    
    //baseColor = angryColor*al;//vec4(vec3(al), 1.0);
    
    vec4 noiseTex = texture(noise, varyingtexcoord*10.0);
    
    vec4 b = baseColor;
    //b.rgb += noiseTex.rgb;
    //baseColor.rgb = mix(baseColor.rgb, angryColor.rgb, 1.0-angryMix);
    
    //baseColor.rgb += angryColor.rgb;
    //baseColor.rgb /= 2.0;
    //baseColor.rgb *= noiseTex.rgb;
    
    //baseColor.rgb *=0.5;
    //baseColor.rgb += b.rgb;
    /*

    vec3 norm = normalize(V*N.xyz);
    vec4 finalColor = vec4(0.0);
    
    
    vec3 cameraSpacePos = vec3(0.0);
    vec3 eyeDirection = normalize(cameraSpacePos - V);
    vec3 lightDirection = normalize(vec3(0.0) - V);
    //float distanceFromLight = length(vec3(0.0) - newP.xyz);
    float intensity = max(dot(N, lightDirection), 0.0);
    vec3 halfVector = normalize(cameraSpacePos - vec3(0.0));
    
    vec4 lightColor = baseColor;
    vec3 diffuse = lightColor.rgb * intensity;
    float shin = 300.0;
    float sf = max(0.0, dot(N, normalize(lightDirection)));
    sf = pow(sf, shin);
    
    diffuse + sf;
    
    finalColor.rgb = diffuse + sf; + baseColor.rgb;
    finalColor.a = 1.0;
    */
    
    /*
    vec3 L = normalize(vec3(0.0,0.0,0.0) - V);
    vec3 E = normalize(-V);
    vec3 R = normalize(-reflect(L, norm));
    
    
    vec4 amb = baseColor;
    vec4 diff = baseColor* max(dot(norm, L), 0.0);
    diff = clamp(diff, 0.0, 1.0);
    
    float spec =  pow(max(dot(R, E), 0.0), 300.0);
    spec = clamp(spec, 0.0, 1.0);
    */
    
    //finalColor += amb + diff + vec4(vec3(spec),0.0);
    //float avg = dot(baseColor.rgb, vec3(1.0))/3.0;
    
    //float d = depth;//mix(0.0, 1.0, depth);
    //baseColor.rgb *= 1.0-avg;
    
    //float fogDistance = ( gl_FragCoord.z  / gl_FragCoord.w )*1000.0;/// 500.01;
    //float fogAmount = fogFactorExp2(-fogDistance, 1000.0001);
    
    //float avg = dot(finalColor.rgb, vec3(1.0))/3.0;
    
    //finalColor = avg < 0.02 ? vec4(1.0, 0.5, 0.8,1.0) : finalColor;
    
    outputcolor =   mix(vec4(1., 1., 1., 1.0), baseColor*fadeInColor, 0.5 );
    //outputcolor =   mix(vec4(1., 1., 1., 1.0)*fadeToBlack, baseColor*fadeInColor, fogAmt );
    outputcolor = baseColor;
    outputcolor.a = 1.0;
    //outputcolor = vec4(1.0 - gl_FragCoord.z/gl_FragCoord.w / 1280.0, 0.0, 0.0, 1.0);
}




