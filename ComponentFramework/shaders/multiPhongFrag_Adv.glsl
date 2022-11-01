#version 460
const int MAX_LIGHTS = 8;

struct LightStruct {
	vec3 lightPos;
	vec4 diffuseColor;
	vec4 specularColor;
};

in  vec3 vertNormal;
in  vec3 lightDir[8];
in  vec3 eyeDir;
out vec4 fragColor;
uniform int numLights;
uniform vec4 lightDiffuse[MAX_LIGHTS];
uniform vec4 lightSpecular[MAX_LIGHTS];

void main() { 
	
	vec4 ka = vec4(0.01, 0.01, 0.01, 0.0);
	
	float diff[MAX_LIGHTS];
	vec3 reflection[MAX_LIGHTS];
	float spec[MAX_LIGHTS];
	
	for(int i = 0; i < numLights; ++i){
		diff[i] = max(dot(vertNormal, lightDir[i]), 0.0);
		/// Reflection is based on the incedent light source which means it is 
		/// a vector FROM the light source to the vertex not the direction TO the light source
		reflection[i] = normalize(reflect(-lightDir[i], vertNormal));
		spec[i] = max(dot(eyeDir, reflection[i]), 0.0);
		if(diff[i] > 0.0){
			spec[i] = pow(spec[i],14.0);
		}
		fragColor +=  ka + ((diff[i] * lightDiffuse[i]) + (spec[i] * lightSpecular[i] ));
	}
} 

