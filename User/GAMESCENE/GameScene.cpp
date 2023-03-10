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
	delete camera;
	delete sceneManager;
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

	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneManager = new SceneManager(dxCommon);
	sceneManager->SceneInitialize();	

}

/// <summary>
/// ���t���[������
/// </summary>
void GameScene::Update() {
	camera->Update();
	if (input->Pad_X_ButtonInput(RB)) {
		input->Pad_X_ShakeController(1.0f, 10);
	}
	sceneManager->SceneUpdate(input);

}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw() {
	sceneManager->SceneDraw();

}