// FRAGMENT SHADER – USE SHADOW
#version 410

in vec4 vNormal;
out vec4 fragColour;

uniform vec3 lightDir;

void main() {
	float d = max(0, dot(normalize(vNormal.xyz), lightDir));
	fragColour = vec4(d, d, d, 1);
}