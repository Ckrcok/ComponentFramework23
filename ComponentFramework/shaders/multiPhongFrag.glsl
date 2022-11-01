#version 460
in  vec3 vertNormal;
in  vec3 lightDir0;
in  vec3 lightDir1;
in  vec3 eyeDir;
out vec4 fragColor;

void main() { 
	vec4 ks0 = vec4(0.6, 0.6, 0.6, 0.0);
	vec4 ks1 = vec4(0.6, 0.6, 0.6, 0.0);

	vec4 kd0 = vec4(0.4, 0.01, 0.01, 0.0); 
	vec4 kd1 = vec4(0.1, 0.1, 0.4, 0.0); 

	vec4 ka = 0.1 * kd0; 
	
	float diff0 = max(dot(vertNormal, lightDir0), 0.0);
	float diff1 = max(dot(vertNormal, lightDir1), 0.0);

	/// Reflection is based on the incedent light source which means it is 
	/// a vector FROM the light source to the vertex not the direction TO the light source

	vec3 reflection0 = normalize(reflect(-lightDir0, vertNormal));
	vec3 reflection1 = normalize(reflect(-lightDir1, vertNormal));

	float spec0 = max(dot(eyeDir, reflection0), 0.0);
	if(diff0 > 0.0){
		spec0 = pow(spec0,14.0);
	}
	float spec1 = max(dot(eyeDir, reflection1), 0.0);
	if(diff0 > 0.0){
		spec1 = pow(spec1,14.0);
	}
	fragColor =  ka + ((diff0 * kd0) + (spec0 * ks0 )) + ((diff1 * kd1) + (spec1 * ks1));
	
} 

