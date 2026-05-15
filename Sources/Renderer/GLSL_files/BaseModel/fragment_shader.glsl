#version 460
in vec3 fragmentColor;
out vec4 frag_color;

void main(){
    frag_color = vec4(fragmentColor, 1.0); 
}
