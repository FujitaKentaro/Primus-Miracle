#pragma once

#include "DirectXCommon.h"
#include "Input.h"
//#include "Audio.h"
//
//#include <string>
//#include <DirectXMath.h>
//
//#include "Object3d.h"
//#include "SpriteCommon.h"
//#include "Sprite.h"
//#include "Model.h"
//
//#include "Matrix4.h"
//#include "ConvertXM.h"
//#include "Transform.h"
//#include "DebugCamera.h"
//#include "FBX/FBXObject3d.h"
//#include "FBX/FbxLoader.h"
//#include "Particle/ParticleManager.h"


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
	
private: // �����o�ϐ�

};

