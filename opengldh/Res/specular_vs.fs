#ifdef GL_ES
precision mediump float;
#endif


uniform vec4 U_LightPos;
uniform vec4 U_EyePos;
uniform vec4 U_AmbientLightColor;
uniform vec4 U_AmbientMaterial;
uniform vec4 U_DiffuseLightColor;
uniform vec4 U_DiffuseMaterial;
uniform vec4 U_SpecularLightColor;
uniform vec4 U_SpecularMaterial;

varying vec3 V_Normal;
varying vec4 V_WorldPos;

void main()
{
	vec4 ambientColor=U_AmbientLightColor*U_AmbientMaterial;

	vec3 L=U_LightPos;
	L=normalize(L);

	vec3 n=normalize(V_Normal);

	float diffuseIntensity=max(0.0f,dot(L,n));
	vec4 diffuseColor=U_DiffuseLightColor*U_DiffuseMaterial*diffuseIntensity;
	
	// specular
	vec3 reflectDir=reflect(-L, n);
	reflectDir=normalize(reflectDir);

	vec3 viewDir=U_EyePos.xyz-V_WorldPos.xyz;
	viewDir=normalize(viewDir);

	vec4 specularColor=U_SpecularLightColor*U_SpecularMaterial*pow(max(0.0,dot(viewDir,reflectDir)), 32.0);

	gl_FragColor=ambientColor+diffuseColor+specularColor;
}
