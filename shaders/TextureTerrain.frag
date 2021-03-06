#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec2 vTexCoord;

out vec4 fragColor;

// Total amount of repeating textures
uniform vec2 textureRepeat;

// Perlin noise texture
uniform sampler2D perlinTexture;

// Textures
uniform sampler2D grass;
uniform sampler2D stone;
uniform sampler2D snow;
uniform sampler2D sand;



void main() {
	
	vec4 perlin = texture(perlinTexture, vTexCoord).rrrr;
	perlin.a = 1.0f;

	vec4 snowVec = texture(snow, vTexCoord * textureRepeat);
	vec4 grassVec = texture(grass, vTexCoord * textureRepeat);
	vec4 stoneVec = texture(stone, vTexCoord * textureRepeat);
	vec4 sandVec = texture(sand, vTexCoord * textureRepeat);

	vec4 placeTexture;
	
	if(perlin.y > 0.9f){
		placeTexture = mix(stoneVec, snowVec, smoothstep(0.9f, 1.0f, perlin.y));
	} else if (perlin.y > 0.6 && perlin.y < 0.9f) {
		placeTexture = mix(grassVec, stoneVec, smoothstep(0.5f, 1.0f, perlin.y));
	} else if (perlin.y > 0.35 && perlin.y < 0.6) {
		placeTexture = mix(sandVec, grassVec, smoothstep(0.4f, 0.5f, perlin.y));
	} else{
		placeTexture = sandVec;
	}
	
	fragColor = placeTexture;
};