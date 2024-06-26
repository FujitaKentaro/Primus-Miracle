#pragma once
#include "Object3d.h"
#include "MathUtility.h"


class ObjectParticle
{
public:
	/// <summary>
	/// 作成
	/// </summary>
	/// <returns></returns>
	static ObjectParticle* Create(const Vector3& pos_, Model* model_, const Vector3& velocity_, float scale = 1.0f, Vector4 color = { 1,1,1,1 });

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="pos_"></param>
	/// <param name="model_"></param>
	/// <param name="pipeline_"></param>
	void Init(const Vector3& pos_, Model* model_, const Vector3& velocity_, float scale, Vector4 color);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="viewPro"></param>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 死んだかゲッター
	/// </summary>
	/// <returns></returns>
	const bool GetIsDead() const
	{
		return isDead;
	}

private:
	// オブジェクト
	std::unique_ptr<Object3d> object_ = nullptr;

	Vector3 velocity_ = { 0,0,0 };

	// 生存時間
	uint32_t lifeTimer = 0;
	const uint32_t MAXLIFETIME = 30;

	float easeTimer = 0;
	const float MAXEASETIME = 20;

	// 終了かどうか
	bool isDead = false;
};



class ObjParticleManager
{
public:
	// インスタンス
	static ObjParticleManager* GetInstance();

	struct ParticlePreset
	{
		// 発生位置
		Vector3 pos_;
		// 広がり値
		Vector2 velocityMinMax = { -1.0,1.0 };
		// 一回で出す量
		size_t volume = 10;
		// オブジェクトスケール
		float scale = 1.0f;
		// オブジェクトカラー
		Vector4 color = { 1,1,1,1 };
	};

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Init(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 爆発演出
	/// </summary>
	/// <param name="pos">発生位置</param>
	/// <param name="minMax">広がり値</param>
	/// <param name="volume">一回で出す量</param>
	/// <param name="scale">オブジェクトスケール</param>
	/// <param name="color">オブジェクトカラー</param>
	void SetAnyExp(const Vector3& pos, Vector2 velocityMinMax = { -1.0,1.0 }, size_t volume = 10, float scale = 1.0f, Vector4 color = { 1,1,1,1 });
	/// <param name="ParticlePreset">プリセット</param>
	void SetAnyExp(ParticlePreset preset);

private:
	std::list<std::unique_ptr<ObjectParticle>> objParticles_;

	// モデル
	Model* model_ = nullptr;

private:
	ObjParticleManager() = default;
	~ObjParticleManager() = default;
	ObjParticleManager(const ObjParticleManager&) = default;
	const ObjParticleManager& operator=(const ObjParticleManager&) = delete;
};