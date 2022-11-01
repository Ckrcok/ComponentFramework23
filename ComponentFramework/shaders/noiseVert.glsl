#version 460
/// This is the reflection shader
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;

out vec3 vertNormal;
out vec3 vertDir;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 offset;
uniform sampler3D noiseTexture;

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vertDir = normalize(vertPos);
	vec3 vertex =vec3(vVertex); /// vVertex.xyz
	vec4 noiseVec = texture(noiseTexture, (vertex * 0.4) + (0.25 * offset) );
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * (vVertex + noiseVec); 
}
