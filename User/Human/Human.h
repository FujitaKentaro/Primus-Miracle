#pragma once
#include "Object3d.h"
#include "Transform.h"
#include "Affin.h"
#include "Input.h"

#include "DirectXCommon.h"

// ���N���X
class Human
{

protected:
	Input* input;

	bool Slow = false;
public:

	Human();
	virtual ~Human();

	/// �V�[���̍X�V���s��
	virtual void Initialize() = 0;

	/// �V�[���̍X�V���s��
	virtual void Update(Input* input) = 0;

	/// �V�[���̕`����s��
	virtual void Draw(DirectXCommon* dxCommon) = 0;

};

