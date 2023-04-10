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

	delete obj2, obj2MD;
	delete obj, model;
}

void TitleScene::Initialize(DirectXCommon* dxCommon) {

	//�p�[�e�B�N���̃Z�b�g
	particleManager_ = std::make_unique<ParticleManager>();
	particleManager_.get()->Initialize();
	//�p�[�e�B�N���p�f��
	particleManager_->LoadTexture("inu.png");
	particleManager_->Update();
	//�p�[�e�B�N���̃Z�b�g
	particleManager2_ = std::make_unique<ParticleManager>();
	particleManager2_.get()->Initialize();
	//�p�[�e�B�N���p�f��
	particleManager2_->LoadTexture("1.png");
	particleManager2_->Update();

	//�X�v���C�g���ʕ����̏�����
	spriteCommon = new SpriteCommon;
	spriteCommon->Initialize(dxCommon);

	sprite = new Sprite();
	Vector2 spritePOS = sprite->GetPosition();
	sprite->Initialize(spriteCommon);
	sprite->SetPozition({0,0});
	sprite->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });


	sprite2 = new Sprite();
	Vector2 spritePOS2 = Vector2{ WinApp::window_width / 2,WinApp::window_height / 2 };
	sprite2->Initialize(spriteCommon);
	sprite2->SetPozition(spritePOS2);
	sprite2->SetSize(Vector2{ WinApp::window_width / 3,WinApp::window_height / 3 });

	spriteCommon->LoadTexture(0, "title.png");
	sprite->SetTextureIndex(0);
	spriteCommon->LoadTexture(1, "end.png");
	sprite2->SetTextureIndex(1);
	

	
	obj2MD = Model::LoadFromOBJ("ene");
	model = Model::LoadFromOBJ("REX");

	obj2 = Object3d::Create();
	obj2->SetModel(obj2MD);
	obj2->wtf.scale = (Vector3{ 0.8, 0.8, 0.8 });
	obj2->Update();

	obj = Object3d::Create();
	obj->SetModel(model);
	obj->wtf.position = (Vector3{ 5, 1, 5 });
	obj->wtf.scale = (Vector3{ 0.1, 0.1, 0.1 });
	obj->Update();

}

void TitleScene::Update(Input* input) {

	obj->Update();
	obj2->Update();

	particleManager_->Update();
	particleManager2_->Update();

	// �p�[�e�B�N���N��
	{
		if (input->KeyboardTrigger(DIK_E)) {
			particleManager_->SetTransform(obj->wtf);
			particleManager2_->SetTransform(obj2->wtf);

			//�ǉ�
			particleManager_->RandParticle();
			particleManager2_->RandParticle();
		}
	}

	if (input->KeyboardTrigger(DIK_SPACE) || input->Pad_X_ButtonTrigger(LB)) {
		//_controller->ChangeScene(new EndScene(_controller));		
	}
}

void TitleScene::Draw(DirectXCommon* dxCommon) {

	
	sprite->Draw();
	sprite2->Draw();
	


	//3D�I�u�W�F�N�g�`��O����
	Object3d::PreDraw(dxCommon->GetCommandList());

	obj2->Draw();
	obj->Draw();

	//3D�I�u�W�F�N�g�`��㏈��
	Object3d::PostDraw();
	
	particleManager_->Draw();
	particleManager2_->Draw();
}