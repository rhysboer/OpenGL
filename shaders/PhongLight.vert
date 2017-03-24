#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;
layout(location=2) in vec2 texCoords;

out vec4 vPosition;
//out vec4 vColour;
out vec4 vNormal;
out vec2 vTextureCoords;

uniform mat4 projectionViewWorldMatrix;
uniform vec4 offsetPosition;

void main() {
	vPosition = position;
	vNormal = normal;
	vTextureCoords = texCoords; 
	
	gl_Position = projectionViewWorldMatrix * (position + offsetPosition);
};
