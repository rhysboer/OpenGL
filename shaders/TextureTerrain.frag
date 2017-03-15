#version 410

in vec4 vNormal;
in vec2 vTexCoord;

// Shadow Test
in vec4 vShadowCoord;

out vec4 fragColor;

// Shadow Test
uniform vec3 lightDir;
uniform sampler2D shadowMap;
uniform float shadowBias;

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
	
	//vec4 perlin = texture(perlinTexture, vTexCoord).rrrr;
	//perlin.a = 1.0f;
	//
	//vec4 snowVec = texture(snow, vTexCoord * textureRepeat);
	//vec4 grassVec = texture(grass, vTexCoord * textureRepeat);
	//vec4 stoneVec = texture(stone, vTexCoord * textureRepeat);
	//vec4 sandVec = texture(sand, vTexCoord * textureRepeat);
	//
	//if(perlin.y > 0.9f){
	//	fragColor = mix(stoneVec, snowVec, smoothstep(0.9f, 1.0f, perlin.y));
	//} else if (perlin.y > 0.6 && perlin.y < 0.9f) {
	//	fragColor = mix(grassVec, stoneVec, smoothstep(0.5f, 1.0f, perlin.y));
	//} else if (perlin.y > 0.35 && perlin.y < 0.6) {
	//	fragColor = mix(sandVec, grassVec, smoothstep(0.4f, 0.5f, perlin.y));
	//} else{
	//	fragColor = sandVec;
	//}
	
	
	float d = max(0, dot(normalize(vNormal.xyz), lightDir));
	
	if(texture(shadowMap, vShadowCoord.xy).r < vShadowCoord.z - shadowBias) {
		d = 0;
	}
	
	fragColor = vec4(d, d, d, 1);
	
};