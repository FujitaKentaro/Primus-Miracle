#pragma once
/**
 * @file GAME1Scene.h
 * @brief ゲーム実行１ステージ目
 */
#include "IScene.h"

#include "JsonLoader.h"
#include "SceneIntegrate.h"


class GAME1Scene :
    public IScene
{
public:
	GAME1Scene();
	~GAME1Scene() override;

	//void Cleate(SceneManager& manager) override;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="input">入力管理クラス</param>
	void Update(Input* input) override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;
private:
	void TutorialInitialize();
	void TutorialUpdate();
	void TutrialDraw(bool isTutrial);
private:
	bool startTime_ = false;
	bool stageClear = false;
	bool stageFailed = false;
	bool isDrawSP_ = true;

	// カメラ座標
	Vector3 camposEye = { 0.0f,90.0f,-10.0001f };
	Vector3 camposTar = { 0,0,0 };
	float forcalLengs = 30.0f;


	std::unique_ptr <Sprite> infoSP_;
	Vector2 infoPos = { 20.0f,10.0f };
	uint32_t infoNum_ = 60;
	uint32_t infoCountTime_ = 0;
	uint32_t nowInfoNum_,oldInfoNum_;
	bool isInfoBarrier, isInfoSHOT, isInfoSLOW, isInfoDUSH, isInfoWEPC,isAllFalse;
	bool isTimeCount;
};

