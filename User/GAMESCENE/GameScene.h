#pragma once

#include "DirectXCommon.h"
#include <string>
#include "Input.h"
#include "Object3d.h"
#include "SpriteCommon.h"
#include "Sprite.h"
#include "Model.h"
#include "Audio.h"
#include "SceneManager.h"
#include "ParticleManager.h"

#include "Matrix4.h"
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
	//�����~�߂�֐�
	IXAudio2SourceVoice* pSourceVoice[10] = { 0 };

	
private: // �����o�ϐ� (�Œ�)
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	SpriteCommon* spriteCommon = nullptr;
	Camera* camera = nullptr;
	Audio* audio = nullptr;
	SceneManager* sceneManager = nullptr;

	LevelData* leveData = nullptr;

	Model* modelcube = nullptr;
	Model* modelREX = nullptr;

	std::map<std::string, Model*> models;
	std::vector<Object3d*> objects;


private:	//�����o�ϐ�
	Transform cam_TF;
	Vector3 eye = { 0.0f, 10.0f, -10.0f };
	Vector3 tar = { 0.0f, 0.0f, 0.0f };


};

