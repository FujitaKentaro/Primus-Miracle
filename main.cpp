
#include "FPS.h"
#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "GameScene.h"



int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

#pragma region WindowsAPI����������


	//�|�C���^
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = new FPS;
	Input* input = nullptr;
	GameScene* gameScene = nullptr;

	//windowsAPI�̏�����
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//���͂̏������@
	input = new Input();
	input->Initialize(winApp);





#pragma endregion

#pragma region DirectX����������

	//// 3D�I�u�W�F�N�g�ÓI������
	//Object3d::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	////�p�[�e�B�N���ÓI������
	//ParticleManager::StaticInitialize(dxCommon->GetDevice(), WinApp::window_width, WinApp::window_height);
	//// FBX�֘A�ÓI������
	//FbxLoader::GetInstance()->Initialize(dxCommon->GetDevice());

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
		if (input->PushKey(DIK_ESCAPE)) {
			break;
		}


		fps->FpsControlBegin();

#pragma endregion

#pragma region DirectX���t���[������
		/////////////////////////////////////////////////////
		//----------DireceX���t���[�������@��������------------//
		///////////////////////////////////////////////////

		//���͂̍X�V
		input->Update();
		// �Q�[���V�[���̖��t���[������
		gameScene->Update();

		//////////////////////////////////////////////
		//-------DireceX���t���[�������@�����܂�--------//
		////////////////////////////////////////////

#pragma endregion

#pragma region �O���t�B�b�N�X�R�}���h

		//4.�`��R�}���h��������
		dxCommon->PreDraw();
		// �Q�[���V�[���̕`��
		gameScene->Draw();
		// �`��I��
		dxCommon->PostDraw();

		fps->FpsControlEnd();
		//4.�`��R�}���h�����܂�

#pragma endregion

#pragma region ��ʓ���ւ�

#pragma endregion
	}
#pragma region  WindowsAPI��n��

	delete gameScene;
	//WindowsAPI�̏I������
	winApp->Finalize();

	//���͊J��
	delete input;
	//WindowsAPI�J��
	delete winApp;
	delete dxCommon;

	delete fps;

#pragma endregion
	return 0;
}