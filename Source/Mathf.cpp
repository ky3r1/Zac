#include <stdlib.h>
#include "Mathf.h"

void Mathf::UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation)
{
    //スケール行列を作成
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    //回転行列を作成
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
    //位置行列を作成
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    //3つの行列を組み合わせ、ワールド行列を作成
    DirectX::XMMATRIX W = S * R * T;
    //計算したワールド行列を取り出す
    DirectX::XMStoreFloat4x4(&transform, W);
}

//外積
float Mathf::Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    return DirectX::XMVectorGetX(DirectX::XMVector3Cross(a, b));
}

//内積
float Mathf::Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR a, b;
    a = DirectX::XMLoadFloat3(&A);
    b = DirectX::XMLoadFloat3(&B);
    return DirectX::XMVectorGetX(DirectX::XMVector3Dot(a, b));
}

//線形補完
float Mathf::Lerp(float a, float b, float t)
{
	return a * (1.0f - t) + (b * t);
}

// 指定範囲のランダム値をfloat型で計算する
float Mathf::RandomRange(float min, float max)
{
	// 0.0～1.0の間までのランダム値
	float value = static_cast<float>(rand()) / RAND_MAX;

	// min～maxまでのランダム値に変換
	return min + (max - min) * value;
}

// 2つのXMFLOAT3の間の長さを返す関数
float Mathf::Pythagoras(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B)
{
    DirectX::XMVECTOR AV = DirectX::XMLoadFloat3(&A);
    DirectX::XMVECTOR BV = DirectX::XMLoadFloat3(&B);
    DirectX::XMVECTOR Dir = {};
    Dir = DirectX::XMVectorSubtract(AV, BV);
    Dir = DirectX::XMVector3Length(Dir);
    return DirectX::XMVectorGetX(Dir);
}
