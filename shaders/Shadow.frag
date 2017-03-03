// FRAGMENT SHADER – USE SHADOW
#version 410

in vec4 vNormal;
in vec4 vShadowCoord;

out vec4 fragColour;

uniform vec3 lightDir;
uniform sampler2D shadowMap;

vec2 poissonDisk[4] = vec2[](
	vec2( -0.94201624, -0.39906216 ),
	vec2( 0.94558609, -0.76890725 ),
	vec2( -0.094184101, -0.92938870 ),
	vec2( 0.34495938, 0.29387760 )
);

void main() {

	float d = max(0, dot(normalize(vNormal.xyz), lightDir));
	
	for(int i=0; i < 4; i++) {
		if(texture(shadowMap, vShadowCoord.xy + poissonDisk[i]/700.0f).r < vShadowCoord.z - 0.01f){
			d -= 0.2f;
		}
	}
	
	fragColour = vec4(d, d, d, 1);
}