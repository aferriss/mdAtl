#version 150


uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;
out vec4 col;

//in vec4 color;
//in vec3 normal;
//in float density;
//out float depth;

out vec2 varyingtexcoord;
//out float fogFactor;




void main( void ){
    //vec4 vVertex = modelViewMatrix * position;
    
    // Transform vertex to view-space
    //const float LOG2 = 1.442695;
    
	//float fogFragCoord = length(vVertex);
    
    /*
	fogFactor = exp2( -density *
					   density *
					   fogFragCoord *
					   fogFragCoord *
					   LOG2 );
	fogFactor = clamp(fogFactor, 0.0, 1.0);
     */
    //vVertex.xy /= vVertex.w;
    //float fogDistance = ;
    
    //fogFactor = fogFactorExp2(fogFragCoord, density);

    
    //col = color;
    //depth = position.z;
    varyingtexcoord = texcoord;
    
    gl_Position	= modelViewProjectionMatrix * position;
}
