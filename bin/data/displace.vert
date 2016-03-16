#version 150

uniform sampler2D u_image;
uniform sampler2D angryTex;
uniform float time;
uniform vec2 res;
uniform float angryMix;
uniform float dispAmt;
uniform float uFogDist;
uniform float beat;
uniform float increaseDisp;
uniform vec3 firstRow;              // Prima riga normalMatrix
uniform vec3 secondRow;             // Seconda riga normalMatrix
uniform vec3 thirdRow;              // Terza riga normalMatrix
uniform float texScale;
uniform float zScale;
uniform float mouseX;
//uniform float spikyMix;
uniform float texDirection;

//out vec3 h;


uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;
in vec4 color;
in vec3 normal;

out vec2 varyingtexcoord;
out float avgLuma;
out vec3 N;
out vec3 V;
out float depth;

float fog_linear(
                      const float dist,
                      const float start,
                      const float end
                      ) {
    return 1.0 - clamp((end - dist) / (end - start), 0.0, 1.0);
}

out float fogAmt;

mat3 getNormalMatrix(mat3 normalMat);

void main() {

    vec3 vn = normalize(normal.xyz);
    
    varyingtexcoord = texcoord;
    
    varyingtexcoord.y = texDirection == 1.0 ? varyingtexcoord.y : 1.0 - varyingtexcoord.y;
    
    vec4 angry = texture(angryTex, varyingtexcoord );
    
    vec4 tex = texture(u_image, varyingtexcoord );

    
    
    
    float avg = dot(tex.rgb, vec3(1.0))/3.0;
    //float avg = tex.r;
    
    float angryAvg = dot( (angry.rgb + tex.rgb)*0.5, vec3(1.0))/3.0;
    //float angryAvg = ( angry.g + tex.g ) * 0.5;
    //avg -=0.75;
    //avg += angryAvg;
    //avg /= 2.0;
    
    avg = mix(avg, avg*angryAvg, angryMix);
    
    avg += (angryAvg * (angryMix*0.5));
    
    avg = avg*avg*(dispAmt*beat);
    avg *= (dispAmt*beat);
    
    
    avgLuma = avg;
    
    
//    float spiky = pow(dot(angry.rgb, vec3(1.0))/3.0, 20.0)*2.0;
    
//    avg = mix(avg, avg*1.35+spiky, spikyMix);
    
   //avg = avg > 0.5 ? avg : 0.0;
    //vec4 pos;
    
    //pos = vec4(position.x, position.y, position.z, 1.0) + vec4(vec3(vn.rgb * -(avg*1600.0-800.0)),0.0);
    vec4 vert = modelViewMatrix * position;
    
    float zOff = -vert.z*-vert.z;
    
    vert+=zOff;
    
    
    vec4 newP = position;
    
    //newP.z += sin(newP.x*0.00025)*3000.0;
    //newP.z += zOff;
    
    float x = abs(cos(varyingtexcoord.x*3.0+1.6)*4000.0) ;
    float y = abs(sin(varyingtexcoord.y*3.0+3.18)*4000.0) ;
    
    x = mix(0.0,1.0,x);
    y = mix(0.0,1.0,y);
    //x = clamp(x, 0.0,1000.0);
    float distanceFromCenter = distance(vec2(0.5),varyingtexcoord.xy );
    distanceFromCenter = smoothstep(0.0,0.7,distanceFromCenter);
    distanceFromCenter = 0.0;
    //vec4 distortion = vec4(vec3((vn.xyz) * (avg*500.0)),0.0);
    //vec4 distortion = vec4( vec3(vn.xyz) * ( y + x )*4.0, 0.0);
    //distanceFromCenter = distanceFromCenter > 0.5 ? 1.0 : distanceFromCenter;
    
    vec4 distortion = vec4( vec3(vn.xyz) * ( (-distanceFromCenter*1500.0) + (avg*(100.0+increaseDisp*2) - avg*(50.0+increaseDisp))), 0.0);
    
    
    //distortion += -avg*100.25;
    newP.xyz += distortion.xyz;
    
    //newP.xy *= texScale;

    //newP.z *= zScale;
    
    mat3 normalM;
    normalM = getNormalMatrix(normalM);
    
    V = vec3(modelViewMatrix * newP);
    N = normalize( normalM * normal);
    
    

    gl_Position = modelViewProjectionMatrix * newP;
    
    depth = newP.z;
    
//    float fogDistance = length(gl_Position.xyz);
//    float fogTime = (sin(time*0.25)/2.0+1.0)*10000.0;
    //fogAmt = 1.0 - fog_linear(fogDistance, 0.0, fogTime);
    ///fogAmt = 1.0 - fog_linear(fogDistance, 0.0, 20000.0+time*1000.0);
    fogAmt = 1.0;// - fog_linear(fogDistance, 0.0, uFogDist);
    
}




mat3 getNormalMatrix(mat3 normalMat)
{
    normalMat[0][0] = firstRow.x;
    normalMat[0][1] = firstRow.y;
    normalMat[0][2] = firstRow.z;
    
    normalMat[1][0] = secondRow.x;
    normalMat[1][1] = secondRow.y;
    normalMat[1][2] = secondRow.z;
    
    normalMat[2][0] = thirdRow.x;
    normalMat[2][1] = thirdRow.y;
    normalMat[2][2] = thirdRow.z;
    
    return normalMat; 
}