#pragma once
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ParticleManager.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Camera.h"

class SceneManager;

// �V�[���Ǘ��̂��߂̊��N���X
// (�������N���X)

class IScene
{
protected:

	SceneManager* _controller;

public:

	IScene();
	virtual ~IScene();

	//virtual Scene Create(SceneManager& controller) = 0;
	/// �V�[���̍X�V���s��
	virtual void Initialize(DirectXCommon* dxCommon,Camera* _camera) = 0;

	/// �V�[���̍X�V���s��
	virtual void Update(Input* input, Camera* _camera) = 0;

	/// �V�[���̕`����s��
	virtual void Draw(DirectXCommon* dxCommon) = 0;

};

