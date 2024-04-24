#include "Tutorial.h"

/**
 * @file Tutorial.cpp
 * @brief ゲーム実行 チュートリアルステージ
 */
#include "Tutorial.h"
#include "SceneManager.h"

Tutorial::Tutorial() {
}

Tutorial::~Tutorial() {
	BulletManager::GetInstance()->AllClearBullet();
	_objects->walls.clear();
	_objects->enemys.clear();
	_objects->boss.clear();
	_objects->damageRedAlpha_ = 0;
	_objects->player->Reset();
	_objects->SlowReset();
	_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / (float)_objects->player->GetMAXHP()));
	_objects->plDamageRed_->Update();
}

void Tutorial::Initialize() {
	_objects->SlowReset();
	_objects->player->Reset();
	_objects->player->MatUpdate();
	startTime_ = true;
	stageClear = false;
	stageFailed = false;
	SpriteInitialize();
	{
		_manager->_camera->SetEye(camposEye);
		_manager->_camera->SetTarget(camposTar);
		_manager->_camera->SetFocalLengs(forcalLengs);
		_manager->_camera->Update();
		_objects->floorGround->Update();

		BulletManager::GetInstance()->Update();
		for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
			enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			enemy->Update();
			if (!enemy->HowDead()) {
				_objects->eneCount++;
			}
		}
		for (std::unique_ptr <Boss>& boss : _objects->boss) {
			boss->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
			boss->Update();
			if (!boss->HowDead()) {
				_objects->bossCount++;
			}
		}
		for (std::unique_ptr < Wall>& walls : _objects->walls) {
			walls->Update();
		}
	}
}

void Tutorial::Update(Input* input) {
	_objects->eneCount = 0;
	_objects->bossCount = 0;
	_objects->floorGround->Update();
	//_objects->bossFbxO_->Update();
	if (input) {

	}



	if (startTime_ == true && stageClear == false && stageFailed == false) {
		startTime_ = _objects->Banner();
	}
	else if (startTime_ == false && stageClear == false && stageFailed == false) {
		_manager->_camera->SetEye(camposEye);
		_manager->_camera->SetTarget(camposTar);
		TutorialUpdate(_manager->tutorialNum);
	}
	else if (startTime_ == false && stageClear == false && stageFailed == true) {
		stageFailed = _objects->Banner(NUMBER::NUM_ONE);
		if (stageFailed == false) {
			_manager->SetSceneNum(SCE_GAME1);
		}
	}
	else if (startTime_ == false && stageClear == true && stageFailed == false) {
		stageClear = _objects->Banner(NUMBER::NUM_TWO);
		if (stageClear == false) {
			/*_manager->SetSceneNum(SCE_CLEAR);*/
			_manager->SetSceneNum(SCE_GAME1);
			if (_manager->tutorialNum == TUTO_8) {
				_manager->TutorialOFF();
			}
		}
	}
	_objects->UIUpdate();
}

void Tutorial::Draw() {
	_objects->floorGround->Draw(_manager->_dxCommon);
	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->Draw(_manager->_dxCommon);
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->Draw(_manager->_dxCommon);
	}
	for (std::unique_ptr <Wall>& walls : _objects->walls) {
		walls->Draw(_manager->_dxCommon);
	}
	//_objects->bossFbxO_->Draw(_manager->_dxCommon->GetCommandList());

	Object3d::PreDraw(_manager->_dxCommon->GetCommandList());

	BulletManager::GetInstance()->Draw();

	Object3d::PostDraw();
	if (startTime_ == false) {
		_objects->player->Draw(_manager->_dxCommon);
	}
	_objects->SlowEffectDraw();
	_objects->plDamageRed_->Draw();
	_objects->UIDraw();
	if (startTime_ == false && stageClear == false && stageFailed == false) {
		SpriteDraw(isDrawSP_);
	}
	if (startTime_ == true || stageFailed == true || stageClear == true) {
		_objects->BannerDraw();
	}
}

