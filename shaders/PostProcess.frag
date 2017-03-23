// FRAGMENT SHADER
#version 410

in vec2 fTexCoord;

out vec4 fragColor;

uniform sampler2D target;
uniform float time;


// another frame buffer for each
mat3 gridX = mat3(
	-1.0, 0.0, 1.0,
	-2.0, 0.0, 2.0,
	-1.0, 0.0, 1.0
);

mat3 gridY = mat3(
	-1.0, -2.0, -1.0,
	0.0, 0.0, 0.0,
	1.0, 2.0, 1.0
);
	
vec4 Simple(){
	return texture(target, fTexCoord);
}

vec4 BoxBlur() {
	
	vec2 texel = 5.0f / textureSize(target, 0).xy;
	
	// 9-tap box kernel
	vec4 colour = texture(target, fTexCoord);
	colour += texture(target, fTexCoord + vec2(-texel.x, texel.y));
	colour += texture(target, fTexCoord + vec2(-texel.x, 0));
	colour += texture(target, fTexCoord + vec2(-texel.x, -texel.y));
	colour += texture(target, fTexCoord + vec2(0, texel.y));
	colour += texture(target, fTexCoord + vec2(0, -texel.y));
	colour += texture(target, fTexCoord + vec2(texel.x, texel.y));
	colour += texture(target, fTexCoord + vec2(texel.x, 0));
	colour += texture(target, fTexCoord + vec2(texel.x, -texel.y));
	return colour / 9;
}

vec4 Pixel() {
    float x = 3.0 * (1.0 / 1280);
    float y = 3.0 * (1.0 / 720);
	
    vec2 newCoord = vec2(x * floor(fTexCoord.x / x), y * floor(fTexCoord.y / y));
	return texture(target, newCoord);
}

void main() {
	fragColor = Pixel();
}