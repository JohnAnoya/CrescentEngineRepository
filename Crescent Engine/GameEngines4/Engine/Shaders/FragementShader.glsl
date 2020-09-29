#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Colour;
in vec3 FragPosition;

out vec4 fragColour;
uniform vec3 viewPosition;

struct Light { 
	vec3 lightPosition; 
	vec3 lightColour; 
	float ambient; 
	float diffuse; 
};

struct Material { 
	sampler2D diffuseMap;  

	float shininess; 
	float transparency; 

	vec3 ambient; 
	vec3 diffuse; 
	vec3 specular; 
};

uniform Light light; 
uniform Material material; 

void main()
{
	fragColour = texture(material.diffuseMap, TexCoords);

	//AMBIENT
	vec3 ambient = light.ambient *  material.ambient * texture(material.diffuseMap, TexCoords).rgb * light.lightColour; 

	//DIFFUSE 
	vec3 norm = normalize(Normal); 
	vec3 lightDir = normalize(light.lightPosition - FragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = (diff * material.diffuse) * texture(material.diffuseMap, TexCoords).rgb * light.lightColour;

	//SPECULAR
	vec3 viewDir = normalize(viewPosition - FragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = (spec * material.specular) * light.lightColour; 

	vec3 result = (ambient + diffuse + specular);
	fragColour = vec4(result, material.transparency);
}