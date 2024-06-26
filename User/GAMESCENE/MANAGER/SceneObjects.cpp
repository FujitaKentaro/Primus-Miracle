/**
 * @file SceneObject.cpp
 * @brief シーンオブジェクト所持クラス
 */
#include "SceneObjects.h"


SceneObjects::SceneObjects(DirectXCommon* dxcommon) {
	_dxcommon = dxcommon;
}
SceneObjects::~SceneObjects() {
	enemys.clear();
	walls.clear();
	boss.clear();
	delete skydome_M;
	delete box;
	delete floorGroundMD;
}

void SceneObjects::Initialize() {
	ShowCursor(false);
#ifdef _DEBUG
	ShowCursor(true);
#endif
	// オーディオロード
	{
		Audio::get_instance()->LoadWave("shot.wav");
	}
	// スプライトロード集
	{
		{
			enum spriteNum
			{
				title = 1,
				inu = 2,
				end = 3,
				clear = 4,
				select = 5,
				gray = 6,
				Cursor = 7,
				START = 8,
				START2 = 9,
			};
			//スプライト初期化
			spriteCommon_ = std::make_unique<SpriteCommon>();
			spriteCommon_->Initialize(_dxcommon);
			// TITLE
			spriteCommon_->LoadTexture(1, "title.png");
			spriteCommon_->LoadTexture(2, "inu.png");
			spriteCommon_->LoadTexture(3, "end.png");
			spriteCommon_->LoadTexture(4, "clear.png");
			spriteCommon_->LoadTexture(5, "select.png");
			spriteCommon_->LoadTexture(6, "gray.png");
			spriteCommon_->LoadTexture(7, "Cursor.png");
			spriteCommon_->LoadTexture(8, "START.png");
			spriteCommon_->LoadTexture(9, "START2.png");
			spriteCommon_->LoadTexture(10, "BACK.png");
			spriteCommon_->LoadTexture(11, "title2.png");
			spriteCommon_->LoadTexture(12, "readyBuck.png");
			spriteCommon_->LoadTexture(13, "readySTART.png");
			spriteCommon_->LoadTexture(14, "faildBuck.png");
			spriteCommon_->LoadTexture(15, "faildFAILED.png");
			spriteCommon_->LoadTexture(16, "clearBuck.png");
			spriteCommon_->LoadTexture(17, "clearCLEAR.png");
			spriteCommon_->LoadTexture(18, "Cursor2.png");

		}
		// スプライトロード  20~ //セレクトステージ
		{
			spriteCommon_->LoadTexture(20, "1.png");
			spriteCommon_->LoadTexture(21, "1_1.png");
			spriteCommon_->LoadTexture(22, "2.png");
			spriteCommon_->LoadTexture(23, "2_1.png");
			spriteCommon_->LoadTexture(24, "3.png");
			spriteCommon_->LoadTexture(25, "3_1.png");
			spriteCommon_->LoadTexture(26, "Left.png");
			spriteCommon_->LoadTexture(27, "Left2.png");
			spriteCommon_->LoadTexture(28, "Right.png");
			spriteCommon_->LoadTexture(29, "Right2.png");
		}
		// スプライトロード  30~ // 色画像用
		{
			spriteCommon_->LoadTexture(30, "red.png");
			spriteCommon_->LoadTexture(31, "orange.png");
			spriteCommon_->LoadTexture(32, "purple.png");
			spriteCommon_->LoadTexture(33, "yellow.png");
			spriteCommon_->LoadTexture(34, "black.png");
			spriteCommon_->LoadTexture(35, "white1x1.png");
			spriteCommon_->LoadTexture(36, "lightgray.png");
			spriteCommon_->LoadTexture(37, "cian.png");
			spriteCommon_->LoadTexture(38, "green.png");
		}
		// スプライトロード  40~ // UI画像用
		{
			spriteCommon_->LoadTexture(40, "UIbase.png");
			spriteCommon_->LoadTexture(41, "Weapon1ICON.png");
			spriteCommon_->LoadTexture(42, "Weapon2ICON.png");
			spriteCommon_->LoadTexture(43, "Weapon3ICON.png");
			spriteCommon_->LoadTexture(44, "Slow1ICON.png");
			spriteCommon_->LoadTexture(45, "Slow2ICON.png");
			spriteCommon_->LoadTexture(46, "Point1ICON.png");
			spriteCommon_->LoadTexture(47, "Point2ICON.png");
			spriteCommon_->LoadTexture(48, "pauseInfo.png");
			spriteCommon_->LoadTexture(49, "pointpic.png");
		}
		// スプライトロード  50~ // シーン用
		{
			spriteCommon_->LoadTexture(50, "goTitle.png");
			spriteCommon_->LoadTexture(51, "goTitle2.png");
			spriteCommon_->LoadTexture(52, "pauseGoBack.png");
			spriteCommon_->LoadTexture(53, "GoSelect.png");
			spriteCommon_->LoadTexture(54, "GoSelect2.png");
			spriteCommon_->LoadTexture(55, "NEXT.png");
			spriteCommon_->LoadTexture(56, "NEXT2.png");

		}
		// スプライトロード  60~ // シーン用
		{
			spriteCommon_->LoadTexture(60, "TYU_WASD.png");
			spriteCommon_->LoadTexture(61, "TYU_SHOT.png");
			spriteCommon_->LoadTexture(62, "TYU_SLOW.png");
			spriteCommon_->LoadTexture(63, "TYU_DASH.png");
			spriteCommon_->LoadTexture(64, "TYU_WPCH.png");
			//spriteCommon_->LoadTexture(65, "NEXT.png");
			//spriteCommon_->LoadTexture(66, "NEXT2.png");

		}
	}

	mouseCursor_ = std::make_unique<Cursor>();
	mouseCursor_->Initialize(spriteCommon_.get());

	// fbx テスト
	{
		bossFbxM_.reset(FbxLoader::GetInstance()->LoadModelFromFile("Fbx_Rex", false));
		bossFbxO_ = std::make_unique<FBXObject3d>();
		bossFbxO_->Initialize();
		bossFbxO_->SetModel(bossFbxM_.get());
		bossFbxO_->SetPosition({ 0,0,0 });
		bossFbxO_->SetScale({ 0.9f,0.9f,0.9f });
		bossFbxO_->PlayAnimation(1);
		bossFbxO_->AnimIsRotateChange();
	}

	// レベルロード
	LoadLevels();
	{
		player = std::make_unique<Player>();
		player->Initialize();
	}
	{
		plDamageRed_ = std::make_unique<Sprite>();
		plDamageRed_->Initialize(spriteCommon_.get(), 30);
		plDamageRed_->SetSize({ WinApp::window_width ,WinApp::window_height });
		plDamageRed_->SetPozition(plDamageRedPos);
		plDamageRed_->SetColor(Vector4(0, 0, 0, 0));
	}
	{
		wallMD.reset(Model::LoadFromOBJ("wall"));
		floorGroundMD = Model::LoadFromOBJ("stage");
		floorGround = std::make_unique<Floor>();
		floorGround->Initialize(floorGroundMD);
	}
	enemyMD.reset(Model::LoadFromOBJ("ene"));
	skydome_O = std::make_unique<Object3d>();
	skydome_M = Model::LoadFromOBJ("skydome");
	box = Model::LoadFromOBJ("cube");
	skydome_O->SetModel(skydome_M);
	skydome_O->Initialize();
	skydome_O->transForm.scale = Vector3(10000.0f, 10000.0f, 10000.0f);


	// 演出用の初期化
	// バナー
	{

		{
			bannerBuckSP_ = std::make_unique<Sprite>();
			bannerBuckSP_->Initialize(spriteCommon_.get(), 12);
			bannerBuckSP_->SetSize({ WinApp::window_width / 2.0f ,100.0f });
			bannerBuckSPpos_ = { 0,WinApp::window_height / 2.0f };
			bannerBuckSPscale_ = Vector3(1.0f, 0001.0f, 1.0f);
			bannerBuckSP_->SetPozition(bannerBuckSPpos_);
			bannerBuckSP_->SetScale(bannerBuckSPscale_);
		}
		{
			bannerBuck2SP_ = std::make_unique<Sprite>();
			bannerBuck2SP_->Initialize(spriteCommon_.get(), 12);
			bannerBuck2SP_->SetSize({ WinApp::window_width / 2.0f ,100.0f });
			bannerBuck2SPpos_ = { WinApp::window_width / 2.0f,WinApp::window_height / 2.0f };
			bannerBuck2SPscale_ = Vector3(1.0f, 0.0001f, 1.0f);
			bannerBuck2SP_->SetPozition(bannerBuck2SPpos_);
			bannerBuck2SP_->SetScale(bannerBuck2SPscale_);
		}
		{
			bannerWordSP_ = std::make_unique<Sprite>();
			bannerWordSP_->Initialize(spriteCommon_.get(), 13);
			bannerWordSP_->SetSize({ 300.0f ,100.0f });
			bannerWordSPpos_ = { -300.0f, WinApp::window_height / 2.0f };
			bannerWordSPscale_ = Vector3(1.0f, 1.0f, 1.0f);
			bannerWordSP_->SetPozition(bannerWordSPpos_);
			bannerWordSP_->SetScale(bannerWordSPscale_);
		}
	}
	// スロー
	{
		slowSP_ = std::make_unique<Sprite>();
		slowSP_->Initialize(spriteCommon_.get(), 32);
		slowSP_->SetPozition(Vector2{ 0.0f,0.0f });
		slowSP_->SetSize({ WinApp::window_width ,WinApp::window_height });
		slowSP_->SetColor(Vector4{ 0.1f,0.1f,0.1f,0.0f });
	}
	// UI
	{
		{
			UIBuckSP_ = std::make_unique<Sprite>();
			UIBuckSP_->Initialize(spriteCommon_.get(), 40);
			UIBuckSPpos_ = Vector2();
			UIBuckSPsize_ = Vector2{ WinApp::window_width ,WinApp::window_height };
			UIBuckSP_->SetPozition(UIBuckSPpos_);
			UIBuckSP_->SetSize(UIBuckSPsize_);
		}
		{
			UISlowSP_ = std::make_unique<Sprite>();
			UISlowSP_->Initialize(spriteCommon_.get(), 44);
			UISlowSPpos_ = Vector2{ WinApp::window_width - WinApp::window_width / 9.0f  ,WinApp::window_height / 9.0f + 100.0f };
			UISlowSPsize_ = Vector2{ 80.0f ,80.0f };
			UISlowSP_->SetPozition(UISlowSPpos_);
			UISlowSP_->SetSize(UISlowSPsize_);
		}
		{
			UIPointSP_ = std::make_unique<Sprite>();
			UIPointSP_->Initialize(spriteCommon_.get(), 46);
			UIPointSPpos_ = Vector2{ UISlowSPpos_.x ,UISlowSPpos_.y + 100.0f };
			UIPointSPsize_ = Vector2{ 80.0f ,80.0f };
			UIPointSP_->SetPozition(UIPointSPpos_);
			UIPointSP_->SetSize(UIPointSPsize_);
		}
		{
			UIHPSP_ = std::make_unique<Sprite>();
			UIHPSP_->Initialize(spriteCommon_.get(), 38);
			UIHPSPpos_ = Vector2{ WinApp::window_width - WinApp::window_width / 9.0f + 26.0f ,WinApp::window_height - WinApp::window_height / 7.0f };
			UIHPSPsize_ = Vector2{ 30.0f,8.0f * player->GetHP() };
			UIHPSP_->SetPozition(UIHPSPpos_);
			UIHPSP_->SetSize(UIHPSPsize_);
			UIHPSP_->SetIsFlipY(true);
		}
		{
			UIHPBaseSP_ = std::make_unique<Sprite>();
			UIHPBaseSP_->Initialize(spriteCommon_.get(), 30);
			UIHPBaseSPpos_ = Vector2{ WinApp::window_width - WinApp::window_width / 9.0f + 26.0f,WinApp::window_height - WinApp::window_height / 7.0f };
			UIHPBaseSPsize_ = Vector2{ 30.0f,8.0f * player->GetHP() };
			UIHPBaseSP_->SetPozition(UIHPBaseSPpos_);
			UIHPBaseSP_->SetSize(UIHPBaseSPsize_);
			UIHPBaseSP_->SetIsFlipY(true);
		}
		{
			UIBarrierGaugeSP_ = std::make_unique<Sprite>();
			UIBarrierGaugeSP_->Initialize(spriteCommon_.get(), 37);
			//UIWeaponSP_->Initialize(spriteCommon_.get(), 41);
			UIWeaponSPpos_ = Vector2{ UIHPBaseSPpos_.x + 30.0f ,WinApp::window_height - WinApp::window_height / 7.0f };
			UIWeaponSPsize_ = Vector2{ 20.0f ,(float)player->GetBarrierCoolTime() };
			UIBarrierGaugeSP_->SetColorAlpha(0.5f);
			UIBarrierGaugeSP_->SetPozition(UIWeaponSPpos_);
			UIBarrierGaugeSP_->SetSize(UIWeaponSPsize_);
			UISP_Wep_size = NUMBER::NUM_THREE;
		}
		{
			backWall = { 0,2,10,21,0,0, };
		}
		{
			UIPauseSP_ = std::make_unique<Sprite>();
			UIPauseSP_->Initialize(spriteCommon_.get(), 48);
			UIPauseSPpos_ = Vector2{ 20 ,20 };
			UIPauseSPsize_ = Vector2{ 125.0f,64.0f };
			UIPauseSP_->SetPozition(UIPauseSPpos_);
			UIPauseSP_->SetSize(UIPauseSPsize_);
		}
		{
			UIDushPos_ = Vector2{ 30 ,WinApp::window_height / 7.0f };
			UIDushSize_ = Vector2{ 64.0f,64.0f };
			for (size_t i = 0; i < UIDushSP_.size(); i++) {
				UIDushSP_[i] = std::make_unique<Sprite>();
				UIDushSP_[i]->Initialize(spriteCommon_.get(), 49);
				UIDushPos_ += Vector2{ 0 ,64 };
				UIDushSP_[i]->SetPozition(UIDushPos_);
				UIDushSP_[i]->SetSize(UIDushSize_);
			}
		}
	}


	//ライトの生成
	lightGroup = std::make_unique< LightGroup>();
	lightGroup->Initialize();

	lightGroup->SetDirLightActive(0, true);
	rotateLight = { MathUtility::radConvert(60.0f), MathUtility::radConvert(30.0f), MathUtility::radConvert(0.0f) };

	lightGroup->SetDirLightColor(0, Vector3(1, 1, 1));
	lightDir = Affin::VecMat(pointLightPos, Affin::matRotation(rotateLight));
	lightGroup->SetDirLightDir(0, Vector4(lightDir.x, lightDir.y, lightDir.z, 0));

	//3Dオブジェクトにライトをセット
	Object3d::SetLight(lightGroup.get());
}

