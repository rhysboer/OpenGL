#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec2 texCoord;

out vec2 vTexCoord;

uniform mat4 projectionViewWorldMatrix;

void main() {
	vTexCoord = texCoord;
	gl_Position= projectionViewWorldMatrix * position;
};