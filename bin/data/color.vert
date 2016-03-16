varying vec2 v_texCoord;

void main() {
    gl_Position	= gl_ModelViewProjectionMatrix * gl_Vertex;
    //gl_FrontColor = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    v_texCoord = gl_TexCoord[0].st;
}