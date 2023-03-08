#include "Keyboard_Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

//using namespace Microsoft::WRL;

Keyboard_Input::Keyboard_Input(){}
Keyboard_Input::~Keyboard_Input(){}

void Keyboard_Input::Initialize(WinApp* winApp)
{
	this->winApp_ = winApp;

	HRESULT result;

	// DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	// �L�[�{�[�h�f�o�C�X�̐���
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = keyboard->SetDataFormat(&c_dfDIKeyboard); // �W���`��
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Keyboard_Input::Update()
{
	HRESULT result;

	// �O��̃L�[���͂�ێ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�{�[�h���̎擾�J�n
	result = keyboard->Acquire();

	// �S�L�[�̓��͏�Ԃ��擾����
	/*BYTE key[256] = {};*/
	result = keyboard->GetDeviceState(sizeof(key), key);
}

bool Keyboard_Input::PushKey(BYTE keyNumber)
{
	// �w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	// �����ł͂Ȃ����false��Ԃ�
	return false;
}

bool Keyboard_Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber])
	{
		if (keyPre[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}

/// <summary>
/// �L�[�̃g���K�[���`�F�b�N
/// </summary>
/// </param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
/// <reutrns>�����ꂽ��</params>
bool Keyboard_Input::ReleaseKey(BYTE keyNumber) {
	if (keyPre[keyNumber])
	{
		if (key[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}