void SceneObjects::UpdateImGui()
{
#ifdef _DEBUG
	// Imgui
	int UISP_Weapon_size = UISP_Wep_size;
	ImGui::Begin("Objects");
	ImGui::Text("Objects");
	ImGui::Text("JsonMapNum:%d", (int)levels.size());
	ImGui::Text("DirLight");
	ImGui::InputFloat3("DirRot", &pointLightPos.x);
	ImGui::SliderFloat3("DirPos", &rotateLight.x, 0.0f, MathUtility::radConvert(360.0f));
	ImGui::Text("UI");
	ImGui::SliderInt("BarrierUISize", &UISP_Weapon_size, 1, 4);
	ImGui::Text("eneSize:%d", enemys.size());
	ImGui::Text("bossSize:%d", boss.size());
	ImGui::End();
	lightDir = Affin::VecMat(pointLightPos, Affin::matRotation(rotateLight));
	lightGroup->SetDirLightDir(0, Vector4(lightDir.x, lightDir.y, lightDir.z, 0));
	UISP_Wep_size = UISP_Weapon_size;
#endif

	////デスフラグの立った弾を削除
	//boss.remove_if([](std::unique_ptr<Boss>& boss_) {
	//	return boss_->HowDead();
	//	});
	//デスフラグの立った弾を削除
	//enemys.remove_if([](std::unique_ptr<Enemy>& enemy) {
	//	return !enemy->HowDead();
	//	});
}

