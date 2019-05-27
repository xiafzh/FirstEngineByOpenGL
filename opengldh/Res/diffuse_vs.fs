#ifdef GL_ES
precision mediump float;
#endif


uniform vec4 U_LightPos;
uniform vec4 U_AmbientLightColor;
uniform vec4 U_AmbientMaterial;
uniform vec4 U_DiffuseLightColor;
uniform vec4 U_DiffuseMaterial;

varying vec3 V_Normal;

void main()
{
	vec4 ambientColor=U_AmbientLightColor*U_AmbientMaterial;

	vec3 L=U_LightPos;
	L=normalize(L);

	vec3 n=normalize(V_Normal);

	float diffuseIntensity= max(0.0f,dot(L,n));
	vec4 diffuseColor=U_DiffuseLightColor*U_DiffuseMaterial*diffuseIntensity;
	
	gl_FragColor=ambientColor+diffuseColor;
}
