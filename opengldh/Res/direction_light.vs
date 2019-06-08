attribute vec3 position;
attribute vec2 texcoord;
attribute vec3 normal;

uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 IT_ModelMatrix;

varying vec3 V_Normal;
varying vec4 V_WorldPos;

void main()
{
	V_Normal=mat3(IT_ModelMatrix)*normal;
	V_WorldPos = ModelMatrix * vec4(position, 1.0);
	gl_Position=ProjectionMatrix*ViewMatrix*V_WorldPos;
}