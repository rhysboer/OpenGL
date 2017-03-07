// Vertex Shader ( Morphing )
#version 410

// VBO 01
layout( location = 0 ) in vec3 Position;
layout( location = 1 ) in vec3 Normal;
layout( location = 2 ) in vec2 TexCoord;

// VBO 02
layout( location = 3 ) in vec3 Position2;
layout( location = 4 ) in vec3 Normal2;

out vec4 vNormal;
out vec2 vTexCoord;

uniform mat4 projectionViewModel;
uniform float keyTime; 	// Between 0,1

void main(){
	vec3 p = mix(Position, Position2, keyTime);
	vec3 n = mix(Normal, Normal2, keyTime);
	
	vNormal = vec4(n.xyz, 0);
	vTexCoord = TexCoord;
	
	gl_Position = projectionViewModel * vec4(p, 1);
}