#pragma once

#include "All.h"
#include "Camera.h"

class CameraController
{
public:
	// カメラからコントローラーへパラメータを同期する
	void SyncCameraToController(const Camera& camera);

	// コントローラーからカメラへパラメータを同期する
	void SyncControllerToCamera(Camera& camera);

	// 更新処理
	void Update(DirectX::XMFLOAT3 target);

	// 更新処理
	void UpdateKey(float elapsedTime,DirectX::XMFLOAT3 target);

	//デバッグ用Imgui表示
	void DrawDebugGUI();
private:
	DirectX::XMFLOAT3		eye;
	DirectX::XMFLOAT3		focus;
	DirectX::XMFLOAT3		up;
	DirectX::XMFLOAT3		right;
	float					distance;
	DirectX::XMFLOAT3		angle;
};