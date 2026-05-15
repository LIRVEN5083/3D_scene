#version 460

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_color;

uniform mat4 u_Model; 
uniform mat4 u_Projection;
uniform mat4 u_View;

out vec3 fragmentColor;

void main() {
    gl_Position = u_Projection * u_View * u_Model * vec4(vertex_position, 1.0);
    fragmentColor = vertex_color;
}
