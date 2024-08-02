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

DirectX::XMFLOAT3 Mathf::Normalize(DirectX::XMFLOAT3 A)
{
    DirectX::XMVECTOR a= DirectX::XMLoadFloat3(&A);
    DirectX::XMVector3Normalize(a);
    DirectX::XMFLOAT3 A_n = {};
    DirectX::XMStoreFloat3(&A_n, a);
    return A_n;
}

float Mathf::Length(DirectX::XMFLOAT3 A)
{
    DirectX::XMVECTOR a = DirectX::XMLoadFloat3(&A);
    return DirectX::XMVectorGetX(DirectX::XMVector3Length(a));
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

//�p�x
float Mathf::Angle(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    return DirectX::XMVectorGetX(DirectX::XMVector3AngleBetweenNormals(a, b));
}

//����
float Mathf::Distance(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
DirectX::XMVECTOR a, b;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    return DirectX::XMVectorGetX(DirectX::XMVector3Length(DirectX::XMVectorSubtract(a, b)));
}
DirectX::XMFLOAT3 Mathf::Distance3(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMFLOAT3 result;
    result.x=sqrtf((A.x - B.x)*(A.x - B.x));
    result.y=sqrtf((A.y - B.y)*(A.y - B.y));
    result.z=sqrtf((A.z - B.z)*(A.z - B.z));
    return result;
}

bool Mathf::Equal(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    if (A.x == B.x && A.y == B.y && A.z == B.z)
    {
        return true;
    }
    return false;
}

bool Mathf::NearlyEqual(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B, DirectX::XMFLOAT3 E)
{
    if (A.x <= B.x + E.x && A.x >= B.x - E.x &&
        A.y <= B.y + E.y && A.y >= B.y - E.y &&
        A.z <= B.z + E.z && A.z >= B.z - E.z)
    {
        return true;
    }
    return false;
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

DirectX::XMFLOAT3 Mathf::Add(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    DirectX::XMFLOAT3 result;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    DirectX::XMStoreFloat3(&result, DirectX::XMVectorAdd(a,b));
    return result;
}

DirectX::XMFLOAT3 Mathf::Subtruct(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    DirectX::XMFLOAT3 result;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    DirectX::XMStoreFloat3(&result, DirectX::XMVectorSubtract(a, b));
    return result;
}
