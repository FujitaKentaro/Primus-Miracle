#include "SceneManager.h"
#include "Input.h"
#include <cassert>
#include "DirectXCommon.h"
#include "Camera.h"

// �V�[���̃C���N���[�h
#include "SceneIntegrate.h"


SceneManager::SceneManager(DirectXCommon* dxCommon, Camera* camera) {
	_dxCommon = dxCommon;
	_scene.reset(new TitleScene(&*this));
	_camera = camera;


}
SceneManager::~SceneManager() {

}
void SceneManager::ObjectInitialize() {

	//�X�v���C�g������
	//spriteCommon_ = std::make_unique<SpriteCommon>();
	//spriteCommon_->Initialize(_dxCommon);
	//spriteCommon_->LoadTexture(1, "gamen.png");
	//spriteCommon_->LoadTexture(2, "title.png");

	audio = std::make_unique<Audio>();
	audio->Initialize();
	// fbx �e�X�g
	{
		//FBX	(�e�X�g)
		// �f�o�C�X���Z�b�g
		FBXObject3d::SetDevice(_dxCommon->GetDevice());
		// �O���t�B�b�N�X�p�C�v���C������
		FBXObject3d::CreateGraphicsPipeline();

		bossFbxM_.reset(FbxLoader::GetInstance()->LoadModelFromFile("boss_prot4"));
		bossFbxO_ = std::make_unique<FBXObject3d>();
		bossFbxO_->SetCamera(_camera);
		bossFbxO_->Initialize();
		bossFbxO_->SetModel(bossFbxM_.get());
		bossFbxO_->SetPosition({ 0,0,10 });
		bossFbxO_->SetScale({ 0.5,0.5,0.5 });
		bossFbxO_->PlayAnimation(1);
		bossFbxO_->AnimIsRotateChange();
	}
	
	////�p�[�e�B�N���̃Z�b�g
	//particleManager_ = std::make_unique<ParticleManager>();
	//particleManager_.get()->Initialize();
	////�p�[�e�B�N���p�f��
	//particleManager_->LoadTexture("effect.png");
	//particleManager_->Update();
	
}

void SceneManager::SceneInitialize() {
	_scene.get()->Initialize(_dxCommon, _camera);

}

void SceneManager::SceneUpdate(Input* input) {
	_scene.get()->Update(input, _camera);

}

void SceneManager::SceneDraw() {
	_scene.get()->Draw(_dxCommon);

}

void SceneManager::ChangeScene(IScene* scene) {
	_scene.reset(scene);
	SceneInitialize();

}