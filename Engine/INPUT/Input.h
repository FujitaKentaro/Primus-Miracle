#pragma once
#include "WinApp.h"

#include "Keyboard_Input.h"
#include "PadInput.h"



// ����
class Input
{
public:
	// namespace
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // �����o�֐�
	// ������
	void Initialize(WinApp* winApp);

	// �X�V
	void Update();
#pragma region �L�[�{�[�h�p�֐�

	/// <summary>
	/// �L�[�̉������`�F�b�N
	/// </summary>
	/// <param name = "keyNumber">�L�[�ԍ�(DIK_0 ��)</param>
	/// <returns>������Ă��邩</returns>
	bool KeyboardPush(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// </param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <reutrns>�g���K�[��</params>
	bool KeyboardTrigger(BYTE keyNumber);

	/// <summary>
	/// �L�[�̃g���K�[���`�F�b�N
	/// </summary>
	/// </param name="keyNumber">�L�[�ԍ�( DIK_0 ��)</param>
	/// <reutrns>�����ꂽ��</params>
	bool KeyboardRelease(BYTE keyNumber);

#pragma endregion �L�[�{�[�h�p�֐�

#pragma region Xbox Pad�p�֐�

	/// <summary>
	/// �R���g���[���[�{�^���̃g���K�[����
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool Pad_X_ButtonTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̃g���K�[����
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool Pad_X_StickTrigger(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate);

	/// <summary>
	/// �R���g���[���[�{�^���̓���
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool Pad_X_ButtonInput(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̓���
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔�</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�|�������ǂ���</returns>
	bool Pad_X_StickInput(ControllerStick stickInput, const float& deadRange, const Vector2& deadRate);

	/// <summary>
	/// �R���g���[���[�{�^���̗������u��
	/// </summary>
	/// <param name="button">�`�F�b�N�������{�^��</param>
	/// <returns>��������</returns>
	bool Pad_X_ButtonOffTrigger(ControllerButton button);

	/// <summary>
	/// �R���g���[���[�X�e�B�b�N�̗������u��
	/// </summary>
	/// <param name="stickInput">�R���g���[���[�X�e�B�b�N����</param>
	/// <param name="deadRange">�f�b�h�]�[���͈̔͏����l0.3f</param>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>��������</returns>
	bool Pad_X_StickOffTrigger(ControllerStick stickInput, const float& deadRang, const Vector2& deadRate);


	/// <summary>
	/// �R���g���[���[�̍��X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�x�N�g��</returns>
	Vector2 Pad_X_GetLeftStickVec(const Vector2& deadRate);

	/// <summary>
	/// �R���g���[���[�̉E�X�e�B�b�N�̃x�N�g��
	/// </summary>
	/// <param name="deadRate">�f�b�h�]�[������̓x���������l1.0f</param>
	/// <returns>�x�N�g��</returns>
	Vector2 Pad_X_GetRightStickVec(const Vector2& deadRate);

	/// <summary>
	/// �R���g���[���[��U��������
	/// </summary>
	/// <param name="power">�U���̋���0.0f�`1.0f</param>
	/// <param name="span">�U���̎��ԃt���[��</param>
	void Pad_X_ShakeController(const float& power, const int& span);

#pragma endregion Xbox Pad�p�֐�

private: // �����o�ϐ�
	
	Keyboard_Input* keybord_;
	Pad_X_Input* Xpad_;

	
};