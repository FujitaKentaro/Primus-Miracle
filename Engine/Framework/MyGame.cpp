#include "MyGame.h"


// ������
void MyGame::Initialize() {

	fps = new FPS;
	fbxManager = FbxManager::Create();

	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏������@
	input = new Input();
	input->Initialize(winApp);
	PadInput = new Pad_X_Input();

	postEffect = new PostEffect();
	postEffect->Initialize(dxCommon);
	postEffect->SetKernelSize(10);
	postEffect->SetRadialBlur(Vector2(winApp->window_width / 2, winApp->window_height / 2), 0.1, 1);
	postEffect->SetShadeNumber(2);

	// ImGui�̏�����
	imgui = new ImGuiManager();
	imgui->Initialize(winApp, dxCommon);

	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice(), dxCommon->GetCommandList());
	// FBX�ÓI������
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//���C�g�ÓI������
	LightGroup::StaticInitialize(dxCommon->GetDevice());

	//FPS�ς������Ƃ�
	fps->SetFrameRate(60);

	endRequest_ = false;

	////////////////////////////
	Framework::Initialize();

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input);


}
// �I��
void MyGame::Finalize() {

	delete gameScene;

	postEffect->Finalize();
	delete postEffect;

	////////////////////////

	Framework::Finalize();
}
// ���t���[���X�V
void MyGame::Update() {

	Framework::Update();

	// �Q�[���V�[���̖��t���[������
	gameScene->Update();

	if (input->KeyboardTrigger(DIK_0)) {
		postEffect->SetShadeNumber(0);
	}
	if (input->KeyboardTrigger(DIK_1)) {
		postEffect->SetShadeNumber(3);
	}

}
// �`��̃t���[�����[�N�̃|�X�g�G�t�F�N�g�̈����킩���
// �`��
void MyGame::Draw() {


	// �Q�[���V�[���̕`��
	postEffect->PreDrawScene(dxCommon->GetCommandList());
	gameScene->Draw();
	postEffect->PostDrawScene();

	///////////////////////////////////////
	//4.�`��R�}���h��������
	dxCommon->PreDraw();

	// �f���E�B���h�E�̕\���I��
	//ImGui::ShowDemoWindow();

	//�|�X�g�G�t�F�N�g�̕`��
	postEffect->Draw(dxCommon->GetCommandList());

	// Imgui��t�I��
	imgui->End();
	// Imgui�`��
	imgui->Draw();

	// �`��I��
	dxCommon->PostDraw();

	fps->FpsControlEnd();
	//4.�`��R�}���h�����܂�
}