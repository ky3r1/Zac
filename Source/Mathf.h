#pragma once
#include <DirectXMath.h>
// 浮動小数算術
class Mathf
{
public:
	//行列更新
	static void UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation);

	//正規化
    static DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 A);

	//長さ
    static float Length(DirectX::XMFLOAT3 A);

	//外積
    static float Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    //内積
    static float Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    // 2つのXMFLOAT3の間の角度を返す関数
    static float Angle(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//点から点の距離
    static float Distance(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	static DirectX::XMFLOAT3 Distance3(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//等号
    static bool Equal(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	//ほぼ等号
	static bool NearlyEqual(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B,DirectX::XMFLOAT3 E);

	//線形補完
	static float Lerp(float a, float b, float t);

	// 指定範囲のランダム値をfloat型で計算する
	static float RandomRange(float min, float max);

	//+演算
	static DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	//-演算
	static DirectX::XMFLOAT3 Subtruct(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

};