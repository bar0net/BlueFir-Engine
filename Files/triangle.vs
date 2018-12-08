#version 330 core

layout(location = 0) in vec3 vertex_position;

layout(std140) uniform GlobalMatrices
{
    mat4 proj;
    mat4 view;
};

uniform mat4 model= mat4(vec4(1, 0, 0, 0),   vec4(0, 1, 0, 0),   vec4(0, 0, 1, 0),   vec4(0, 0, 0, 1));

void main() 
{    
	gl_Position = proj * view * model * vec4(vertex_position, 1.0); 
}