#version 400

smooth in vec4 vertPos;
smooth in vec4 vertNormal;
smooth in vec2 vertUV;

out vec4 outputColour;

uniform vec4 CameraPos;

uniform vec4 kA;
uniform vec4 kD;
uniform vec4 kS;

uniform int useTextures = 0;

uniform sampler2D DiffuseTexture;
uniform sampler2D SpecularTexture;
uniform sampler2D NormalTexture;

uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

uniform vec4 lightDirection;

void main()
{
	vec4 textureData = vec4(1, 1, 1, 1);

	if(useTextures != 0)
	{
		textureData = texture(DiffuseTexture, vertUV);
	}

	vec3 ambient = kA.xyz * lightAmbient;
	
	float nDL = max(0.0f, dot(normalize(vertNormal), -lightDirection));
	vec3 diffuse = kD.xyz * lightDiffuse * nDL * textureData.rgb;

	vec3 r = reflect(lightDirection, normalize(vertNormal)).xyz;
	vec3 e = normalize(CameraPos - vertPos).xyz;

	float specTerm = pow(max(0.0f, dot(e, r)), kS.a);
	vec3 specular = kS.xyz * lightSpecular * specTerm;

	outputColour = vec4(ambient + diffuse + specular, 1.0f);
}