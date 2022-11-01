#version 460
in  vec3 vertNormal;
in  vec3 lightDir;
in  vec3 eyeDir;
in  vec2 uvCoords;
out vec4 fragColor;

uniform sampler2D myTexture;

void main() { 
	
	float diff = max(dot(vertNormal, lightDir), 0.0);
	vec4 textureColor = texture(myTexture,uvCoords);


	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float spec = max(dot(eyeDir, reflection), 0.0);
	if(diff > 0.0){
		spec = pow(spec,14.0);
	}
	vec4 specLightColor = vec4(0.2, 0.2, 0.2, 0.0);
	vec4 ka = 0.1 * textureColor;
	fragColor =  ka + ((diff * textureColor) + (spec * specLightColor ));
	
} 

