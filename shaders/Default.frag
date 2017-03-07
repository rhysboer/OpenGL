// FRAG SHADER ( DEFAULT )
#version 410

in vec4 vNormal;

out vec4 fragColor;

void main() { 
	fragColor = vec4(vNormal.xyz, 1);
}