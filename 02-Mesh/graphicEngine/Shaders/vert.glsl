#version 460

// Attributes
// in
in vec3 vertexIn;

// Uniforms
uniform mat4 translateMatrix;
uniform mat4 scaleMatrix;
uniform mat4 rotateMatrix;

void main()
{
	//gl_PointSize = gl_Normal.x;
	gl_Position = rotateMatrix * scaleMatrix * translateMatrix * vec4(vertexIn, 1.0);
}