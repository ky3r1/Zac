#pragma once
#include <DirectXMath.h>
// ���������Z�p
class Mathf
{
public:
	//�s��X�V
	static void UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation);

	//���K��
    static DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 A);

	//����
    static float Length(DirectX::XMFLOAT3 A);

	//�O��
    static float Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    //����
    static float Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    // 2��XMFLOAT3�̊Ԃ̊p�x��Ԃ��֐�
    static float Angle(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//�_����_�̋���
    static float Distance(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	static DirectX::XMFLOAT3 Distance3(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//����
    static bool Equal(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	//�قړ���
	static bool NearlyEqual(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B,DirectX::XMFLOAT3 E);

	//���`�⊮
	static float Lerp(float a, float b, float t);

	// �w��͈͂̃����_���l��float�^�Ōv�Z����
	static float RandomRange(float min, float max);

	//+���Z
	static DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	//-���Z
	static DirectX::XMFLOAT3 Subtruct(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

};