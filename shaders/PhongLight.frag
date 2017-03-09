#version 410
in vec4 vPosition;
in vec4 vNormal;

out vec4 fragColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform float specPow;

vec4 ambientLight = vec4(0.2f, 0.2f, 0.2f, 1) * vNormal;

void main() {
	
	float d = max(0, dot(normalize(vNormal.xyz), lightDirection));
	vec3 E = normalize(cameraPos - vPosition.xyz);
	vec3 R = reflect(-lightDirection, vNormal.xyz);
	float s = max(0, dot(E,R));
	s = pow(s, specPow);
	
	// Toon Shading
	if(d > 0.95f){
		d = 1.0f;
	}else if(d > 0.5f){
		d = 0.6f;
	}else if(d > 0.25){
		d = 0.4f;
	}else{
		d = 0.2f;
	}
	
	fragColor = vec4(ambientLight.xyz + vNormal.xyz * d + lightColor * s, 1);
};