void Tutorial::TutorialUpdate(uint32_t tutorialNum)
{
#ifdef _DEBUG
	if (Input::get_instance().KeyboardPush(DIK_P)) {
		Vector3 eyeDebug = _objects->player->GetTransform().position;
		eyeDebug.y = (float)3.5f;
		_manager->_camera->SetEye(eyeDebug);
		_manager->_camera->SetTarget(_objects->player->GetReticleTransform().position);
		_manager->_camera->Update();
	}
#endif // DEBUG

	_objects->player->Update(&Input::get_instance());
	_objects->SlowEffect(_objects->player->GetIsSlow());
	_objects->damageRedAlpha_ = (float)_objects->player->GetHIT() / (float)_objects->player->GetMAXHP();
	_objects->plDamageRed_->SetColor(Vector4(1, 0, 0, _objects->damageRedAlpha_ / (float)_objects->player->GetMAXHP()));

	stageFailed = _objects->player->GetIsDeath();

	SpriteUpdate(tutorialNum);
	BulletManager::GetInstance()->Update();

	for (std::unique_ptr <Enemy>& enemy : _objects->enemys) {
		enemy->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
		enemy->Update();
		if (!enemy->HowDead()) {
			_objects->eneCount++;
		}
	}
	for (std::unique_ptr <Boss>& boss : _objects->boss) {
		boss->SetReticle(Affin::GetWorldTrans(_objects->player->GetTransform().matWorld));
		boss->Update();
		if (!boss->HowDead()) {
			_objects->bossCount++;
		}
	}
	for (std::unique_ptr < Wall>& walls : _objects->walls) {
		walls->Update();
	}	

	if (Input::get_instance().KeyboardTrigger(DIK_TAB)) {
		_manager->SetSceneNum(SCE_PAUSE);
	}
	else if (_objects->eneCount == 0 && _objects->bossCount == 0) {
		stageClear = true;
		_manager->tutorialNum += 1;
	}
}

void Tutorial::SpriteInitialize()
{
	infoSP_ = std::make_unique<Sprite>();
	infoSP_->Initialize(_objects->spriteCommon_.get(), 60);
	infoSP_->SetSize({ 300,150 });
	infoSP_->SetPozition({ (WinApp::window_width / 1.5f) - 150,WinApp::window_height - 200 });
	isDrawSP_ = true;
	infoNum_ = 60;
	nowInfoNum_ = 0;

	isInfoBarrier = false;
	isInfoSHOT = false;
	isInfoSLOW = false;
	isInfoDUSH = false;
	isInfoWEPC = false;
	isAllFalse = true;
	isTimeCount = false;
}

void Tutorial::SpriteUpdate(uint32_t tutorialNum) {
	if (tutorialNum) {

	}
	if (Input::get_instance().KeyboardPush(DIK_SPACE) && nowInfoNum_ == 0) {
		isInfoBarrier = true;
		isTimeCount = true;
	}
	if ((Input::get_instance().MouseButtonPush(0) && !Input::get_instance().MouseButtonPush(1)) && nowInfoNum_ == 1) {
		isInfoSHOT = true;
		isTimeCount = true;
	}
	if ((!Input::get_instance().MouseButtonPush(0) && Input::get_instance().MouseButtonPush(1)) && nowInfoNum_ == 2) {
		isInfoSLOW = true;
		isTimeCount = true;
	}
	if ((Input::get_instance().MouseButtonPush(0) && Input::get_instance().MouseButtonPush(1)) && nowInfoNum_ == 3) {
		isInfoDUSH = true;
		isTimeCount = true;
	}
	if ((Input::get_instance().KeyboardPush(DIK_E)) && nowInfoNum_ == 4) {
		isInfoWEPC = true;
		isTimeCount = true;

	}
	if (isTimeCount) {
		infoCountTime_++;
	}
	if (isInfoBarrier == true && infoCountTime_ >= 150) {
		nowInfoNum_ = 1;
		infoNum_ = 61;
		isInfoBarrier = false;
		isTimeCount = false;
		infoCountTime_ = 0;
	}
	if (isInfoSHOT == true && infoCountTime_ >= 150) {
		nowInfoNum_ = 2;
		infoNum_ = 62;
		isInfoSHOT = false;
		isTimeCount = false;
		infoCountTime_ = 0;
	}
	if (isInfoSLOW == true && infoCountTime_ >= 150) {
		nowInfoNum_ = 3;
		infoNum_ = 63;
		isInfoSLOW = false;
		isTimeCount = false;
		infoCountTime_ = 0;
	}
	if (isInfoDUSH == true && infoCountTime_ >= 150) {
		nowInfoNum_ = 4;
		infoNum_ = 64;
		isInfoDUSH = false;
		isTimeCount = false;
		infoCountTime_ = 0;
	}
	if (isInfoWEPC == true && infoCountTime_ >= 150) {
		nowInfoNum_ = 0;
		infoNum_ = 60;
		isInfoWEPC = false;
		isDrawSP_ = false;
		isTimeCount = false;
		infoCountTime_ = 0;
	}
	infoSP_->SetTextureIndex(infoNum_);
}

void Tutorial::SpriteDraw(bool isTutrial)
{
	if (isTutrial == true) {
		infoSP_->Draw();
	}
}
