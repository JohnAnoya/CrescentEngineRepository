#version 450 core

in vec2 TexCoords;
out vec4 colour;

uniform vec4 particleColour;
uniform sampler2D textureID;

void main(){
	vec4 tmpColour =  texture(textureID, TexCoords) * particleColour;
	colour = tmpColour;
}