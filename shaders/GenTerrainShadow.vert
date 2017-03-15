// VERTEX SHADER ( Generate Terrain Shadow ) 
// Change later, so that the shader doesn't create the terrain warp
#version 410

layout(location=0) in vec4 position;
layout(location=2) in vec2 texCoord;

uniform sampler2D perlinTexture;
uniform mat4 lightMatrix;

void main() {

	// Perlin noise
	vec4 pos = position;
	pos.y += texture(perlinTexture, texCoord).r * 10;
	
	gl_Position = lightMatrix * pos;
};