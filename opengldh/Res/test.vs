attribute vec3 position;
attribute vec2 texture;
attribute vec3 normal;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	gl_Position=ProjectionMatrix*ViewMatrix*ModelMatrix*vec4(position,1.0);
}