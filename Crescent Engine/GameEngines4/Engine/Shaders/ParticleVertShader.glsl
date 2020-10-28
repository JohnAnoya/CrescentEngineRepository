#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view; 

void main(){
	vec4 temp = view * model * vec4(position, 1.0f);
	float dist = length(temp.xyz);
	float attenuation = inversesqrt(0.1f * dist);

	gl_Position = proj * model * vec4(position, 1.0f);
	TexCoords = texCoords;
}