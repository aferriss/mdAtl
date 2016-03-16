#version 150



uniform sampler2D tDiffuse;
uniform float amount;
uniform float angle;

in vec2 varyingtexcoord;
out vec4 outputColor;

void main() {
    
    vec2 vUv = varyingtexcoord;
    vec2 offset = amount * vec2( cos(angle), sin(angle));
    float dist = distance(vUv, vec2(0.5));
    offset = vec2(dist*dist)*0.02;
    vec4 cr = texture(tDiffuse, vUv + offset);
    vec4 cga = texture(tDiffuse, vUv);
    vec4 cb = texture(tDiffuse, vUv - offset);
    
    
    
    outputColor = vec4(cr.r, cga.g, cb.b, cga.a);
}