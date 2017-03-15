#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;
layout(location=2) in vec2 texCoord;

out vec4 vNormal;
out vec2 vTexCoord;
out vec4 vShadowCoord;

uniform sampler2D perlinTexture;
uniform mat4 projectionViewWorldMatrix;

// Shadow Test
uniform mat4 lightMatrix;

void main() {
	// Perlin noise
	vec4 pos = position;
	//pos.y += texture(perlinTexture, texCoord).r * 10;
	//
	//vNormal = normal;
	//vTexCoord = texCoord;
	//
	//vShadowCoord = lightMatrix * pos;
	//
	//gl_Position= projectionViewWorldMatrix * pos;
	
	gl_Position = projectionViewWorldMatrix * position;
};