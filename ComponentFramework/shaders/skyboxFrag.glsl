#version 460
out vec4 fragColor;

in vec3 uvwCoords;
uniform samplerCube skyboxTexture;

void main() { 
	vec3 uvwCoordsFix  = uvwCoords;
	uvwCoordsFix.x *= -1.0;
	fragColor = texture(skyboxTexture,uvwCoordsFix);	
} 

