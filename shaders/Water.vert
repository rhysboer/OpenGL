// VERTEX SHADER ( WATER )
#version 410
layout(location=0) in vec4 position;
layout(location=1) in vec4 normal;
layout(location=2) in vec2 texCoord;

uniform mat4 projectionViewWorldMatrix;
uniform float time;

// Wave Settings
uniform float waveHeight;	// Height of the waves
uniform float waveSpeed;	// Speed of the waves

out vec4 vPosition;
out vec4 vNormal;
out vec2 vTexCoord;
out float timer;

void main(){

	vPosition = position;
	vNormal = normal;
	vTexCoord = texCoord;
	
	vec4 pos = position;
	pos.y = position.y + sin((time + position.x) * waveSpeed) * waveHeight;
	
	timer = time;
	
	gl_Position = projectionViewWorldMatrix * pos;
}