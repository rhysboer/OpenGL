// VERT SHADER ( OUTLINE )
#version 410

layout( location = 0 ) in vec4 position;
layout( location = 1 ) in vec4 normal;
layout( location = 2 ) in vec2 texCoords;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 projectionViewWorldMatrix;

void main() {

	vPosition = position.xyz;
	vNormal = normal.xyz;
	vTexCoord = texCoords;
	
	gl_Position = projectionViewWorldMatrix * (position + vec4(0, 5, 0, 0));
}