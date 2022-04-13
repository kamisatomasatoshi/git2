#include "BasicShaderHeader.hlsli"
VSOutput VSmain(float4 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	float4 wnormal = normalize(mul(world, float4(normal, 0)));
	float4 wpos = mul(world, pos);
	//�g�U���ˌ�
	float3 diffuse = dot(lightv, wnormal.xyz);
	//����x
	const float shininess = 4.0f;
	//���_���王�_�ւ̕����x�N�g��
	float3 eyedir = normalize(cameraPos - wpos.xyz);
	//���ˌ��x�N�g��
	float3 reflect = normalize(-lightv + 2 * dot(lightv, wnormal.xyz) * wnormal.xyz);//(lightdir + 2 * dot(-lightdir, normal)*normal);
	//���ʔ��ˌ�
	float3 specular = pow(saturate(dot(reflect, eyedir)), shininess);

	VSOutput output; // �s�N�Z���V�F�[�_�[�ɓn���l
	output.svpos = mul(mul(viewproj, world), pos);//���W�ɍs�����Z
	output.normal = normal;
	output.color.rgb = (diffuse + specular) * lightcolor;
	output.color.a = 1;
	output.uv = uv;
	return output;
}