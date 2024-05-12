#version 460

struct Light 
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	float shininess;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

// Attributes
in vec3 colorOut;
in vec2 textureOut;
in vec3 vertexOut;
out vec4 fragColor;


// Uniforms
// object Uniforms
uniform Light light;
uniform Material material;

// uniforms
uniform vec3 cameraPosition;
uniform bool isLit;
uniform bool isTextured;
uniform sampler2D textureImage;

void main()
{
	if (isLit)
	{
		// calculations for lighting
		// ambient
		vec3 ambientColor = light.ambient * material.ambient;

		// ==================================================
		// diffuse
		vec3 normal = vec3(0.0, 1.0, 0.0);
		vec3 lightDirection = normalize(light.position - vertexOut);
		float lightIntensity = max(dot(lightDirection, normal), 0.0); 
		vec3 diffuseColor = light.diffuse * material.diffuse * lightIntensity;

		// ==================================================
		// specular
		vec3 viewDirection = normalize(cameraPosition - vertexOut);

		vec3 reflection = reflect(-lightDirection, normal);
		float specularTerm = pow(max(dot(viewDirection, reflection),0.0), material.shininess);
		vec3 specularColor = light.specular * material.specular * specularTerm;

		vec3 finalColor = ambientColor + diffuseColor + specularColor;

		if (isTextured)
		{
			fragColor = vec4(finalColor, 1.0) * texture(textureImage, textureOut);
		}
		else
		{
			fragColor = vec4(finalColor, 1.0);
		}
	}

	else
	{
		fragColor = vec4(colorOut, 1.0);
	}

}