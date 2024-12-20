#pragma once
#include <DirectXMath.h>
// ®¬Zp
class Mathf
{
public:
	//sñXV
	static void UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation);

	//³K»
    static DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3 A);

	//·³
    static float Length(DirectX::XMFLOAT3 A);

	//OÏ
    static float Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    //àÏ
    static float Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    // 2ÂÌXMFLOAT3ÌÔÌpxðÔ·Ö
    static float Angle(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//_©ç_Ì£
    static float Distance(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	static DirectX::XMFLOAT3 Distance3(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//
    static bool Equal(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	//ÙÚ
	static bool NearlyEqual(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B,DirectX::XMFLOAT3 E);

	//ü`â®
	static float Lerp(float a, float b, float t);

	// wèÍÍÌ_lðfloat^ÅvZ·é
	static float RandomRange(float min, float max);

	//+Z
	static DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);
	//-Z
	static DirectX::XMFLOAT3 Subtruct(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//tÌsxAñyÌlðÔ·
	float GetTransform(DirectX::XMFLOAT4X4 t, int x, int y);
};