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
	//ParticleManager::SetCamera(camera);
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
}

/// <summary>
/// ���t���[������
/// </summary>
void GameScene::Update() {
	skydome->Update();




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

	sprite->Draw();
}