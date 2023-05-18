#pragma once
#include"DirectXCommon.h"
#include "WinApp.h"
#include <DirectXTex.h>
#include <array>
#include <string>

#include "Affin.h"

class PostEffect
{
public:
	PostEffect();
	//~PostEffect();

	void Update();

	void Draw(ID3D12GraphicsCommandList* cmdList);

public: // �X�v���C�g�R�������玝���Ă�������
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	struct Vertex
	{
		Vector3 pos; // xyz���W
		Vector2 uv;  // uv���W
	};
	// �萔�o�b�t�@�p�f�[�^�\���́i�}�e���A���j
	struct ConstBufferDataMaterial {
		Vector4 color; // �F (RGBA)
	};
	//�萔�o�b�t�@�p�\���́i�RD�ϊ��s��j
	struct ConstBufferDataTransform {
		Matrix4 mat;	//3D�ϊ��s��
	};
	//���_�ԍ�
	enum VertexNumber {
		LB,//����
		LT,//����
		RB,//�E��
		RT,//�E��
	};
public:
	PostEffect(uint32_t texNum,
		Vector2 pos,
		Vector2 size,
		Vector4 color,
		Vector2 anchorP,
		bool swapLR,
		bool swapUD);

	//������
	void InitializeGraphicsPipeline(DirectXCommon* dxcommon);
	void Initialize( uint32_t textureIndex);

	//DirectXCommon* GetDxCommon() { return dxcommon_; }
	//ID3D12RootSignature* GetRootSignature() { return rootSignature.Get(); }
	//ID3D12PipelineState* GetPipelineState() { return pipelineState.Get(); }
	//ID3D12DescriptorHeap* GetSrvHeap() { return srvHeap.Get(); }
	//D3D12_CPU_DESCRIPTOR_HANDLE GetSrvHandle() { return srvHandle; }
	//UINT GetSizeVB() { return sizeVB; }
	//D3D12_RESOURCE_DESC& GetResourceDesc() { return resDesc; }

	void LoadTexture(uint32_t index, const std::string& fileName);

	//void SetTextureCommands(uint32_t index);

	Microsoft::WRL::ComPtr<ID3D12Resource> GetTextureBuffer(uint32_t index)const { return texBuff[index].Get(); }

	//SRV�p�f�X�N���v�^�q�[�v
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> srvHeap = nullptr;
private:
	// ���_�f�[�^
	Vertex vertices[4] = {
		// x      y     z       u     v
		{{-0.4f, -0.7f, 0.0f}, {0.0f, 1.0f}}, // ����
		{{-0.4f, +0.7f, 0.0f}, {0.0f, 0.0f}}, // ����
		{{+0.4f, -0.7f, 0.0f}, {1.0f, 1.0f}}, // �E��
		{{+0.4f, +0.7f, 0.0f}, {1.0f, 0.0f}}, // �E��
	};
	// SRV�̍ő��
	static const size_t kMaxSRVCount = 2056;

	DirectXCommon* dxcommon_;
	ComPtr<ID3DBlob> vsBlob; // ���_�V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> psBlob; // �s�N�Z���V�F�[�_�I�u�W�F�N�g
	ComPtr<ID3DBlob> errorBlob; // �G���[�I�u�W�F�N�g
	HRESULT result;

	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v�����X�e�[�g�̐���
	ComPtr<ID3D12PipelineState> pipelineState;
	std::array<ComPtr<ID3D12Resource>, kMaxSRVCount>texBuff;

	//�������s�N�Z����
	const size_t textureWidth = 256;
	//�c�����s�N�Z����
	const size_t textureHeight = 256;
	//�z��̗v�f��
	const size_t imageDataCount = textureWidth * textureHeight;

	//SRV�q�[�v�̐擪�n���h�����擾
	D3D12_CPU_DESCRIPTOR_HANDLE srvHandle;

	TexMetadata metadata{};
	ScratchImage scratchImg{};
	D3D12_HEAP_PROPERTIES textureHeapProp{};
	D3D12_RESOURCE_DESC textureResourceDesc{};

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc{};
	// �O���t�B�b�N�X�p�C�v���C���ݒ�
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};
	// �f�X�N���v�^�q�[�v�̐ݒ�
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};

	UINT sizeVB;

	D3D12_RESOURCE_DESC resDesc{};

	//�f�t�H���g�e�N�X�`���i�[�f�B���N�g��
	static std::string kDefaultTextureDirectoryPath;

	UINT incrementSize;

public: // �X�v���C�g���玝���Ă�������
		//void SetPozition(const Vector2& position_);

		const Vector2& GetPosition() const { return position; }

		//void SetRotation(float rotation_);

		float GetRotation() { return rotation; }

		void SetColor(const Vector4& color_) { color = color_; }

		Vector4 GetColor() { return color; }

		void SetScale(const Vector3& scale_) { scale = scale_; }

		Vector3 GetScale() { return scale; }

		void SetAnchorPoint(const Vector2& anchorPoint_) { anchorPoint = anchorPoint_; }

		Vector2 GetAnchorPoint() { return anchorPoint; }

		//void SetTextureIndex(uint32_t texNmb) { textureIndex_ = texNmb; AdjustTextureSize(); }

		uint32_t GetTextureIndex() { return textureIndex_; }

		void SetTexSize(Vector2 texSize) { textureSize = texSize; }

		Vector2 GetTexSize() { return textureSize; }

		Vector2 GetSize() { return size_; }

		//void SetSize(Vector2 size);

		/// �㉺���]�̐ݒ�
		//void SetIsFlipY(bool isFlipY);

		/// ���E���]�̐ݒ�
		//void SetIsFlipX(bool isFlipX);
private:

	//�e�N�X�`���T�C�Y���C���[�W�ɍ��킹��
	void AdjustTextureSize();	

	// ���_�o�b�t�@�r���[�̍쐬
	D3D12_VERTEX_BUFFER_VIEW vbView{};

	Matrix4 matScale;//�X�P�[�����O�s��
	Matrix4 matWorld;
	Matrix4 matRot;//��]�s��
	Matrix4  matTrans;//���s�ړ��s��

	//���W
	Vector3 scale{ 0.5f, 0.5f, 1.0f };

	Vector2 size_ = { 100.0f,100.0f };

	float rotation = 0.0f;
	Vector2 position = { 0.0f, 0.0f };

	Vector4 color = { 1,1,1,1 };

	Vector2 anchorPoint = { 0.0f,0.0f };

	ComPtr<ID3D12Resource> constBuffTransform;
	ConstBufferDataTransform* constMapTransform = nullptr;

	ConstBufferDataMaterial* constMapMaterial = nullptr;

	ComPtr<ID3D12Resource> constBuffMaterial;

	Vertex vertices_[4];

	Vertex* vertMap = nullptr;

	//�e�N�X�`���ԍ�
	uint32_t textureIndex_ = 0;

	//�e�N�X�`��������W
	Vector2 textureLeftTop = { 0.0f,0.0f };
	//�e�N�X�`���؂�o���T�C�Y
	Vector2 textureSize = { 100.0f,100.0f };

	Matrix4 matProjection;

	// �A���J�[�|�C���g
	Vector2 anchorpoint = { 0, 0 };

	// ���_�o�b�t�@�̐���
	ComPtr<ID3D12Resource> vertBuff = nullptr;

	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
};

