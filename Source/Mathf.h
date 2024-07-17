#pragma once
#include <DirectXMath.h>
// ®¬Zp
class Mathf
{
public:
	//sñXV
	static void UpdateTransform(DirectX::XMFLOAT4X4& transform, DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 scale, DirectX::XMFLOAT3 rotation);

	//OÏ
    static float Cross(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    //àÏ
    static float Dot(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

    // 2ÂÌXMFLOAT3ÌÔÌpxðÔ·Ö
    static float Angle(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//_©ç_Ì£
    static float Distance(DirectX::XMFLOAT3 A, DirectX::XMFLOAT3 B);

	//ü`â®
	static float Lerp(float a, float b, float t);

	// wèÍÍÌ_lðfloat^ÅvZ·é
	static float RandomRange(float min, float max);
};