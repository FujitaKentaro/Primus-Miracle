/**
 * @file SceneManager.cpp
 * @brief シーン管理クラス
 */

#include <cassert>

#include "SceneManager.h"
#include "Input.h"
#include "DirectXCommon.h"
#include "Camera.h"
#include "SceneObjects.h"

 // シーンのインクルード
#include "SceneIntegrate.h"


SceneManager::SceneManager(DirectXCommon* dxCommon, Camera* camera, SceneObjects* objects) {
	_dxCommon = dxCommon;
	_objects = objects;
	IScene::SetSceneManager(&*this);
	_scene.emplace(new TitleScene());
	_objects->SetingLevel(_objects->levels.at(_objects->levelName_[0]).get());
	_camera = camera;

}
SceneManager::~SceneManager() {

}

void SceneManager::SceneInitialize() {
	_scene.top().get()->Initialize();
}

void SceneManager::SceneUpdate(Input* input) {
	_scene.top().get()->Update(input);
}

void SceneManager::SceneDraw() {
	_scene.top().get()->Draw();
}

void SceneManager::ChangeScene() {

	if (goToTitle == true) {
		_scene.pop();
		_scene.pop();
		_scene.emplace(new TitleScene());
		_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TITLE]).get());
		SceneInitialize();
		_objects->OFFIsUIDraw();
		TransScene();
		goToTitle = false;
	}

	if (isChange == true && goToTitle == false) {

		switch (sceneNum)
		{
		case SCE_TITLE:
			_scene.pop();
			_scene.emplace(new TitleScene());
			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TITLE]).get());
			SceneInitialize();
			_objects->OFFIsUIDraw();
			TransScene();
			break;
		case SCE_GAME1:
			_scene.pop();
			_scene.emplace(new GAME1Scene());
			_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::TUTRIAL]).get());
			SceneInitialize();
			_objects->ONIsUIDraw();
			TransScene();
			break;

		case SCE_GAME2:
		case SCE_GAME3:
			_scene.pop();
			_scene.emplace(new GAME2Scene());
			if (SCE_GAME2 == sceneNum) {
				_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::STAGE1]).get());
			}
			else if (SCE_GAME3 == sceneNum) {
				_objects->SetingLevel(_objects->levels.at(_objects->levelName_[LEVELS::STAGE2]).get());
			}
			SceneInitialize();
			_objects->ONIsUIDraw();
			TransScene();
			break;
		case SCE_SELECT:
			_scene.pop();
			_scene.emplace(new SelectScene());
			SceneInitialize();
			_objects->OFFIsUIDraw();
			TransScene();
			break;
		case SCE_CLEAR:
			_scene.pop();
			_scene.emplace(new Clear());
			SceneInitialize();
			_objects->OFFIsUIDraw();
			TransScene();
			break;
		case SCE_PAUSE:
			Pause();
			break;
			/////////////////////////////////////////////////////
		default:
			break;
		}
		isChange = false;
	}
	else {
		isChange = false;
	}
}

void SceneManager::TransScene()
{
	_scene.emplace(new TransitionsScene());
	SceneInitialize();
}

void SceneManager::Pause()
{
	_scene.emplace(new PauseScene());
	SceneInitialize();
}

void SceneManager::PushScene(IScene* scene) {
	_scene.emplace(scene);
}
void SceneManager::PopScene() {
	_scene.pop();
	assert(!_scene.empty());
}