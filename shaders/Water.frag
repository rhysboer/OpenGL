// FRAGMENT SHADER ( WATER )
#version 410

uniform sampler2D waterTexture;
uniform float scrollSpeed;

uniform float time;
uniform int repeatCount;

out vec4 fragColor;

in vec4 vPosition;
in vec4 vNormal;
in vec2 vTexCoord;

void main(){
	fragColor = texture(waterTexture, ((vTexCoord + (time * 0.02f)) * repeatCount));
}