#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 albedo = vec4(1.0, 1.0, 1.0, 0.75);

void main()
{
	color = vec4(albedo.x, albedo.y, albedo.z, albedo.w);
}