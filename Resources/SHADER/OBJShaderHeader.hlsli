cbuffer cbuff0 : register(b0)
{
	matrix viewproj;//ビュープロジェクション行列
	matrix world; //ワールド行列
	float3 cameraPos; //カメラ座標 (ワールド座標)
    float4 color_; // 色情報
};

cbuffer cbuff1 : register(b1)
{
	float3 m_ambient  : packoffset(c0); // アンビエント係数
	float3 m_diffuse  : packoffset(c1); // ディフューズ係数
	float3 m_specular : packoffset(c2); // スペキュラー係数
	float m_alpha : packoffset(c2.w);	// アルファ
}

cbuffer cbuff2 : register(b2)
{
    float3 lightv; //ライト方向の単位ベクトル
    float3 lightcolor; //ライトの色(RGB)
}

static const uint DIR_LIGHT_NUM = 3;

//平行
struct DirLight {
	float3 lightv;//ライト
	float3 lightcolor;
	uint active;
};

//点光源の数
static const int POINTLIGHT_NUM = 3;

struct PointLight {
	float3 lightpos;//ライト座標
	float3 lightcolor;//ライトの色
	float3 lightatten;//ライトの距離減衰係数
	uint active;
};

//スポットライトの数
static const int SPOTLIGHT_NUM = 3;

struct SpotLight {
	float3 lightv;//ライトの光線方向の逆ベクトル
	float3 lightpos;//ライトの座標
	float3 lightcolor;//ライトの色
	float3 lightatten;//ライト距離減衰係数
	float2 lightfactoranglecos;//ライト減衰角度のコサイン
	uint active;
};


//丸影の数
static const int CIRCLESHADOW_NUM = 1;

struct CircleShadow {
	float3 dir;//東映方向の逆ベクトル
	float3 casterPos;//キャスター座標
	float distanceCasterLight;//キャスターとライトの距離
	float3 atten;//距離減衰係数
	float2 factorAngleCos;//減衰角度のコサイン
	uint active;
};


cbuffer cbuff2 : register(b2) {
	float3 ambientColor;
	DirLight dirLights[DIR_LIGHT_NUM];
	PointLight pointLights[POINTLIGHT_NUM];
	SpotLight spotLights[SPOTLIGHT_NUM];
	CircleShadow circleShadows[CIRCLESHADOW_NUM];
}

// 頂点シェーダーからピクセルシェーダーへのやり取りに使用する構造体
struct VSOutput
{
	float4 svpos : SV_POSITION;// システム用頂点座標
	float4 worldpos :POSITION;//ワールド座標
	float3 normal :NORMAL;//法線
	float2 uv  :TEXCOORD;// uv値
};
