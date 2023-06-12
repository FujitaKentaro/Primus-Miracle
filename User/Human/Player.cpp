#include "Player.h"


Player::Player() {

}
Player::~Player() {
	delete model_;
}

/// �V�[���̍X�V���s��
void Player::Initialize() {
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

}

/// �V�[���̍X�V���s��
void Player::Update(Input* input) {

	object_->Update();
}

/// �V�[���̕`����s��
void Player::Draw(DirectXCommon* dxCommon) {
	Object3d::PreDraw(dxCommon->GetCommandList());
	object_->Draw();
	Object3d::PostDraw();
}