#include "Human.h"


Human::Human() {

}
Human::~Human() {

}

/// シーンの更新を行う
void Human::Initialize() {

}

/// シーンの更新を行う
void Human::Update(Input* input,bool isTitle) {
	assert(input);
	if (input) {

	}
	_isTitle = isTitle;
}

/// シーンの描画を行う
void Human::Draw(DirectXCommon* dxCommon) {
	assert(dxCommon);
	dxCommon->GetDevice();
}