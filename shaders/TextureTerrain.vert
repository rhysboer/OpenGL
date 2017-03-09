#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;
layout(location=2) in vec2 texCoord;

out vec4 vNormal;
out vec2 vTexCoord;

uniform sampler2D perlinTexture;
uniform mat4 projectionViewWorldMatrix;

void main() {
	// Perlin noise
	vec4 pos = position;
	pos.y += texture(perlinTexture, texCoord).r * 10;
	
	vNormal = normal;
	vTexCoord = texCoord;
	
	gl_Position= projectionViewWorldMatrix * pos;
};