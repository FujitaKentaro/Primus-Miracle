#pragma once
#include <DirectXMath.h>
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "CircleShadow.h"

#include"Affin.h"

class LightGroup
{
private://�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template <class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirecX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public: 
	static const int DirLightNum = 3;

	//�_�����̐�
	static const int PointLightNum = 3;

	//�X�|�b�g���C�g�̐�
	static const int SpotLightNum = 3;

	//�ۉe�̐�
	static const int CircleShadowNum = 1;

public://�T�u�N���X
	struct ConstBufferData
	{
		XMFLOAT3 ambientColor;
		float pad1;

		//���s����
		DirectionalLight::ConstBufferData dirLights[DirLightNum];
		//�_�����p
		PointLight::ConstBufferData pointLights[PointLightNum];
		//�X�|�b�g���C�g�p
		SpotLight::ConstBufferData spotLights[SpotLightNum];
		//�ۉe�p
		CircleShadow::ConstBufferData circleShadows[CircleShadowNum];
	};
	HRESULT result;

private://�ÓI�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;

public:
	//�ÓI�����o�֐�

	static void StaticInitialize(ID3D12Device* device);

public:
	/// <summary>
	/// �C���X�^���X�̐���
	/// </summary>
	/// <returns></returns>
	static LightGroup* Create();

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	//�W�����C�g
	void DefaultLightSetting();

	//���s
	void SetAmbientColor(const XMFLOAT3& color) {
		ambientColor = color;
		dirty = true;
	}

	void SetDirLightActive(int index, bool active) {
		assert(0 <= index && index < DirLightNum);
		dirLights[index].SetActive(active);
	}

	void SetDirLightDir(int index, const Vector4& lightdir) {
		assert(0 <= index && index < DirLightNum);
		dirLights[index].SetLightDir(lightdir);
		dirty = true;
	}
	void SetDirLightColor(int index, const Vector3& lightcolor) {
		assert(0 <= index && index < DirLightNum);
		dirLights[index].SetLightColor(lightcolor);
		dirty = true;
	}

	//�_����
	void SetPointLightActive(int index, bool active) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetActive(active);
	}

	void SetPointLightPos(int index, const XMFLOAT3& lightpos) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetLightPos(lightpos);
		dirty = true;
	}

	void SetPointLightColor(int index, const XMFLOAT3& lightcolor) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetLightColor(lightcolor);
		dirty = true;
	}

	void SetPointLightAtten(int index, const XMFLOAT3& lightAtten) {
		assert(0 <= index && index < PointLightNum);
		pointLights[index].SetLightAtten(lightAtten);
		dirty = true;
	}

	//�X�|�b�g���C�g
	void SetSpotLightActive(int index, bool active) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetActive(active);
	}
	void SetSpotLightDir(int index, const XMVECTOR& lightdir) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightDir(lightdir);
		dirty = true;
	}
	void SetSpotLightPos(int index, const XMFLOAT3& lightpos) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightPos(lightpos);
		dirty = true;
	}
	void SetSpotLightColor(int index, const XMFLOAT3& lightcolor) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightColor(lightcolor);
		dirty = true;
	}
	void SetSpotLightAtten(int index, const XMFLOAT3& lightAtten) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightAtten(lightAtten);
		dirty = true;
	}
	void SetSpotLightFactorAngle(int index, const XMFLOAT2& lightFactorAngle) {
		assert(0 <= index && index < SpotLightNum);
		spotLights[index].SetLightFactorAngle(lightFactorAngle);
		dirty = true;
	}


	//�V���h�E
	void SetCircleShadowActive(int index, bool active) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetActive(active);
	}

	void SetCircleShadowCasterPos(int index, const XMFLOAT3& casterPos) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetCasterPos(casterPos);
		dirty = true;
	}

	void SetCircleShadowDir(int index, const XMVECTOR& lightdir) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetDir(lightdir);
		dirty = true;
	}

	void SetCircleShadowDistanceCasterLight(int index, float distanceCasterLight) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetDistanceCasterLight(distanceCasterLight);
		dirty = true;
	}

	void SetCircleShadowAtten(int index, const XMFLOAT3& lightAtten) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetAtten(lightAtten);
		dirty = true;
	}

	void SetCircleShadowFactorAngle(int index, const XMFLOAT2& lightFactorAngle) {
		assert(0 <= index && index < CircleShadowNum);
		circleShadows[index].SetFactorAngle(lightFactorAngle);
		dirty = true;
	}



private:
	//�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//�����̐F
	XMFLOAT3 ambientColor = { 1,1,1 };

	//���s�����̔z��
	DirectionalLight dirLights[DirLightNum];
	//�_�����̔z��
	PointLight pointLights[PointLightNum];
	//�X�|�b�g���C�g�z��
	SpotLight spotLights[SpotLightNum];
	//�ۉe�̔z��
	CircleShadow circleShadows[CircleShadowNum];

	//�_�[�e�B�t���O
	bool dirty = false;

};