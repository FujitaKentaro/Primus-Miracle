#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"

// Imgui �̊Ǘ�
class ImGuiManager
{
public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(WinApp* winApp,DirectXCommon* dxCommon);

private:

	// SRV�p�f�X�N���v�^�[�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap_;

public:



};

