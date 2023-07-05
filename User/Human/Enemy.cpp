#include "Enemy.h"

Enemy::Enemy() {

}
Enemy::~Enemy() {
	delete model_;
	delete weapon_;
}

///
void Enemy::Initialize() {
	isDead = false;
	nowTitle = false;
	model_ = Model::LoadFromOBJ("cube");

	object_ = Object3d::Create();
	object_->SetModel(model_);
	object_->Initialize();

	reticle = Object3d::Create();
	reticle->SetModel(model_);
	reticle->Initialize();
	weapon_ = new Assault();
	weapon_->Initialize();

	//当たり判定用
	SPHERE_COLISSION_NUM = 1;
	sphere.resize(SPHERE_COLISSION_NUM);
	spherePos.resize(SPHERE_COLISSION_NUM);
	//FbxO_.get()->isBonesWorldMatCalc = true;	// ボーンの行列を取得するか
	coliderPosTest_.resize(SPHERE_COLISSION_NUM);
	
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		sphere[i] = new SphereCollider;
		CollisionManager::GetInstance()->AddCollider(sphere[i]);
		spherePos[i] = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->SetBasisPos(&spherePos[i]);
		sphere[i]->SetRadius(8.0f);
		sphere[i]->Update();
		sphere[i]->SetAttribute(COLLISION_ATTR_ENEMIES);
		////test
		//coliderPosTest_[i] = Object3d::Create();
		//coliderPosTest_[i]->SetModel(hpModel_.get());
		//coliderPosTest_[i]->SetPosition(sphere[i]->center);
		//coliderPosTest_[i]->SetScale({ sphere[i]->GetRadius(),sphere[i]->GetRadius() ,sphere[i]->GetRadius() });
		//coliderPosTest_[i]->SetRotate({ 0,0,0 });
		//coliderPosTest_[i]->Update();
	}
}

///
void Enemy::Update(Input* input, bool isTitle) {
	assert(input);
	object_->Update();
	if (input->KeyboardPush(DIK_SPACE)) {
		weapon_->Shot(object_->wtf, reticle->wtf,0);
	}
	if (!isTitle) {
		weapon_->Update(input, isSlow);
	}
	for (int i = 0; i < SPHERE_COLISSION_NUM; i++) {
		spherePos[i] = Affin::GetWorldTrans(object_->wtf.matWorld);
		sphere[i]->Update();
		/*if (sphere[i]->GetIsHit() == true && player_->GetIsAtkCollide() == true){

		 }*/

	}
}

///
void Enemy::Draw(DirectXCommon* dxCommon) {

	if (!isDead) {
		Object3d::PreDraw(dxCommon->GetCommandList());
		object_->Draw();
		if (nowTitle) {
			reticle->Draw();
		}
		Object3d::PostDraw();
		if (nowTitle) {
			weapon_->Draw(dxCommon);
		}
	}
}

/// リセットを行う
void Enemy::Reset() {

}