void SceneObjects::Reset()
{
	enemys.clear();
	boss.clear();
	walls.clear();
}


bool SceneObjects::Banner(uint32_t isStart)
{

	if (isStart == 0) {
		bannerBuckSP_->SetTextureIndex(12);
		bannerBuck2SP_->SetTextureIndex(12);
		bannerWordSP_->SetTextureIndex(13);
	}
	if (isStart == 1) {
		bannerBuckSP_->SetTextureIndex(14);
		bannerBuck2SP_->SetTextureIndex(14);
		bannerWordSP_->SetTextureIndex(15);
	}
	if (isStart == 2) {
		bannerBuckSP_->SetTextureIndex(16);
		bannerBuck2SP_->SetTextureIndex(16);
		bannerWordSP_->SetTextureIndex(17);
	}

	bannerTimer++;
	bannerTime++;
	bannerEasetime = (float)bannerTime / bannerEaseMaxTime;
	if (isBannerEaseOut) {
		bannerBuckSPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)bannerEasetime);
		bannerBuckSPpos_ = Easing::OutQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(0.0f, WinApp::window_height / 2.0f), (float)bannerEasetime);
		bannerBuck2SPscale_ = Easing::OutQuintVec3(Vector3(1.0f, 0.0001f, 1.0f), Vector3(1, 1, 1), (float)bannerEasetime);
		bannerBuck2SPpos_ = Easing::OutQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), (float)bannerEasetime);
		bannerWordSPpos_ = Easing::OutQuintVec2(Vector2(-300.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f - 150.0f, WinApp::window_height / 2.0f), (float)bannerEasetime);
	}
	else {
		bannerBuckSPpos_ = Easing::InQuintVec2(Vector2(0.0f, WinApp::window_height / 2.0f), Vector2(-(WinApp::window_width / 2.0f), WinApp::window_height / 2.0f), (float)bannerEasetime);
		bannerBuck2SPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width, WinApp::window_height / 2.0f), (float)bannerEasetime);
		//readyStartSPpos_ = Easing::InQuintVec2(Vector2(WinApp::window_width / 2.0f - 150.0f, WinApp::window_height / 2.0f), Vector2(WinApp::window_width / 2.0f - 150.0f, -100.0f), (float)easetime);
		bannerWordSP_->SetColor({ 1.0f,1.0f,1.0f,Easing::InQuintFloat(1.0f,0.0f, (float)bannerEasetime) });
	}
	bannerBuckSP_->SetScale(bannerBuckSPscale_);
	bannerBuckSP_->SetPozition(bannerBuckSPpos_);
	bannerBuck2SP_->SetScale(bannerBuck2SPscale_);
	bannerBuck2SP_->SetPozition(bannerBuck2SPpos_);
	bannerWordSP_->SetScale(bannerWordSPscale_);
	bannerWordSP_->SetPozition(bannerWordSPpos_);

	bannerBuckSP_->Update();
	bannerBuck2SP_->Update();
	bannerWordSP_->Update();


	if (bannerTime >= bannerEaseMaxTime && isBannerEaseOut == true) {
		bannerTime = 0;
		bannerEasetime = 0;
		isBannerEaseOut = false;
	}
	if (bannerTime >= bannerEaseMaxTime && isBannerEaseOut == false) {
		bannerTime = 0;
		bannerEasetime = 0;
		isBannerEaseOut = true;
		return false;
	}
	return true;
}
void SceneObjects::BannerDraw()
{
	bannerBuckSP_->Draw();
	bannerBuck2SP_->Draw();
	bannerWordSP_->Draw();
}

