
#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "ImGuiManager.h"
#include <imgui.h>


#include "GameScene.h"
#include "PadInput.h"
#include "PostEffect.h"

#include "fbxsdk.h"



int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	FbxManager* fbxManager = FbxManager::Create();
#pragma region WindowsAPI����������


	//�|�C���^
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
	Pad_X_Input* PadInput = nullptr;
	GameScene* gameScene = nullptr;
	PostEffect* postEffect = nullptr;

	ImGuiManager* imgui = nullptr;

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
	postEffect->SetShadeNumber(1);

	// ImGui�̏�����
	imgui = new ImGuiManager();
	imgui->Initialize(winApp,dxCommon);

#pragma endregion

#pragma region DirectX����������
	// 3D�I�u�W�F�N�g�ÓI������
	Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//�p�[�e�B�N���ÓI������
	ParticleManager::StaticInitialize(dxCommon->GetDevice(),dxCommon->GetCommandList());
	// FBX�ÓI������
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());
	//���C�g�ÓI������
	LightGroup::StaticInitialize(dxCommon->GetDevice());

#pragma endregion

#pragma region �`�揉��������

	////////////////////////////
	//------�����ǂݍ���--------//
	///////////////////////////

	// �Q�[���V�[���̏�����
	gameScene = new GameScene();
	gameScene->Initialize(dxCommon, input);
	

	//FPS�ς������Ƃ�
	fps->SetFrameRate(60);

#pragma endregion
	//�Q�[�����[�v
	while (true) {
#pragma region �E�B���h�E���b�Z�[�W����

		//�A�v���P�[�V�������I��鎞��message��WM_QUIT�ɂȂ�
		if (winApp->ProcessMessage()) {
			break;
		}
		/*if (input->KeyboardPush(DIK_ESCAPE)) {
			break;
		}*/


		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX���t���[������
		/////////////////////////////////////////////////////
		//----------DireceX���t���[�������@��������------------//
		///////////////////////////////////////////////////

		//���͂̍X�V
		input->Update();
		PadInput->Update();
		// Imgui��t�J�n
		imgui->Begin();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();		

		//////////////////////////////////////////////
		//-------DireceX���t���[�������@�����܂�--------//
		////////////////////////////////////////////

#pragma endregion

#pragma region �O���t�B�b�N�X�R�}���h

		// �Q�[���V�[���̕`��
		postEffect->PreDrawScene(dxCommon->GetCommandList());
		gameScene->Draw();
		postEffect->PostDrawScene();

		//4.�`��R�}���h��������
		dxCommon->PreDraw();
		
		// �f���E�B���h�E�̕\���I��
		ImGui::ShowDemoWindow();


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

#pragma endregion

#pragma region ��ʓ���ւ�

#pragma endregion
	}
#pragma region  WindowsAPI��n��

	/*ID3D12DebugDevice* debugInterface;
	if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(&debugInterface))) {
		debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
		debugInterface->Release();
	}*/

	delete gameScene;

	postEffect->Finalize();
	delete postEffect;

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
	
#pragma endregion
	return 0;
}