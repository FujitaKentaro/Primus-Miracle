#pragma once
#include "IScene.h"

class TitleScene :public IScene
{
protected:
	SceneManager* _controller;

public:
	
	TitleScene(SceneManager* controller);
	~TitleScene() override;

	void Initialize(DirectXCommon* dxCommon) override;
	void Update(Input* input) override;
	void Draw(DirectXCommon* dxCommon) override;
private:


public:
	//�p�[�e�B�N���N���X�̏����� 
	ParticleManager* particleManager = nullptr;
	ParticleManager_2* particleManager2 = nullptr;


	SpriteCommon* spriteCommon = nullptr;
	Sprite* sprite = nullptr;
	Sprite* sprite2 = nullptr;

	Object3d* obj = nullptr;
	Model* model = nullptr;

	Object3d* obj2 = nullptr;
	Model* obj2MD = nullptr;

};