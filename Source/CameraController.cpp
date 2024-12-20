#include <imgui.h>
#include "CameraController.h"
#include "Input/Input.h"

#define MAXANGLE_X 3.14f * 0.5f-0.01f
#define MINANGLE_X 0.1f

// カメラからコントローラーへパラメータを同期する
void CameraController::SyncCameraToController(const Camera& camera)
{
	eye = camera.GetEye();
	focus = camera.GetFocus();
	up = camera.GetUp();
	right = camera.GetRight();

	// 視点から注視点までの距離を算出
	DirectX::XMVECTOR Eye = DirectX::XMLoadFloat3(&eye);
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(Focus, Eye);
	DirectX::XMVECTOR Distance = DirectX::XMVector3Length(Vec);
	DirectX::XMStoreFloat(&distance, Distance);

	// 回転角度を算出
	const DirectX::XMFLOAT3& front = camera.GetFront();
	angle.x = ::asinf(-front.y);
	if (up.y < 0)
	{
		if (front.y > 0)
		{
			angle.x = -DirectX::XM_PI - angle.x;
		}
		else
		{
			angle.x = DirectX::XM_PI - angle.x;
		}
		angle.y = ::atan2f(front.x, front.z);
	}
	else
	{
		angle.y = ::atan2f(-front.x, -front.z);
	}
}

// コントローラーからカメラへパラメータを同期する
void CameraController::SyncControllerToCamera(Camera& camera)
{
	camera.SetLookAt(eye, focus, up);
}

// 更新処理
void CameraController::Update(float elapsedTime, DirectX::XMFLOAT3 target, Camera& camera)
{
	// デバッグウインドウ操作中は処理しない
	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow))
	{
		return;
	}

	// IMGUIのマウス入力値を使ってカメラ操作する
	ImGuiIO io = ImGui::GetIO();

	// マウスカーソルの移動量を求める
	float moveX = io.MouseDelta.x * 0.02f;
	float moveY = io.MouseDelta.y * 0.02f;

	// マウス左ボタン押下中
	if (io.MouseDown[ImGuiMouseButton_Right])
	{
		// Y軸回転
		angle.y += moveX * 0.5f;
		if (angle.y > DirectX::XM_PI)
		{
			angle.y -= DirectX::XM_2PI;
		}
		else if (angle.y < -DirectX::XM_PI)
		{
			angle.y += DirectX::XM_2PI;
		}
		// X軸回転
		angle.x += moveY * 0.5f;
		if (angle.x > DirectX::XM_PI)
		{
			angle.x -= DirectX::XM_2PI;
		}
		else if (angle.x < -DirectX::XM_PI)
		{
			angle.x += DirectX::XM_2PI;
		}
	}
	// マウス中ボタン押下中
	else if (io.MouseDown[ImGuiMouseButton_Middle])
	{
		// 平行移動
		float s = distance * 0.035f;
		float x = moveX * s;
		float y = moveY * s;

		focus.x -= right.x * x;
		focus.y -= right.y * x;
		focus.z -= right.z * x;

		focus.x += up.x * y;
		focus.y += up.y * y;
		focus.z += up.z * y;
	}
	// マウス右ボタン押下中
	else if (io.MouseDown[ImGuiMouseButton_Left] && io.MouseDown[ImGuiMouseButton_Right])
	{
		// ズーム
		distance += (-moveY - moveX) * distance * 0.1f;
	}
	// マウスホイール
	else if (io.MouseWheel != 0)
	{
		// ズーム
		distance -= io.MouseWheel * distance * 0.1f;
	}

	float sx = ::sinf(angle.x);
	float cx = ::cosf(angle.x);
	float sy = ::sinf(angle.y);
	float cy = ::cosf(angle.y);

	// カメラの方向を算出
	DirectX::XMVECTOR Front = DirectX::XMVectorSet(-cx * sy, -sx, -cx * cy, 0.0f);
	DirectX::XMVECTOR Right = DirectX::XMVectorSet(cy, 0, -sy, 0.0f);
	DirectX::XMVECTOR Up = DirectX::XMVector3Cross(Right, Front);
	// カメラの視点＆注視点を算出
	DirectX::XMVECTOR Focus = DirectX::XMLoadFloat3(&focus);
	DirectX::XMVECTOR Distance = DirectX::XMVectorSet(distance, distance, distance, 0.0f);
	DirectX::XMVECTOR Eye = DirectX::XMVectorSubtract(Focus, DirectX::XMVectorMultiply(Front, Distance));
	// ビュー行列からワールド行列を算出
	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtLH(Eye, Focus, Up);
	DirectX::XMMATRIX World = DirectX::XMMatrixTranspose(View);
	// ワールド行列から方向を算出
	Right = DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(1, 0, 0, 0), World);
	Up = DirectX::XMVector3TransformNormal(DirectX::XMVectorSet(0, 1, 0, 0), World);

	// 結果を格納
	DirectX::XMFLOAT4X4 view, projection;
    DirectX::XMStoreFloat4x4(&view, View);
    DirectX::XMStoreFloat4x4(&projection, World);
	DirectX::XMStoreFloat3(&eye, Eye);
	DirectX::XMStoreFloat3(&up, Up);
	DirectX::XMStoreFloat3(&right, Right);

	//回転行列から前方向ベクトルを取り出す
	Front = World.r[2];
	DirectX::XMFLOAT3 front;
	DirectX::XMStoreFloat3(&front, Front);

	//注視点から後ろベクトル方向に一定距離離れたカメラ視点を求める
	//DirectX::XMFLOAT3 eye;
	eye.x = target.x - front.x * distance / 1.0f;
	eye.y = target.y - front.y * distance / 1.0f;
	eye.z = target.z - front.z * distance / 1.0f;

	//カメラの視点と注視点を設定
	//CameraManager::Instance().GetMainCamera().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
	camera.SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
	CameraShake(elapsedTime, camera);
}

