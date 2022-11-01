#version 460
in vec3  vertDir;
out vec4 fragColor;
uniform sampler3D noiseTexture;
uniform vec3 offset;

vec4 solarSurface();
vec4 marbleSurface();
vec4 graniteSurface();

void main() {
	fragColor = marbleSurface();
}	

vec4 solarSurface(){
	vec4 noiseVec = texture(noiseTexture, (vertDir * 1.25) + offset);
    vec4 color1 = vec4(0.8, 0.7, 0.0, 0.0);
	vec4 color2 = vec4(0.6, 0.1, 0.0, 0.0);
	float intensity = abs(noiseVec[0] - 0.25) +
			     abs(noiseVec[1] - 0.125) + 
			     abs(noiseVec[2] - 0.0625) + 
			     abs(noiseVec[3] - 0.03125);
	
	intensity = clamp(intensity * 4.0, 0.0, 1.0);
	return mix(color1, color2, intensity);
}

vec4 marbleSurface(){
	vec4 noiseVec = texture(noiseTexture, vertDir );
    vec4 veinColor = vec4(0.5, 0.3, 0.3, 0.0);
	vec4 marbleColor = vec4(0.7, 0.7, 0.6, 0.0);
	float intensity = abs(noiseVec[0] - 0.25) +
			     abs(noiseVec[1] - 0.125) + 
			     abs(noiseVec[2] - 0.0625) + 
			     abs(noiseVec[3] - 0.03125);
	
	float sinVal = sin(vertDir.y * 6.0 + intensity * 12.0) * 0.5 + 0.5;
	return mix(veinColor, marbleColor, sinVal);	
}

vec4 graniteSurface(){
	vec4 noiseVec = texture(noiseTexture, vertDir + offset);
	float intensity = min(1.0, noiseVec[3] * 18.0);
	return vec4(intensity,intensity,intensity,1.0);	
}