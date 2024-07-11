#pragma once
#include <DirectXMath.h>
// 浮動小数算術
class Mathf
{
public:
	//行列更新
	static void UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation);

	//外積
    static float Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    //内積
    static float Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//線形補完
	static float Lerp(float a, float b, float t);

	// 指定範囲のランダム値をfloat型で計算する
	static float RandomRange(float min, float max);

	// 2つのXMFLOAT3の間の長さを返す関数
	static float Pythagoras(DirectX::XMFLOAT3 A,DirectX::XMFLOAT3 B);
};