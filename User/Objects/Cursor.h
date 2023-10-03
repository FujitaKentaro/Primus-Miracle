#pragma once
#include "Input.h"
#include "DirectXCommon.h"
#include "Object3d.h"
#include "Sprite.h"
#include "SpriteCommon.h"

class Cursor
{
public:
	Cursor();
	~Cursor();
	/// シーンの更新を行う
	void Initialize(SpriteCommon* spriteCommon);
	/// シーンの更新を行う
	void Update(Input* input);
	/// シーンの描画を行う
	void Draw(DirectXCommon* dxCommon);

	void CusUpdate();
private:
	Transform cameraWTF_;
	Model* model_;
	Object3d* object_;
	Transform worldTransform3DReticle_;

	float mouseSensitivity_ = 0.099f;	//マウス感度 0.05

private://リソース
	std::unique_ptr <Sprite> cursorPic_;
};

