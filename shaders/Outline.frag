// FRAG SHADER ( OUTLINE )
#version 410

out vec4 fragColor;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexCoord;

// Depth Picture
uniform sampler2D screenTexture;

// X axis filter
mat3 filX = mat3(
	1, 2, 1,
	0, 0, 0,
	-1, -2, -1
);

// Y axis filter
mat3 filY = mat3(
	1, 0, -1,
	2, 0, -2,
	1, 0, -1
);

void main() {

	vec3 diffuse = texture(screenTexture, vTexCoord.st).rgb;
	mat3 I;
	
	for(int x = 0; x < 3; x++){
		for(int y = 0; y < 3; y++){
			vec3 sam = texelFetch(screenTexture, ivec2(gl_FragCoord) + ivec2(x-1,y-1), 0).rgb;
			I[x][y] = length(sam);
		}
	}
	
	float gx = dot(filX[0], I[0]) + dot(filX[1], I[1]) + dot(filX[2], I[2]);
	float gy = dot(filY[0], I[0]) + dot(filY[1], I[1]) + dot(filY[2], I[2]);
	
	float g = sqrt(pow(gx, 2.0)+pow(gy, 2.0));
	g = smoothstep(2.0, 5.0, g);
    
	fragColor = vec4(diffuse - vec3(g), 1.0);
}