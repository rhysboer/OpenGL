#version 410

in vec4 vNormal;
in vec2 vTexCoord;

out vec4 fragColor;

// Total amount of repeating textures
uniform vec2 textureRepeat;

uniform sampler2D perlinTexture;

uniform sampler2D grass;
uniform sampler2D stone;
uniform sampler2D snow;

void main() {
	
	vec4 perlin = texture(perlinTexture, vTexCoord).rrrr;
	perlin.a = 1.0f;
	
	vec4 snowVec = texture(snow, vTexCoord * textureRepeat);
	vec4 grassVec = texture(grass, vTexCoord * textureRepeat);
	vec4 stoneVec = texture(stone, vTexCoord * textureRepeat);
	
	if(perlin.y > 0.9f){
		fragColor = mix(stoneVec, snowVec, smoothstep(0.9f, 1.0f, perlin.y));
	} else if (perlin.y > 0.6 && perlin.y < 0.9f) {
		fragColor = mix(grassVec, stoneVec, smoothstep(0.5f, 1.0f, perlin.y));
	} else {
		fragColor = texture(grass, vTexCoord * textureRepeat);
	}
};