#version 460


// Attributes
// in
in vec3 vertexIn;
in vec3 colorIn;
in vec2 textureIn;

// out
out vec3 vertexOut;
out vec3 colorOut;
out vec2 textureOut;

// Uniforms
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 translateMatrix;
uniform mat4 scaleMatrix;
uniform mat4 rotateMatrix;

void main()
{
	colorOut = colorIn;
	textureOut = textureIn;
	vertexOut = (rotateMatrix * scaleMatrix * translateMatrix * vec4(vertexIn,1.0)).xyz;


	gl_Position = projectionMatrix * viewMatrix * rotateMatrix * scaleMatrix * translateMatrix * vec4(vertexIn, 1.0);
}