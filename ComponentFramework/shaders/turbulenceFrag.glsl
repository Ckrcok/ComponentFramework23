#version 460
in vec3  vertDir;
out vec4 fragColor;
uniform sampler3D noiseTexture;
uniform vec3 offset;

void main() {
	vec4 noiseVec = texture(noiseTexture, (vertDir * 1.25) + offset);
    vec4 color1 = vec4(0.8, 0.7, 0.0,0.0);
	vec4 color2 = vec4(0.6, 0.1, 0.0,0.0);
	float intensity = abs(noiseVec[0] - 0.25) +
			     abs(noiseVec[1] - 0.125) + 
			     abs(noiseVec[2] - 0.0625) + 
			     abs(noiseVec[3] - 0.03125);
	
	intensity = clamp(intensity * 4.0, 0.0, 1.0);
	fragColor = mix(color1, color2, intensity);
}
