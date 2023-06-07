#pragma once

#include "GameScene.h"
#include "PostEffect.h"
#include "fbxsdk.h"
#include "Framework.h"

class MyGame : public Framework
{
public:	// �����o�֐�

	// ������
	void Initialize() override;
	// �I��
	void Finalize() override;
	// ���t���[���X�V
	void Update() override;
	// �`��
	void Draw() override;

protected:

	//�|�C���^
	FbxManager* fbxManager = nullptr;
	GameScene* gameScene = nullptr;
	PostEffect* postEffect = nullptr;
};

