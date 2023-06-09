#include "Framework.h"


void Framework::Run() {
	Initialize();
	while (true)
	{
		Update();
		if (IsEndRequest()) {
			break;
		}
		Draw();
	}

	Finalize();

}


void Framework::Initialize() {

	fps = new FPS();

	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏������@
	input = new Input();
	input->Initialize(winApp);
	PadInput = new Pad_X_Input();

	//FPS�ς������Ƃ�
	fps->SetFrameRate(60);

	endRequest_ = false;
}

void Framework::Finalize() {

	imgui->Finalize();
	//WindowsAPI�̏I������
	winApp->Finalize();
	delete imgui;

	//���͊J��
	delete input;
	delete PadInput;
	//WindowsAPI�J��
	delete winApp;
	delete dxCommon;
	delete fps;
}

void Framework::Update() {

#pragma region �E�B���h�E���b�Z�[�W����

	//�A�v���P�[�V�������I��鎞��message��WM_QUIT�ɂȂ�
	if (winApp->ProcessMessage()) {
		Framework::endRequest_ = true;
	}

	fps->FpsControlBegin();

#pragma endregion

	//���͂̍X�V
	input->Update();
	PadInput->Update();
	// Imgui��t�J�n
	imgui->Begin();

}