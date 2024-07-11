#include <stdlib.h>
#include "Mathf.h"

void Mathf::UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation)
{
    //�X�P�[���s����쐬
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    //��]�s����쐬
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
    //�ʒu�s����쐬
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    //3�̍s���g�ݍ��킹�A���[���h�s����쐬
    DirectX::XMMATRIX W = S * R * T;
    //�v�Z�������[���h�s������o��
    DirectX::XMStoreFloat4x4(&transform, W);
}

//�O��
float Mathf::Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    return DirectX::XMVectorGetX(DirectX::XMVector3Cross(a, b));
}

//����
float Mathf::Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    return DirectX::XMVectorGetX(DirectX::XMVector3Dot(a, b));
}

//���`�⊮
float Mathf::Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

// �w��͈͂̃����_���l��float�^�Ōv�Z����
float Mathf::RandomRange(float min, float max)
{
	// 0.0�`1.0�̊Ԃ܂ł̃����_���l
	float value = static_cast<float>(rand()) / RAND_MAX;

	// min�`max�܂ł̃����_���l�ɕϊ�
	return min + (max - min) * value;
}

// 2��XMFLOAT3�̊Ԃ̒�����Ԃ��֐�
float Mathf::Pythagoras(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR AV = DirectX::XMLoadFloat3(&A);
    DirectX::XMVECTOR BV = DirectX::XMLoadFloat3(&B);
    DirectX::XMVECTOR Dir = {};
    Dir = DirectX::XMVectorSubtract(AV, BV);
    Dir = DirectX::XMVector3Length(Dir);
    return DirectX::XMVectorGetX(Dir);
}
