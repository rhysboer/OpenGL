#version 410

in vec4 vNormal;
in vec2 vTexCoord;

out vec4 fragColor;

uniform sampler2D diffuse;

void main() {
	fragColor = texture(diffuse,vTexCoord);
};