void SceneObjects::ShakeRand(Shake& shake)
{
	//フラグ0
	if (shake.isShake == 0) {
		shake.quantity = 23;
		shake.maxSwing = 10;
		shake.count = 50;
	}

	if (shake.isShake == 1) {
		shake.randX = rand() % shake.quantity - shake.maxSwing;
		shake.randZ = rand() % shake.quantity - shake.maxSwing;
		shake.count--;
	}

}
void SceneObjects::SlowEffect(bool isSlow)
{
	if (isSlowEaseOut == true && slowPlayEase_ == true) {
		nowSlowEffect = true;
		slowTime++;
		slowEasetime = (float)slowTime / slowEaseMaxTime;
		slowSPAlpha_ = Easing::OutQuintFloat(slowSP_ALPHA_MIN, slowSP_ALPHA_MAX, (float)slowEasetime);
		if (slowSPAlpha_ == slowSP_ALPHA_MAX) {
			slowSPTime_MAX = true;
			nowSlowEffect = false;
			slowTime = 0;
			slowEasetime = 0;
		}
	}
	if (isSlowEaseOut == false && slowPlayEase_ == true) {
		nowSlowEffect = true;
		slowTime++;
		slowEasetime = (float)slowTime / slowEaseMaxTime;
		slowSPAlpha_ = Easing::OutQuintFloat(slowSP_ALPHA_MAX, slowSP_ALPHA_MIN, (float)slowEasetime);
		if (slowSPAlpha_ == slowSP_ALPHA_MIN) {
			slowSPTime_MAX = true;
			nowSlowEffect = false;
			slowTime = 0;
			slowEasetime = 0;
		}
	}

	if (isSlowEaseOut != isSlow && changeIsSlow == false) {
		changeIsSlow = true;
	}
	else {
		changeIsSlow = false;
	}
	if (nowSlowEffect == false && slowSPTime_MAX == true) {
		slowPlayEase_ = false;
	}
	if (changeIsSlow == true && slowPlayEase_ == false) {
		slowTime = 0;
		slowEasetime = 0;
		slowPlayEase_ = true;
		isSlowEaseOut = isSlow;
	}

	slowSP_->SetColorAlpha(slowSPAlpha_);
	slowSP_->Update();
}
void SceneObjects::SlowReset()
{
	slowSPAlpha_ = 0.0f;
	slowSPTime_MAX = false;
	slowPlayEase_ = false;
	nowSlowEffect = false;
	changeIsSlow = false;
	isSlowEaseOut = false;
	slowEasetime = 0.0f;
	slowTime = 0;
	slowSP_->SetColorAlpha(0.0f);
	slowSP_->Update();
}
void SceneObjects::SlowEffectDraw()
{
	slowSP_->Draw();
}

