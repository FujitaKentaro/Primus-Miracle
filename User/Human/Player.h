#pragma once
#include "Human.h"


class Player :
    public Human
{
public:
	Player();
	~Player()override;


	/// �V�[���̍X�V���s��
	void Initialize()override;

	/// �V�[���̍X�V���s��
	void Update(Input* input)override;

	/// �V�[���̕`����s��
	void Draw(DirectXCommon* dxCommon)override;

	void Move(Input* input);

private:
	Model* model_;
	Object3d* object_;
	//�ړ����x
	const float kMoveSpeed_ = 0.5;
	//�ړ��x�N�g��
	Vector3 velocity_;
	Vector3 faceAngle_;


};

