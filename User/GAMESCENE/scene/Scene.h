#pragma once


class Input;
class SceneManager;
class DirectXCommon;

// �V�[���Ǘ��̂��߂̊��N���X
// (�������N���X)

class Scene
{
protected:

	SceneManager* _controller;

public:

	Scene();
	virtual ~Scene();

	//virtual Scene Create(SceneManager& controller) = 0;
	/// �V�[���̍X�V���s��
	virtual void Initialize(DirectXCommon* dxCommon) = 0;

	/// �V�[���̍X�V���s��
	virtual void Update(Input* input) = 0;

	/// �V�[���̕`����s��
	virtual void Draw(DirectXCommon* dxCommon) = 0;

};

