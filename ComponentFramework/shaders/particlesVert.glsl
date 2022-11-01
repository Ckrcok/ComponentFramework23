#version 460
layout (location = 0) in  vec4 pos;
layout (location = 1) in  vec4 vel;
layout (location = 2) in  vec4 color;

out vec4 vertColor;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float totalTime;

void main() {
	vertColor = color;
	vec4 newPos = pos + (vel * totalTime);
	//newPos.y += -2.8 * totalTime * totalTime;
	gl_Position =  projectionMatrix * viewMatrix * newPos;
	gl_PointSize = 2.0;
}
