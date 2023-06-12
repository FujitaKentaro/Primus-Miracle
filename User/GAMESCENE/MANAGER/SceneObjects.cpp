#include "SceneObjects.h"

SceneObjects::SceneObjects(DirectXCommon*DXCommon,Camera* camera) {
	_dxCommon = DXCommon;
	_camera = camera;
}
SceneObjects::~SceneObjects() {

}
void SceneObjects::Initialize() {

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

	{
		human_ = std::make_unique<Player>();
		human_->Initialize();
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