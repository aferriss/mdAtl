#version 150

/*
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;
in vec4 color;
in vec4 normal;

out vec2 varyingtexcoord;


void main()
{
    varyingtexcoord = texcoord;
    gl_Position	= modelViewProjectionMatrix * position;
}
*/


uniform vec2 repeat;
uniform float useNormal;
uniform float useRim;

uniform vec3 firstRow;              // Prima riga normalMatrix
uniform vec3 secondRow;             // Seconda riga normalMatrix
uniform vec3 thirdRow;              // Terza riga normalMatrix

varying vec2 vUv;
varying vec3 vTangent;
varying vec3 vBinormal;
varying vec3 vNormal;
varying vec3 vEye;
varying vec3 vU;
varying vec2 vN;

vec3 tangent;

out varyingtexcoord;

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 texcoord;
in vec4 color;
in vec4 normal;

mat3 getNormalMatrix(mat3 normalMat);

void main() {
    vec3 c1 = cross(normal.rgb, vec3(0.0, 0.0, 1.0));
    vec3 c2 = cross(normal.rgb, vec3(0.0, 1.0, 0.0));

    if (length(c1)>length(c2))
    {
        tangent = c1;
    }
    else
    {
        tangent = c2;
    }

    tangent = normalize(tangent);
    

    vec4 p = vec4(position, 1.0);
    vU = normalize( vec3( modelViewMatrix * p ) );

    if( useNormal == 0. ) {
        vec3 n = normalize( normalMatrix * normal );

        vec3 r = reflect( vU, n );
        float m = 2. * sqrt( 
            pow( r.x, 2. ) + 
            pow( r.y, 2. ) + 
            pow( r.z + 1., 2. ) 
        );
        vN = r.xy / m + .5;
    } else {
        vN = vec2( 0. );
    }

    vUv = repeat * uv;
    

    vNormal = normalize( normalMatrix * normal );

    if( useNormal == 1. ) {
        vTangent = normalize( normalMatrix * tangent.xyz );
        vBinormal = normalize( cross( vNormal, vTangent ) * tangent.w );
    } else {
        vTangent = vec3( 0. );
        vBinormal = vec3( 0. );
    }

    if( useRim > 0. ) {
        vEye = ( modelViewMatrix * vec4( position, 1.0 ) ).xyz;
    } else {
        vEye = vec3( 0. );
    }

    gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
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