void SceneObjects::UIUpdate()
{
	if (player->GetOnFire() && !player->GetIsCoolTimeON()) {
		UIBarrierGaugeSP_->SetTextureIndex(37);
		UIWeaponSPsize_.y = UISP_Wep_size * -(float)player->GetBarrierOnTime();
	}
	else if (player->GetOnFire() && player->GetIsCoolTimeON()) {
		UIWeaponSPsize_.y = UISP_Wep_size * 2.0f * -(float)player->GetBarrierCoolTime();
		UIBarrierGaugeSP_->SetTextureIndex(36);
		UIPointSP_->SetTextureIndex(46);
	}
	else {
		UIWeaponSPsize_.y = UISP_Wep_size * -(float)player->GetBarrierOnTime();
		UIBarrierGaugeSP_->SetTextureIndex(37);
	}
	if (player->GetIsSlow()) {
		//UIWeaponSP_->SetTextureIndex(43);
		UISlowSP_->SetTextureIndex(45);
		UIPointSP_->SetTextureIndex(47);
		if (player->GetPointMAX()) {
			UIPointSP_->SetTextureIndex(46);
		}
	}
	else {
		UISlowSP_->SetTextureIndex(44);
	}
	if (player->GetHP() > 0) {
		UIHPSPsize_.y = 8.0f * player->GetHP();
	}
	else if (player->GetHP() <= 0) {
		UIHPSPsize_.y = 0.0f;
	}
	UIBarrierGaugeSP_->SetSize(UIWeaponSPsize_);
	UIHPSP_->SetSize(UIHPSPsize_);
	UIBuckSP_->Update();
	UIBarrierGaugeSP_->Update();
	UISlowSP_->Update();
	UIPointSP_->Update();
	UIHPSP_->Update();
	UIHPBaseSP_->Update();
	UIPauseSP_->Update();
	for (size_t i = 0; i < NUMBER::NUM_FIVE; i++) {
		UIDushSP_[i]->Update();
	}
	for (size_t i = 0; i < NUMBER::NUM_FIVE; i++) {
		if (player->GetPoint()->GetRegistNum() - NUMBER::NUM_ONE == i) {
			UIDushSP_[i]->SetColor({1,0,0,1});
		}
		else if (player->GetPoint()->GetLineActive((uint32_t)i) == false) {
			UIDushSP_[i]->SetColor({ 1,1,1,1 });
		}
	}

}

