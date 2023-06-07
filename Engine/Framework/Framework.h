#pragma once

#include "WinApp.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "FPS.h"
#include "ImGuiManager.h"
#include "PadInput.h"
#include <imgui.h>

class Framework
{
public: // �����o�֐�

	virtual ~Framework() = default;

	virtual void Initialize();

	virtual void Finalize();

	virtual void Update();

	virtual void Draw() = 0;

	virtual bool IsEndRequest() { return endRequest_; }

	void Run();

protected:
	bool endRequest_;

	//�|�C���^
	WinApp* winApp = nullptr;
	DirectXCommon* dxCommon = nullptr;
	FPS* fps = nullptr;
	Input* input = nullptr;
	Pad_X_Input* PadInput = nullptr;
	ImGuiManager* imgui = nullptr;

};

