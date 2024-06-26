#include "Framework.h"


void Framework::Run() {
	Initialize();
	while (true)
	{
		Update();
		if (IsEndRequest()) {
			break;
		}
		if (input->KeyboardPush(DIK_ESCAPE)) {
			break;
		}
		Draw();
	}

	Finalize();

}


void Framework::Initialize() {

	fps = new FPS();

	//windowsAPIの初期化
	winApp = new WinApp();
	winApp->Initialize();

	dxCommon = new DirectXCommon();
	dxCommon->Initialize(winApp);

	//入力の初期化　
	input = &Input::get_instance();
	input->Initialize(winApp);

	//FPS変えたいとき
	fps->SetFrameRate(60);

	imgui = new ImGuiManager();
	imgui->Initialize(winApp, dxCommon);

	audio = Audio::get_instance();
	audio->Initialize();

	endRequest_ = false;
}

void Framework::Finalize() {

	////// メモリりーく
	//ID3D12DebugDevice* debugInterface;
	//if (SUCCEEDED(dxCommon->GetDevice()->QueryInterface(&debugInterface))) {
	//	debugInterface->ReportLiveDeviceObjects(D3D12_RLDO_DETAIL | D3D12_RLDO_IGNORE_INTERNAL);
	//	debugInterface->Release();
	//}

	audio->Finalize();

	imgui->Finalize();
	//WindowsAPIの終了処理
	winApp->Finalize();
	delete imgui;

	//入力開放
	input->Finalize();
	//WindowsAPI開放
	delete winApp;
	delete dxCommon;
	delete fps;
}

void Framework::Update() {

#pragma region ウィンドウメッセージ処理

	//アプリケーションが終わる時にmessageがWM_QUITになる
	if (winApp->ProcessMessage()) {
		endRequest_ = true;
	}
	winApp->Update();// カーソルの制限用
	fps->FpsControlBegin();

#pragma endregion

	//入力の更新
	input->Update();
	// Imgui受付開始
	imgui->Begin();

}