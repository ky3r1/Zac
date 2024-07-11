#pragma once
#include <DirectXMath.h>
// ���������Z�p
class Mathf
{
public:
	//�s��X�V
	static void UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation);

	//�O��
    static float Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    //����
    static float Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//���`�⊮
	static float Lerp(float a, float b, float t);

	// �w��͈͂̃����_���l��float�^�Ōv�Z����
	static float RandomRange(float min, float max);

	// 2��XMFLOAT3�̊Ԃ̒�����Ԃ��֐�
	static float Pythagoras(DirectX::XMFLOAT3 A,DirectX::XMFLOAT3 B);
};