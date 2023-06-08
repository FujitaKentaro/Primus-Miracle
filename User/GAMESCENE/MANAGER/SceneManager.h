#pragma once
#include <memory>
#include <stack>

class Input;
class IScene;
class DirectXCommon;
class Camera;
class SceneObjects;

// �V�[���Ǘ��N���X
class SceneManager
{
public:
	std::shared_ptr<IScene> _scene;
	DirectXCommon* _dxCommon;
	Camera* _camera;
	SceneObjects* _objects;
	
public:

	SceneManager(DirectXCommon* dxCommon, Camera* camera, SceneObjects* objects);
	~SceneManager();

	// �e�V�[����Initialize���Ăяo��
	void SceneInitialize();
	// �e�V�[����Update���Ăяo��
	void SceneUpdate(Input* input);
	// �e�V�[����Draw���Ăяo��
	void SceneDraw();

	// �V�[����ύX����
	void ChangeScene(IScene*);

	// �e�V�[���ɓn���p�̃I�u�W�F�N�g�̃|�C���^���擾
	//void SetSceneObjects(SceneObjects* objects) { _objects = objects; };
};

//	�Q�ƌ�
//	https://qiita.com/tsuchinokoman/items/390a22a20abe2a6daa6d <-�����킩���