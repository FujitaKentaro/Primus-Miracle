#include "GameScene.h"


#include<sstream>
#include<fstream>
#include<iomanip>
#include"imgui.h"

/// <summary>
	/// �R���X�g�N���^
	/// </summary>
GameScene::GameScene() {

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameScene::~GameScene() {
	//�I�[�f�B�I���
	//audio->Finalize();
	//delete audio;

	delete spriteCommon;
	delete camera;
	delete sceneManager;
}

/// <summary>
/// ������
/// </summary>
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input) {
	// null�`�F�b�N
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	cam_TF.Initialize();
	cam_TF.position = { 0.0f, 2.5f, 8.0f };
	tar = { 0.0f, 2.5f, 0.0f };


	// �J��������
	camera = new Camera(WinApp::window_width, WinApp::window_height);
	//FBXObject3d::SetCamera(camera);
	ParticleManager::SetCamera(camera);
	Object3d::SetCamera(camera);

	sceneManager = new SceneManager(dxCommon, camera);
	sceneManager->ObjectInitialize();
	sceneManager->SceneInitialize();
	// Json
	{
		//leveData = JsonLoader::LoadJsonFile("Test");

		//// ���f���ǂݍ���
		//modelcube = Model::LoadFromOBJ("cube");
		//modelREX = Model::LoadFromOBJ("REX");

		//models.insert(std::make_pair("cube", modelcube));
		//models.insert(std::make_pair("REX", modelREX));

		//{


		//	for (auto& objectData : leveData->objects) {
		//		//�t�@�C��������o�^�ς݃��f��������
		//		Model* model = nullptr;
		//		decltype(models)::iterator it = models.find(objectData.fileName);
		//		if (it != models.end()) { model = it->second; }
		//		// ���W
		//		Object3d* newObject = Object3d::Create();
		//		newObject->SetModel(model);
		//		//���W
		//		Vector3 pos;
		//		pos = objectData.translation;
		//		newObject->wtf.position = pos;
		//		//��]
		//		Vector3 rot;
		//		rot = objectData.rotation;
		//		newObject->wtf.rotation = rot;
		//		//�g�k
		//		Vector3 sca;
		//		sca = objectData.scaling;
		//		newObject->wtf.scale = sca;
		//		//
		//		objects.push_back(newObject);

		//	}
		//}
	}

}

/// <summary>
/// ���t���[������
/// </summary>
void GameScene::Update() {
	cam_TF.UpdateMat();
	camera->SetEye(Affin::GetWorldTrans(cam_TF.matWorld));
	camera->SetTarget(tar);
	camera->Update();

	

	/*for (auto& object : objects) {
		object->Update();
	}*/
	sceneManager->SceneUpdate(input);
}

/// <summary>
/// �`��
/// </summary>
void GameScene::Draw() {
	sceneManager->SceneDraw();
	// Json
	{
		/*Object3d::PreDraw(dxCommon->GetCommandList());
		for (auto& object : objects) {
			object->Draw();
		}
		Object3d::PostDraw();*/
	}
	//ImGui::Begin("Info");
	////ImGui::Text("E : particle");
	//ImGui::Text("WASD : ball rotate");
	//ImGui::End();
}