#include "PadInput.h"
#include <winerror.h>
//#include <intsafe.h>

Pad_X_Input::Pad_X_Input() {

}
Pad_X_Input::~Pad_X_Input() {

}

bool Pad_X_Input::StickInDeadZone(Vector2& Thumb, const Vector2& DeadRate)
{
	bool x = false;
	bool y = false;

	if ((Thumb.x < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x
		&& Thumb.x > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.x))
	{
		Thumb.x = 0.0f;
		x = true;
	}
	if ((Thumb.y < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y
		&& Thumb.y > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE * DeadRate.y))
	{
		Thumb.y = 0.0f;
		y = true;
	}

	if (x && y)
	{
		return true;
	}

	return false;
}

void Pad_X_Input::Update()
{
	oldXinputState = xinputState;
	ZeroMemory(&xinputState, sizeof(XINPUT_STATE));

	//�R���g���[���[�擾
	DWORD dwResult = XInputGetState(0, &xinputState);

	if (dwResult == ERROR_SUCCESS)
	{
		//�R���g���[���[���ڑ�����Ă���
		if (0 < shakeTimer)
		{
			shakeTimer--;
			XINPUT_VIBRATION vibration;
			ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

			if (shakeTimer == 0)
			{
				vibration.wLeftMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(0.0f); // use any value between 0-65535 here
			}
			else
			{
				vibration.wLeftMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
				vibration.wRightMotorSpeed = static_cast<WORD>(65535.0f * shakePower); // use any value between 0-65535 here
			}

			XInputSetState(dwResult, &vibration);
		}
	}
	else
	{
		//�R���g���[���[���ڑ�����Ă��Ȃ�
	}
}

bool Pad_X_Input::ButtonTrigger(ControllerButton button)
{
	//�g���K�[
	if (button == LT)
	{
		return oldXinputState.Gamepad.bLeftTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonInput(button);
	}
	else if (button == RT)
	{
		return oldXinputState.Gamepad.bRightTrigger <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD && ButtonInput(button);
	}
	else
	{
		return !(oldXinputState.Gamepad.wButtons & button) && ButtonInput(button);
	}
}

bool Pad_X_Input::StickTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 oldVec;
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;
	if (isLeftStick)
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbLX, oldXinputState.Gamepad.sThumbLY);
		vec = Vector2(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbRX, oldXinputState.Gamepad.sThumbRY);
		vec = Vector2(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate))
	{
		return false;
	}

	if (StickInDeadZone(vec, deadRate))
	{
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP)
	{
		result = !(deadRange < (oldVec.y / STICK_INPUT_MAX)) && deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN)
	{
		result = !(oldVec.y / STICK_INPUT_MAX < -deadRange) && vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		result = !(deadRange < (oldVec.x / STICK_INPUT_MAX)) && deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT)
	{
		result = !(oldVec.x / STICK_INPUT_MAX < -deadRange) && vec.x / STICK_INPUT_MAX < -deadRange;
	}
	else
	{
		assert(0);
	}

	return result;
}

bool Pad_X_Input::ButtonInput(ControllerButton button)
{
	if (button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState.Gamepad.bLeftTrigger;
	}
	else if (button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < xinputState.Gamepad.bRightTrigger;
	}
	else
	{
		return xinputState.Gamepad.wButtons & button;
	}
}