void CameraController::UpdateKey(float elapsedTime, DirectX::XMFLOAT3 target, Camera& camera)
{
	GamePad& gamePad = Input::Instance().GetGamePad();
	float ax = gamePad.GetAxisRX();
	float ay = gamePad.GetAxisRY();

	DirectX::XMFLOAT3	angle = DirectX::XMFLOAT3(0, 0, 0);

	static DirectX::XMFLOAT3	cameraAngle = DirectX::XMFLOAT3(0, 0, 0);
	static float				cameraRollSpeed = DirectX::XMConvertToRadians(90);
	static float				cameraMaxPitch = DirectX::XMConvertToRadians(45);
	static float				cameraMinPitch = DirectX::XMConvertToRadians(-45);
	static float				cameraRange = 100.0f;
	static 	float				characterHeight = 10.0f;
	float lengthSq = ax * ax + ay * ay;
	if (lengthSq > 0.1f)
	{
		float speed = cameraRollSpeed * elapsedTime;

		cameraAngle.x += ay * speed;
		cameraAngle.y += ax * speed;

		if (cameraAngle.x < cameraMinPitch)
		{
			cameraAngle.x = cameraMinPitch;
		}
		if (cameraAngle.x > cameraMaxPitch)
		{
			cameraAngle.x = cameraMaxPitch;
		}
		if (cameraAngle.y < -DirectX::XM_PI)
		{
			cameraAngle.y += DirectX::XM_2PI;
		}
		if (cameraAngle.y > DirectX::XM_PI)
		{
			cameraAngle.y -= DirectX::XM_2PI;
		}
	}

	DirectX::XMVECTOR Offset = DirectX::XMVectorSet(0.0f, characterHeight, 0.0f, 0.0f);
	DirectX::XMVECTOR Target = DirectX::XMLoadFloat3(&target);
	DirectX::XMVECTOR Focus = DirectX::XMVectorAdd(Target, Offset);
	DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(cameraAngle.x, cameraAngle.y, cameraAngle.z);
	DirectX::XMVECTOR Range = DirectX::XMVectorSet(0.0f, 0.0f, -cameraRange, 0.0f);
	DirectX::XMVECTOR Vec = DirectX::XMVector3TransformCoord(Range, Transform);
	DirectX::XMVECTOR Eye = DirectX::XMVectorAdd(Focus, Vec);

	DirectX::XMFLOAT3 eye, focus;
	DirectX::XMStoreFloat3(&eye, Eye);
	DirectX::XMStoreFloat3(&focus, Focus);
	//Camera* camera = ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>().get();
	camera.SetLookAt(eye, focus, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::DrawDebugGUI()
{
}

void CameraController::CameraShake(float elapsedTime, Camera& camera)
{
	if (camera.GetCameraShake())
	{
		static int num = 0;
		static float shake_time = 1.0f;
		switch (num)
		{
		case 0:
			shake_time = camera.GetShakeTime();
            num = 1;
			break;
		case 1:
			//カメラシェイクする時間
			shake_time -= elapsedTime;
			if (shake_time < 0)
			{
				shake_time = 1.0f;
				num = 0;
				camera.SetCameraShake(false);
			}

			// カメラシェイク処理
			{
				// -1.0~1.0のランダム値を取得する関数
				auto getRand = []()->float
				{
					return rand() / (float)RAND_MAX * 2.0f - 1.0f;
				};

				//// ヒットストップ時間が少なくとも揺れが小さくなるようにする係数
				//float t = hitStopLastSeconds / hitStopSecondsLength;

				// 注視点を揺らすオフセット値を求める
				DirectX::XMFLOAT3 shake;
				float cameraShakeRange = camera.GetShakeRange();
				shake.x = getRand() * shake_time * cameraShakeRange;
				shake.y = getRand() * shake_time * cameraShakeRange;
				shake.z = getRand() * shake_time * cameraShakeRange;

				// 注視点に揺れ値を加える
				DirectX::XMFLOAT3 focus = camera.GetFocus();
				focus.x += shake.x;
				focus.y += shake.y;
				focus.z += shake.z;

				camera.SetLookAt(camera.GetEye(), focus, camera.GetUp());
				break;
			}
		}

	}
}
