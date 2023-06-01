#include"PostEffect.hlsli"


Texture2D<float4> tex0 : register(t0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
Texture2D<float4> tex1 : register(t1); // 1�ԃX���b�g�ɐݒ肳�ꂽ�e�N�X�`��
SamplerState smp : register(s0); // 0�ԃX���b�g�ɐݒ肳�ꂽ�T���v���[

float4 main(VSOutput input) : SV_TARGET
{

    float offsetU = 1 / 1280.0f;
    float offsetV = 1 / 720.0f;

    if (shadeNumber == 0)
    {
        float4 colortex0 = tex0.Sample(smp, input.uv);
        float4 colortex1 = tex1.Sample(smp, input.uv);

		//�|���鋭�x
        int kernelSize = KernelSize;

		// ���ϒl���v�Z���邽�߂̑��a
        float4 sum = float4(0, 0, 0, 0);

		// �J�[�l���T�C�Y�͈͓̔��Ńs�N�Z�����C�e���[�g
        for (int y = -kernelSize; y <= kernelSize; ++y)
        {
            for (int x = -kernelSize; x <= kernelSize; ++x)
            {
                float2 offset = float2(x, y) * float2(offsetU, offsetV);
                float4 colortex0 = tex0.Sample(smp, input.uv + offset);
                sum += colortex0;
            }
        }

		// ���a���J�[�l���T�C�Y�Ŋ��邱�Ƃŕ��ϒl���v�Z
        float kernelArea = (2 * kernelSize + 1) * (2 * kernelSize + 1);
        float4 averageColor = sum / kernelArea;

        float4 color = averageColor;

        if (fmod(input.uv.y, 0.1f) < 0.05f)
        {
            color = colortex1;
        }
        return float4(color.rgb, 1);
    }
    else if (shadeNumber == 1)
    {
        float2 uv = input.uv;
        float2 direction = uv - center;
        float2 step = direction / float(samples);

        float4 result = tex0.Sample(smp, uv);
        float totalWeight = 1.0;
        for (int i = 1; i < samples; ++i)
        {
            float weight = (float(samples) - float(i)) / float(samples);
            float2 sampleUV = uv - step * float(i) * intensity;
            result += tex0.Sample(smp, sampleUV) * weight;
            totalWeight += weight;
        }

        result /= totalWeight;
        return result;
    }
    return float4(1, 1, 1, 1);
}