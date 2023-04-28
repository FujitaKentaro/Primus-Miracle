#pragma once
#include <d3d12.h>
#include <d3dx12.h>
#include <string>
#include <sstream>
#include <fstream>

#include "Affin.h"
#include <DirectXMath.h>
#include <map>

#include "Model.h"
#include "Object3d.h"

// ���x���f�[�^
struct LevelData {

	struct ObjectData {
		// �t�@�C����
		std::string fileName;
		// ���s�ړ�
		Vector3 translation;
		// ��]�p
		Vector3 rotation;
		// �X�P�[�����O
		Vector3 scaling;
	};

	// �I�u�W�F�N�g�z��
	std::vector<ObjectData> objects;
};

class JsonLoader
{
private: // �G�C���A�X
	// std::���ȗ�
	using string = std::string;
public: // �萔
	// ���f���i�[���[�g�p�X
	static const string baseDirectory;
	// �f�t�H���g�̓ǂݍ��݃f�B���N�g��
	static const std::string kDefaultBaseDirectory;
	// �t�@�C���g���q
	static const std::string kExtension;
public:
	JsonLoader();
	~JsonLoader();

	static LevelData* LoadJsonFile(const string& filename);
	//void NodeRecursive(nlohmann::json deserialized, LevelData* levelData);

	//void MakeScene(LevelData* leveData);

private:
	std::map<std::string,Model*> models;
};

