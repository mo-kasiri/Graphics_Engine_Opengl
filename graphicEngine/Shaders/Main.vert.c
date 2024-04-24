#version 460

in vec3 vertexIn;
in vec3 colorIn;
out vec3 colorOut;


uniform mat4 viewMatrix;

uniform mat4 translateMatrix;
uniform mat4 scaleMatrix;

uniform mat4 projectionMatrix;

void main()
{
	colorOut = colorIn;
	gl_Position = projectionMatrix * viewMatrix * scaleMatrix * translateMatrix * vec4(vertexIn, 1.0);
}