#pragma once

#include "DirectXCommon.h"
#include <string>
#include "Input.h"
#include "SpriteCommon.h"
#include "SceneManager.h"
#include "SceneObjects.h"
#include "Affin.h"
#include "Camera.h"

#include "JsonLoader.h"


/// <summary>
/// �Q�[���V�[��
/// </summary>
class GameScene
{
private: // �ÓI�����o�ϐ�
	//static const int debugTextTexNumber = 0;

public: // �����o�֐�

	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

public:

	
private: // �����o�ϐ� (�Œ�)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Camera* camera = nullptr;
	SceneManager* sceneManager = nullptr;
	std::unique_ptr<SceneObjects> sceneObjects;

	LevelData* leveData = nullptr;
	Model* modelcube = nullptr;
	Model* modelREX = nullptr;

	std::map<std::string, Model*> models;
	std::vector<Object3d*> JsonObjects;


private:	//�����o�ϐ�
	Transform cam_TF;
	Vector3 eye = { 0.0f, 10.0f, -10.0f };
	Vector3 tar = { 0.0f, 0.0f, 0.0f };


};

