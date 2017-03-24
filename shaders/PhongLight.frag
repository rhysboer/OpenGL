#version 410
in vec4 vPosition;
in vec4 vNormal;
in vec2 vTextureCoords;

out vec4 fragColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform float specPow;

// Texture
uniform sampler2D mainTexture;

// Texture to Vec4
vec4 textVec = texture(mainTexture, vTextureCoords);

vec4 ambientLight = vec4(0.4f, 0.4f, 0.4f, 1) * textVec;

void main() {
	
	float d = max(0, dot(normalize(vNormal.xyz), lightDirection));
	vec3 E = normalize(cameraPos - vPosition.xyz);
	vec3 R = reflect(-lightDirection, vNormal.xyz);
	float s = max(0, dot(E,R));
	s = pow(s, specPow);
	
	fragColor = vec4(ambientLight.xyz + textVec.xyz * d + lightColor * s, 1);
};
