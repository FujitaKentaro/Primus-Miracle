#pragma once
#pragma warning(push)
#pragma warning(disable: 4819)
#pragma warning(disable: 4820)
#pragma warning(disable: 4061)
#pragma warning(disable: 4514)
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include <string.h>
#pragma warning(pop)
#include "Model.h"
#include "LightGroup.h"
#include "Affin.h"
#include "Transform.h"
#include "Camera.h"


/// <summary>
/// 3Dオブジェクト
/// </summary>
class Object3d
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略

	// 定数バッファ用データ構造体
	struct ConstBufferDataB0
	{
		Matrix4 veiwproj;  //ビュープロジェクション行列
		Matrix4 world;		//ワールド行列
		Vector3 cameraPos;	//カメラ座標 (ワールド座標)
		float pad1;//パディング
		Vector4 color;
	};



private: // 定数
	static const uint32_t division = 50;					// 分割数
	static const float radius;				// 底面の半径
	static const float prizmHeight;			// 柱の高さ
	static const uint32_t planeCount = division * 2 + division * 2;		// 面の数
	static const uint32_t vertexCount = planeCount * 3;		// 頂点数

public: // 静的メンバ関数
	/// <summary>
	/// 静的初期化
	/// </summary>
	/// <param name="device">デバイス</param>
	/// <param name="window_width">画面幅</param>
	/// <param name="window_height">画面高さ</param>
	static void StaticInitialize(ID3D12Device* device);

	/// <summary>
	/// 描画前処理
	/// </summary>
	/// <param name="cmdList">描画コマンドリスト</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// 描画後処理
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3Dオブジェクト生成
	/// </summary>
	/// <returns></returns>
	static Object3d* Create();

private: // 静的メンバ変数
	// デバイス
	static ComPtr<ID3D12Device> device_;

	// コマンドリスト
	static ComPtr<ID3D12GraphicsCommandList> cmdList_;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelinestate;


	//ライト
	static LightGroup* lightGroup_;

	// ビュー行列
	static Matrix4 matView;
	// 射影行列
	static Matrix4 matProjection;
	// 視点座標
	static Vector3 eye;
	// 注視点座標
	static Vector3 target;
	// 上方向ベクトル
	static Vector3 up;


	static float focalLengs;

private:// 静的メンバ関数

	/// <summary>
	/// カメラ初期化
	/// </summary>
	/// <param name="window_width">画面横幅</param>
	/// <param name="window_height">画面縦幅</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// グラフィックパイプライン生成
	/// </summary>
	/// <returns>成否</returns>
	static void InitializeGraphicsPipeline();

	/// <summary>
	/// ビュー行列を更新
	/// </summary>
	static void UpdateViewMatrix();

public: // メンバ関数

	Object3d();
	~Object3d();

	bool Initialize();
	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	void UpdateMatrix();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	Object3d* GetParent() const { return parent_; }

	void SetParent(Object3d* parent) { parent_ = parent; }
	static void SetCamera(Camera* camera) { Object3d::camera_ = camera; }

	static void SetLight(LightGroup* lightGroup) {
		Object3d::lightGroup_ = lightGroup;
	}

	//setter
	void SetModel(Model* model) { model_ = model; }
	void SetColor(Vector4 color) { color_ = color; }
	Vector4 GetColor() { return color_; }
	Model& GetModel() { return *model_; }

private: // メンバ変数
	Vector4 color_ = {0.0f,0.0f,0.0f,1.0f};
	ComPtr<ID3D12Resource> constBuffB0; // 定数バッファ

	// 色
public:

	// 親オブジェクト
	Object3d* parent_ = nullptr;
	//モデル
	Model* model_ = nullptr;
	static Camera* camera_;

	static float win_wi, win_hi;
public:
	Transform transForm;

};