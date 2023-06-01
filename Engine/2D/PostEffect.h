#pragma once
#include"DirectXCommon.h"
#include "WinApp.h"
#include <DirectXTex.h>
#include <array>
#include <string>

#include "Affin.h"

class PostEffect
{
protected: // �G�C���A�X
    // Microsoft::WRL::���ȗ�
    template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
    // DirectX::���ȗ�

public:
    /// <summary>
    /// ���_�f�[�^�\����
    /// </summary>
    struct VertexPosUv {
        Vector3 pos; // xyz���W
        Vector2 uv;  // uv���W
    };

    /// <summary>
    /// �萔�o�b�t�@�p�f�[�^�\����
    /// </summary>
    struct ConstBufferData {
        Vector4 color; // �F (RGBA)
        Matrix4 mat;   // �R�c�ϊ��s��
    };

    //GPU
    struct SendDataGPU {
        int shadeNumber;
        int kernelSize;
        Vector2 center;
        float intensity;
        int samples;
    };

    //�f�t�H���g�e�N�X�`���i�[�f�B���N�g��
    std::string kDefaultTextureDirectoryPath = "Resources/";
    HRESULT result;
public:

    static void Initialize(DirectXCommon* dxCommon);

    static void Finalize();

    /// <summary>
    /// �p�C�v���C������
    /// </summary>
    static void CreatGraphicsPipeline();

    /// <summary>
    /// �V�[���`��O����
    /// </summary>
    /// <param name="cmdList">�R�}���h���X�g</param>
    static void PreDrawScene(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`�揈��
    /// </summary>
    static void Draw(ID3D12GraphicsCommandList* cmdList);

    /// <summary>
    /// �V�[���`��㏈��
    /// </summary>
    /// <param name="cmdList">�R�}���h����</param>
    static void PostDrawScene();

    static void SetShadeNumber(int SetShadeNumber);

    static void SetKernelSize(int range);

    static void SetRadialBlur(Vector2 senter, float intensity, int sample);

private://�ÓI�����o�ϐ�
    static const float clearColor[4];

    static ID3D12Device* device_;

    static ID3D12GraphicsCommandList* commandList;

    static VertexPosUv vertices[4];

    static VertexPosUv* vertMap;

    static ComPtr<ID3D12Resource> vertBuff;	//���_�o�b�t�@

    //���_�o�b�t�@�r���[�̍쐬
    static D3D12_VERTEX_BUFFER_VIEW vbView;
    static ComPtr<ID3D12Resource> texBuff[2];

    static ComPtr<ID3D12DescriptorHeap> descHeapSRV;
    //�[�x�o�b�t�@
    static ComPtr<ID3D12Resource> depthBuff;
    //RTV�p�̃f�X�N���v�^�q�[�v
    static ComPtr<ID3D12DescriptorHeap> descHeapRTV;
    //DSV�p�̃f�X�N���v�^�q�[�v
    static ComPtr<ID3D12DescriptorHeap> descHeapDSV;

    static ComPtr<ID3D12PipelineState> pipelineState;
    static ComPtr<ID3D12RootSignature> rootSignature;
private:
    // �萔�o�b�t�@
    static ComPtr<ID3D12Resource> constDataBuff_;
    // �}�b�s���O�ς݃A�h���X
    static SendDataGPU* dataMap;
};

