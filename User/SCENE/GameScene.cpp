#include "GameScene.h"

/// <summary>
	/// �R���X�g�N���^
	/// </summary>
GameScene::GameScene() {

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene() {


	//�I�[�f�B�I���
	//audio->Finalize();
	//delete audio;
	delete spriteCommon;
	delete sprite;
	delete camera;

	delete skydome, skydomeMD;

	delete particleManager;
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input){
	// null�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);


	skydomeMD = Model::LoadFromOBJ("skydome");

	skydome = Object3d::Create();

	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 1000, 1000, 1000 });
	skydome->Update();
	

	sprite = new Sprite();

	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition(spritePOS);
	sprite->SetSize(Vector2{ WinApp::window_width/3,WinApp::window_height/3 });

	spriteCommon->LoadTexture(0, "inu.png");
	sprite->SetTextureIndex(0);

	// �p�[�e�B�N������
	particleManager = ParticleManager::Create();
	particleManager->LoadTexture("1.png");
	particleManager->Update();
}

/// <summary>
/// ���t���[������
/// </summary>
void GameScene::Update() {
	camera->Update();
	particleManager->Update();

	skydome->Update();



	// �p�[�e�B�N���N��(������)
	{
		if (input->TriggerKey(DIK_P)) {

			//�p�[�e�B�N���͈�
			for (int j = 0; j < 50; j++) {
				//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
				const float rnd_pos = 0.03f;
				//const float rnd_posX = 1.0f;
				Vector3 pos{};
				pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z +=( (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f)+10;

				//���x
				//X,Y,Z�S��[-0.05f,+0.05f]�Ń����_���ɕ��z
				const float rnd_vel = 0.5f;
				Vector3 vel{};
				vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
				//�d�͂Ɍ����Ă�Y�̂�[-0.001f,0]�Ń����_���ɕ��z
				const float rnd_acc = -0.01f;
				const float rnd_acc_v = -0.01f;
				Vector3 acc{};
				acc.x = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				acc.y = ((float)rand() / RAND_MAX * rnd_acc) * ((float)rand() / RAND_MAX * rnd_acc_v);
				//acc.z = (float)rand() / RAND_MAX * rnd_acc;

				//�ǉ�
				particleManager->Add(50, pos, vel, acc, 1.0f, 0.0f);
			}
		}
	}
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw() {

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());
	/// <summary>
	/// 3D�I�u�W�F�N�g�̕`��
	/// ������3D�I�u�W�F�N�g�̕`�揈����ǉ��ł���
	/// <summary>
	
	skydome->Draw();
	
	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();

	// 3D�I�u�W�F�N�g�`��O����
	ParticleManager::PreDraw(dxCommon->GetCommandList());


	//// 3D�I�u�N�W�F�N�g�̕`��
	particleManager->Draw();

	// 3D�I�u�W�F�N�g�`��㏈��
	ParticleManager::PostDraw();

	sprite->Draw();
}