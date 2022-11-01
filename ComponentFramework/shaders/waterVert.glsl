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
uniform sampler3D noiseTexture; 

/// C-style prototypes
vec4 grow();
vec4 shrink();

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(modelMatrix * vVertex); /// This is the position of the vertex from the origin
	vertDir = normalize(vertPos);

	gl_Position =  (projectionMatrix * viewMatrix) * modelMatrix * (vVertex + shrink() );
}

vec4 grow( ){
	vec4 grow = vNormal * time;
	grow.w = 1.0;
	return grow;
}

vec4 shrink( ){
	vec4 grow = vNormal / time;
	grow.w = 1.0;
	return grow;
}


