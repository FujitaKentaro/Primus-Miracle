#pragma once
#include "SceneManager.h"
#include "SceneObjects.h"
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
	SceneObjects* _objects;

public:

	IScene();
	virtual ~IScene();

	//virtual Scene Create(SceneManager& controller) = 0;
	/// �V�[���̍X�V���s��
	virtual void Initialize() = 0;

	/// �V�[���̍X�V���s��
	virtual void Update(Input* input) = 0;

	/// �V�[���̕`����s��
	virtual void Draw() = 0;

};

