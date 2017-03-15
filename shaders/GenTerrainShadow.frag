// FRAG SHADER ( Generate Terrain Shadow ) 
// Change later, so that the shader doesn't create the terrain warp

#version 410

out float fragDepth;

void main() { 
	fragDepth = gl_FragCoord.z;
}