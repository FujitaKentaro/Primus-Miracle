#include "TitleScene.h"
#include "SceneManager.h"

#include "EndScene.h"



TitleScene::TitleScene(SceneManager* controller) {
	_controller = controller;
}
TitleScene::~TitleScene() {
	delete spriteCommon;
	delete sprite;
	delete sprite2;

	delete particleManager;
	delete particleManager2;

	delete skydome, skydomeMD;
	delete obj, model;
}

void TitleScene::Initialize(DirectXCommon* dxCommon) {

	// �p�[�e�B�N������
	particleManager = ParticleManager::Create();
	particleManager->LoadTexture("1.png");
	particleManager->Update();
	particleManager2 = ParticleManager::Create();
	particleManager2->LoadTexture("1_2.png");
	particleManager2->Update();

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	sprite = new Sprite();

	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition(spritePOS);
	sprite->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });

	spriteCommon->LoadTexture(0, "title.png");
	sprite->SetTextureIndex(0);

	sprite2 = new Sprite();

	Vector2 spritePOS2 = Vector2{ WinApp::window_width / 2,WinApp::window_height / 2 };
	sprite2->Initialize(spriteCommon);
	sprite2->SetPozition(spritePOS2);
	sprite2->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });

	spriteCommon->LoadTexture(1, "end.png");
	sprite2->SetTextureIndex(1);

	
	skydomeMD = Model::LoadFromOBJ("skydome");
	skydome = Object3d::Create();
	skydome->SetModel(skydomeMD);
	skydome->wtf.scale = (Vector3{ 10000, 10000, 10000 });
	skydome->Update();

	model = Model::LoadFromOBJ("skydome");
	obj = Object3d::Create();
	obj->SetModel(model);
	obj->wtf.scale = (Vector3{ 10, 10, 10 });
	obj->Update();

}

void TitleScene::Update(Input* input) {





	obj->Update();
	skydome->Update();

	particleManager->Update();
	particleManager2->Update();

	// �p�[�e�B�N���N��( P ����)
	{
		if (input->KeyboardTrigger(DIK_P) || input->Pad_X_ButtonTrigger(B)) {
			//�p�[�e�B�N���͈�
			for (int j = 0; j < 50; j++) {
				//X,Y,Z�S��[-5.0f,+5.0f]�Ń����_���ɕ��z
				const float rnd_pos = 0.03f;
				//const float rnd_posX = 1.0f;
				Vector3 pos{};
				pos.x += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.y += (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
				pos.z += ((float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f) + 10;

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
				particleManager2->Add(100, pos, vel + vel, acc, 1.0f, 0.0f);
			}
		}
	}

	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		//_controller->ChangeScene(new EndScene(_controller));
		
	}
}

void TitleScene::Draw(DirectXCommon* dxCommon) {
	sprite->Draw();
	sprite2->Draw();

	particleManager->Draw();
	particleManager2->Draw();

	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	skydome->Draw();

	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
}