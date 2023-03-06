#pragma once
#include <memory>
#include <stack>

class Input;
class Scene;
class DirectXCommon;

// �V�[���Ǘ��N���X
class SceneManager
{
private:
	std::shared_ptr<Scene> _scene;
	DirectXCommon* _dxCommon;
public:

	SceneManager(DirectXCommon* dxCommon);
	~SceneManager();	

	// �e�V�[����Initialize���Ăяo��
	void SceneInitialize();
	// �e�V�[����Update���Ăяo��
	void SceneUpdate(Input* input);
	// �e�V�[����Draw���Ăяo��
	void SceneDraw();

	// �V�[����ύX����
	void ChangeScene(Scene*);

};

//	�Q�ƌ�
//	https://qiita.com/tsuchinokoman/items/390a22a20abe2a6daa6d <-�����킩���