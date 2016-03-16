#version 150

uniform sampler2D srcTex;
//uniform sampler2D depthTex;
uniform vec2 step;
uniform vec2 res;

in vec2 varyingtexcoord;
out vec4 outputcolor;

//varying vec4 vertTexCoord;

// gaussian blur filter modified from Filip S. at intel 
// https://software.intel.com/en-us/blogs/2014/07/15/an-investigation-of-fast-real-time-gpu-based-image-blur-algorithms
vec3 GaussianBlur( sampler2D tex0, vec2 centreUV, vec2 pixelOffset ){                                                                                                                                                                    
	vec3 colOut = vec3( 0.0, 0.0, 0.0 );
    /*
    float dt = texture(depthTex, varyingtexcoord).r;
    
    float focus = 0.5;
    float aperture = 0.5;
    float maxBlur = 0.2;
    
    float factor = dt - focus;
    vec2 dof = vec2(clamp(factor * aperture, -maxBlur, maxBlur));
	 */
	const int stepCount = 9;
	float gWeights[stepCount];
	    gWeights[0] = 0.10855;
	    gWeights[1] = 0.13135;
	    gWeights[2] = 0.10406;
	    gWeights[3] = 0.07216;
	    gWeights[4] = 0.04380;
	    gWeights[5] = 0.02328;
	    gWeights[6] = 0.01083;
	    gWeights[7] = 0.00441;
	    gWeights[8] = 0.00157;

	float gOffsets[stepCount];
	    gOffsets[0] = 0.66293;
	    gOffsets[1] = 2.47904;
	    gOffsets[2] = 4.46232;
	    gOffsets[3] = 6.44568;
	    gOffsets[4] = 8.42917;
	    gOffsets[5] = 10.41281;
	    gOffsets[6] = 12.39664;
	    gOffsets[7] = 14.38070;
	    gOffsets[8] = 16.36501;
	

	for( int i = 0; i < stepCount; i++ ){                                                                                                                                                                
	    vec2 texCoordOffset = gOffsets[i] * pixelOffset;                                                                                                           
	    //vec3 col = texture( tex0, centreUV + texCoordOffset *dof).xyz + texture( tex0, centreUV - texCoordOffset *dof).xyz;
        vec3 col = texture( tex0, centreUV + texCoordOffset ).xyz + texture( tex0, centreUV - texCoordOffset ).xyz;
	    colOut += gWeights[i] * col;                                                                                                                               
	}

	return colOut;                                                                                                                                                   
} 


void main(){
	
	vec2 uv = varyingtexcoord;
	//vec3 blurredTex = GaussianBlur(srcTex, vec2(uv.x, res.y-uv.y), vec2(0.0, step.y ) );
    vec3 blurredTex = GaussianBlur(srcTex, vec2(uv.x, uv.y), vec2(0.0, step.y ) );

	outputcolor = vec4(blurredTex, 1.0);
}