bool Pad_X_Input::StickInput(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick)
	{
		vec = Vector2(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		vec = Vector2(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (StickInDeadZone(vec, deadRate))return false;

	if (stickInput % 4 == L_UP)
	{
		return deadRange < (vec.y / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_DOWN)
	{
		return  vec.y / STICK_INPUT_MAX < -deadRange;
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		return deadRange < (vec.x / STICK_INPUT_MAX);
	}
	else if (stickInput % 4 == L_LEFT)
	{
		return  vec.x / STICK_INPUT_MAX < -deadRange;
	}

	assert(0);
	return false;
}

bool Pad_X_Input::ButtonOffTrigger(ControllerButton button)
{
	//�g���K�[
	if (button == LT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState.Gamepad.bLeftTrigger && !ButtonInput(button);
	}
	else if (button == RT)
	{
		return XINPUT_GAMEPAD_TRIGGER_THRESHOLD < oldXinputState.Gamepad.bRightTrigger && !ButtonInput(button);
	}
	//�{�^��
	else
	{
		return (oldXinputState.Gamepad.wButtons & button) && !ButtonInput(button);
	}
}

bool Pad_X_Input::StickOffTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate)
{
	 Vector2 oldVec;
	 Vector2 vec;
	bool isLeftStick = stickInput <= L_RIGHT;

	if (isLeftStick)
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbLX, oldXinputState.Gamepad.sThumbLY);
		vec = Vector2(xinputState.Gamepad.sThumbLX, xinputState.Gamepad.sThumbLY);
	}
	else
	{
		oldVec = Vector2(oldXinputState.Gamepad.sThumbRX, oldXinputState.Gamepad.sThumbRY);
		vec = Vector2(xinputState.Gamepad.sThumbRX, xinputState.Gamepad.sThumbRY);
	}

	if (!StickInDeadZone(oldVec, deadRate))
	{
		return false;
	}

	if (StickInDeadZone(vec, deadRate))
	{
		return false;
	}

	bool result = false;

	if (stickInput % 4 == L_UP)
	{
		result = deadRange < (oldVec.y / STICK_INPUT_MAX) && !(deadRange < (vec.y / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_DOWN)
	{
		result = oldVec.y / STICK_INPUT_MAX < -deadRange && !(vec.y / STICK_INPUT_MAX < -deadRange);
	}
	else if (stickInput % 4 == L_RIGHT)
	{
		result = deadRange < (oldVec.x / STICK_INPUT_MAX) && !(deadRange < (vec.x / STICK_INPUT_MAX));
	}
	else if (stickInput % 4 == L_LEFT)
	{
		result = oldVec.x / STICK_INPUT_MAX < -deadRange && !(vec.x / STICK_INPUT_MAX < -deadRange);
	}
	else
	{
		assert(0);
	}

	return result;
}

 Vector2 Pad_X_Input::GetLeftStickVec(const Vector2& deadRate)
{

	Vector2 result(static_cast<float>(xinputState.Gamepad.sThumbLX), static_cast<float>(-xinputState.Gamepad.sThumbLY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;
}

 Vector2 Pad_X_Input::GetRightStickVec(const Vector2& deadRate)
{
	Vector2 result(static_cast<float>(xinputState.Gamepad.sThumbRX), static_cast<float>(-xinputState.Gamepad.sThumbRY));
	StickInDeadZone(result, deadRate);
	return result / STICK_INPUT_MAX;;
}

void Pad_X_Input::ShakeController(const float& power, const int& span)
{
	if (!(0 < power && power <= 1.0f))
	{
		assert(0);
	}

	shakePower = power;
	shakeTimer = span;
}






//-----------------------------------------
// direct input �̎c�[

/*
#include "PadInput.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

	//using namespace Microsoft::WRL;

void Pad_D_Input::Initialize(WinApp* winApp)
{
	this->winApp_ = winApp;

	HRESULT result;

	// DirectInput�̃C���X�^���X����
	//ComPtr<IDirectInput8> directInput = nullptr;
	result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
	assert(SUCCEEDED(result));


	// �L�[�{�[�h�f�o�C�X�̐���
	//ComPtr<IDirectInputDevice8> keyboard = nullptr;
	result = directInput->CreateDevice(GUID_Joystick, &D_Pad_, nullptr);
	assert(SUCCEEDED(result));

	// ���̓f�[�^�`���̃Z�b�g
	result = D_Pad_->SetDataFormat(&c_dfDIJoystick); // �W���`��
	assert(SUCCEEDED(result));

	// �r�����䃌�x���̃Z�b�g
	result = D_Pad_->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Pad_D_Input::Update()
{
	HRESULT result;

	// �O��̃L�[���͂�ێ�
	memcpy(keyPre, key, sizeof(key));

	// �L�[�{�[�h���̎擾�J�n
	result = D_Pad_->Acquire();

	// �S�L�[�̓��͏�Ԃ��擾����
	//BYTE key[256] = {};
	result = D_Pad_->GetDeviceState(sizeof(key), key);
}

bool Pad_D_Input::PushKey(BYTE keyNumber)
{
	// �w��L�[�������Ă����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	// �����ł͂Ȃ����false��Ԃ�
	return false;
}

bool Pad_D_Input::TriggerKey(BYTE keyNumber)
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
bool Pad_D_Input::ReleaseKey(BYTE keyNumber) {
	if (keyPre[keyNumber])
	{
		if (key[keyNumber]) {
			return false;
		}
		return true;
	}

	return false;
}
*/

