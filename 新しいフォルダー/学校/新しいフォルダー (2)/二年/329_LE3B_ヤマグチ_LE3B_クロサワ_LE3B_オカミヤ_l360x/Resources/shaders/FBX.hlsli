cbuffer cbuff0 : register(b0)
{
	matrix viewproj; // ビュープロジェクション行列
	matrix world; // ワールド行列
	float3 cameraPos; // カメラ座標（ワールド座標）
};

cbuffer cbuff1 : register(b1)
{
	float3 baseColor;

	float metalness;

	float specular;

	float roughness;
};

//平行光源
static const int DIRLIGHT_NUM = 3;
struct DirLight
{
	float3 lightv;
	float3 lightcolor;
	uint activ;
};
//点光源
static const int POINTLIGHT_NUM = 3;
struct PointLight
{
	float3 lightpos;
	float3 lightcolor;
	float3 lightatten;
	uint activ;
};
//スポットライト
static const int SPOTLIGHT_NUM = 3;
struct SpotLight
{
	float3 lightv;
	float3 lightpos;
	float3 lightcolor;
	float3 lightatten;
	float2 lightfactoranglecos;
	uint activ;
};
//定数バッファライト用
cbuffer cbuff2:register(b2)
{
	float3 ambientLightColor;
	DirLight dirLight[DIRLIGHT_NUM];
	PointLight pointLight[POINTLIGHT_NUM];
	SpotLight spotLight[SPOTLIGHT_NUM];
}
//バーテックスバッファーの入力
struct VSInput
{
	float4 pos	: POSITION;//位置   
	float3 normal : NORMAL;//頂点法線
	float2 uv	: TEXCOORD;//テクスチャー座標
};

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION; // システム用頂点座標
	float3 worldpos : pos; //ワールド座標
	float3 normal :NORMAL; // 法線
	float2 uv  :TEXCOORD; // uv値
};
