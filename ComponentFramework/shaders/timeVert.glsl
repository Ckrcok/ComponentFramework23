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
uniform float time;

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vertDir = normalize(vertPos);
	vec4 grow = vVertex * time;
	grow.w = 1.0;
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * (grow); 
}