void SceneObjects::UIDraw()
{
	//UIBuckSP_->Draw();
	UIBarrierGaugeSP_->Draw();
	UISlowSP_->Draw();
	UIPointSP_->Draw();
	UIHPBaseSP_->Draw();
	UIHPSP_->Draw();
	UIPauseSP_->Draw();
	for (size_t i = 0; i < NUMBER::NUM_FIVE; i++) {
		UIDushSP_[i]->Draw();
		// リソース待ち
	}
}

void SceneObjects::LoadLevels()
{
	levelName_.push_back("title");
	levelName_.push_back("stageDEMO");
	levelName_.push_back("stageTEMP2");
	levelName_.push_back("stageDEMO2");
	levelName_.push_back("Tutorial_1");
	levelName_.push_back("Tutorial_2");
	levelName_.push_back("Tutorial_3");

	for (int32_t i = 0; i < levelName_.size(); i++) {
		std::unique_ptr<LevelData> levelData = std::move(JsonLoader::LoadJsonFile(levelName_[i]));
		levels.emplace(std::make_pair(levelName_[i], std::move(levelData)));
	}

}

void SceneObjects::SetingLevel(LevelData* data)
{
	for (auto& objectData : data->JsonObjects) {

		if (objectData.fileName == "enemy") {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			if (objectData.weapon == "ASSAULT") {
				newEnemy->SetWeaponNum(WP_ASSAULT);
			}if (objectData.weapon == "SHOTGUN") {
				newEnemy->SetWeaponNum(WP_SHOTGUN);
			}if (objectData.weapon == "BOMFIRE") {
				newEnemy->SetWeaponNum(WP_BOMFIRE);
			}
			newEnemy->SetModel(enemyMD.get());
			newEnemy->Initialize();
			//座標
			Vector3 pos;
			pos = objectData.translation;
			newEnemy->object_->transForm.position = pos;
			//回転
			Vector3 rot;
			rot = objectData.rotation;
			newEnemy->object_->transForm.rotation = rot;
			newEnemy->SetRestRotate(rot);
			//拡縮
			Vector3 sca;
			sca = objectData.scaling;
			newEnemy->object_->transForm.scale = sca;
			//newEnemy->object_->SetColor(Vector4(0.5f, 1, 1, 0));
			enemys.emplace_back(std::move(newEnemy));
		}
		else if (objectData.fileName == "boss") {
			std::unique_ptr<Boss> newBoss = std::make_unique<Boss>();
			if (objectData.weapon == "ASSAULT") {
				newBoss->SetWeaponNum(WP_ASSAULT);
			}if (objectData.weapon == "SHOTGUN") {
				newBoss->SetWeaponNum(WP_SHOTGUN);
			}if (objectData.weapon == "BOMFIRE") {
				newBoss->SetWeaponNum(WP_BOMFIRE);
			}
			newBoss->SetFBXModel(bossFbxM_.get());
			newBoss->Initialize();
			//座標
			Vector3 pos;
			pos = objectData.translation;
			newBoss->object_->transForm.position = pos;
			//回転
			Vector3 rot;
			rot = objectData.rotation;
			newBoss->object_->transForm.rotation = rot;
			newBoss->SetRestRotate(rot);
			//拡縮
			Vector3 sca;
			sca = objectData.scaling;
			newBoss->object_->transForm.scale = sca;
			//newBoss->object_->SetColor(Vector4(0.5f, 1, 1, 0));
			boss.emplace_back(std::move(newBoss));
		}
		else if (objectData.fileName == "wall") {
			std::unique_ptr<Wall> newWall = std::make_unique<Wall>();
			newWall->Initialize(wallMD.get());
			//座標
			Vector3 pos;
			pos = objectData.translation;
			newWall->object_->transForm.position = pos;
			//回転
			Vector3 rot;
			rot = objectData.rotation;
			newWall->object_->transForm.rotation = rot;
			//拡縮
			Vector3 sca;
			sca = objectData.scaling;
			newWall->object_->transForm.scale = sca;
			newWall->object_->SetColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
			newWall->object_->Update();
			newWall->CollideInitialize();
			walls.emplace_back(std::move(newWall));
		}
		else if (objectData.fileName == "player") {
			Vector3 position = objectData.translation;
			player->SetPos(position);
		}
	}
}
