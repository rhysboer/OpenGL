#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;
out vec4 vPosition;
out vec4 vColour;
out vec4 vNormal;
uniform mat4 projectionViewWorldMatrix;
void main() {
	vPosition = position;
	vNormal = normal;
	gl_Position = projectionViewWorldMatrix * position;
};
