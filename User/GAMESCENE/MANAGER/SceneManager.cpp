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
		bossFbxO_->SetPosition({ 0,0,0 });
		bossFbxO_->SetScale({ 0.5,0.5,0.5 });
		bossFbxO_->PlayAnimation(1);
		bossFbxO_->AnimIsRotateChange();
	}
	
	//���C�g�̐���
	lightGroup = std::make_unique< LightGroup>();
	lightGroup->Initialize();

	lightGroup->SetDirLightActive(0, true);
	pointLightPos[0] = 0.0f;
	pointLightPos[1] = 5.0f;
	pointLightPos[2] = 0.0f;

		lightGroup->SetDirLightColor(0, Vector3(1, 1, 1));
		lightGroup->SetDirLightDir(0, Vector4(1, -1, 0, 0));

	//3D�I�u�W�F�N�g�Ƀ��C�g���Z�b�g
	Object3d::SetLight(lightGroup.get());
}

void SceneManager::SceneInitialize() {
	_scene.get()->Initialize(_dxCommon, _camera);

}

void SceneManager::SceneUpdate(Input* input) {
	lightGroup->Update();

	_scene.get()->Update(input, _camera);
}

void SceneManager::SceneDraw() {
	_scene.get()->Draw(_dxCommon);

}

void SceneManager::ChangeScene(IScene* scene) {
	_scene.reset(scene);
	SceneInitialize();

}