#include "StageManager.h"

///Component///
//Stage
#include "StageMain.h"

//Character
#include "Player.h"
#include "Enemy.h"

//Camera
#include "Camera.h"

#include "Mathf.h"

#define NoneS
#define MainS

void StageManager::Initialize()
{
	screenWidth = Graphics::Instance().GetScreenWidth();
	screenHeight = Graphics::Instance().GetScreenHeight();
	switch (stage_num)
	{
	case StageNumber::None:
		NoneInitialize();
		break;
	case StageNumber::MainStage:
        MainStageInitialize();
        break;
	default:
		break;
	}
}

void StageManager::Finalize()
{
	ActorManager::Instance().Clear();
	for (int i = 0; i < sizeof(actor_imgui_checker); i++)
	{
		actor_imgui_checker[i] = false;
	}
	switch (stage_num)
	{
	default:
		break;
	}
}

void StageManager::Update(float elapsedTime)
{
	//Actor更新
	ActorManager::Instance().Update(elapsedTime);

	//カメラ更新処理
	{
		Actor* player = ActorManager::Instance().GetActor("Player");
		Camera* camera = ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>().get();
		camera_controller.Update(elapsedTime, player->GetPosition(), *camera);
	}

	switch (stage_num)
	{
	case StageNumber::None:
		NoneUpdate(elapsedTime);
		break;
	case StageNumber::MainStage:
		break;
	default:
		break;
	}
}

void StageManager::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.4f, 0.4f, 0.4f, 1.0f };	// RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);

	// 描画処理
	RenderContext rc;
	rc.lightDirection = { 0.0f, -1.0f, 0.0f, 0.0f };	// ライト方向（下方向）

	//カメラパラメータ設定
	Actor* camera = ActorManager::Instance().GetActor("MainCamera");
	rc.view = camera->GetComponent<Camera>()->GetView();
	rc.projection = camera->GetComponent<Camera>()->GetProjection();

	{
		// 3Dモデル描画
		{
			Shader* shader = graphics.GetShader();
			shader->Begin(dc, rc);
			// アクター描画
			ActorManager::Instance().UpdateTransform();
			ActorManager::Instance().Render(dc, shader);
			shader->End(dc);
		}

		//3Dエフェクト描画
		{
		}

		// 3Dデバッグ描画
		{
			//プレイヤーデバッグプリミティブ描画
			ActorManager::Instance().DrawDebug();
			// ラインレンダラ描画実行
			graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);
			// デバッグレンダラ描画実行
			graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
		}

		// 2Dスプライト描画
		{
		}

		// デバッグGUI描画
		{
			static bool actor_open = {};
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("Actor"))
				{
					ImGui::MenuItem("All", "", &actor_imgui_checker[static_cast<int>(ActorType::All)]);
					ImGui::MenuItem("Player", "", &actor_imgui_checker[static_cast<int>(ActorType::Player)]);
					ImGui::MenuItem("Enemy", "", &actor_imgui_checker[static_cast<int>(ActorType::Enemy)]);
					ImGui::MenuItem("Stage", "", &actor_imgui_checker[static_cast<int>(ActorType::Stage)]);
					ImGui::MenuItem("Object", "", &actor_imgui_checker[static_cast<int>(ActorType::Object)]);
					ImGui::MenuItem("Bullet", "", &actor_imgui_checker[static_cast<int>(ActorType::Bullet)]);
					ImGui::MenuItem("Camera", "", &actor_imgui_checker[static_cast<int>(ActorType::Camera)]);
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}



			if (actor_imgui_checker[static_cast<int>(ActorType::All)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::All);
			}
			if (actor_imgui_checker[static_cast<int>(ActorType::Player)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::Player);
			}
			if (actor_imgui_checker[static_cast<int>(ActorType::Enemy)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::Enemy);
			}
			if (actor_imgui_checker[static_cast<int>(ActorType::Object)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::Object);
			}
			if (actor_imgui_checker[static_cast<int>(ActorType::Bullet)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::Bullet);
			}
			if (actor_imgui_checker[static_cast<int>(ActorType::Stage)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::Stage);
			}
			if (actor_imgui_checker[static_cast<int>(ActorType::Camera)])
			{
				ActorManager::Instance().DrawDetail();
				ActorManager::Instance().DrawLister(ActorType::Camera);
			}


			for (int i = 0; i < sizeof(actor_imgui_checker); i++)
			{
				if (actor_imgui_checker[i])
				{
					actor_open = true;
					break;
				}
				else actor_open = false;
			}

			//Close
			if (actor_open)
			{
				if (ImGui::Begin("Actor Lister", nullptr, ImGuiWindowFlags_None))
				{
					if (ImGui::Button("Close"))
					{
						for (int i = 0; i < sizeof(actor_imgui_checker); i++)
						{
							actor_imgui_checker[i] = false;
						}
						actor_open = false;
					}
				}
				ImGui::End();
			}
		}
}

	switch (stage_num)
	{
	case StageNumber::None:
		NoneRender();
		break;
	case StageNumber::MainStage:
        MainStageRender();
		break;
	default:
		break;
	}
}

#ifdef NoneS
void StageManager::NoneInitialize()
{
}

void StageManager::NoneUpdate(float elapsedTime)
{
}

void StageManager::NoneRender()
{
}
#endif // NoneS


#ifdef MainS
void StageManager::MainStageInitialize()
{

	// ステージ
	{
		const char* filename = "Data/Model/Stage/stage01.mdl";
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		actor->LoadModel(filename);
		actor->SetName("MainStage");
		actor->SetPosition(DirectX::XMFLOAT3(0, 0, 0));
		actor->SetRotation(DirectX::XMFLOAT4(3.14f * -0.0f, 3.14f * 0.0f, 3.14f * 0.0f, 1));
		actor->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
		actor->SetRaycastFlg(true);
		actor->SetActorType(ActorType::Stage);
		actor->AddComponent<StageMain>();
	}

	// プレイヤー
	//プレイヤーの初期位置を設定(下のCameraの初期位置で使用)
	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(0, 0, -200);
	{
		const char* filename = "Data/Model/Assets/Wizard/Wizard.mdl";
		//const char* filename = "Data/Model/Player/Wraith.mdl";
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		actor->LoadModel(filename);
		actor->SetName("Player");
		actor->SetPosition(position);
		actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
		actor->SetScale(DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f));
		actor->SetWeight(10.0f);
		actor->SetRadius(5.0f);
		actor->SetHeight(15.0f);
		actor->SetActorType(ActorType::Player);
		actor->AddComponent<Player>();
	}

	// カメラ
	{
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		actor->SetName("MainCamera");
		actor->SetActorType(ActorType::Camera);
		actor->AddComponent<Camera>();
		Camera* camera = actor->GetComponent<Camera>().get();
		camera->SetPerspectiveFov(
			DirectX::XMConvertToRadians(45),	// 画角
			screenWidth / screenHeight,			// 画面アスペクト比
			0.1f,								// ニアクリップ
			1000.0f								// ファークリップ
		);
		camera->SetLookAt(
			{ position.x, position.y + 20, position.z - 50 },		// 視点
			position,		// 注視点
			{ 0, 1, 0 }			// 上ベクトル
		);
		camera_controller.SyncCameraToController(*camera);
	}

	//Enemy
	{
		// Enemy
		for (int i = 0; i < 1; i++)
		{
			const char* filename = "Data/Model/Slime/Slime.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			std::string name = std::string("Enemy:") + std::to_string(i);
			actor->SetName(name);
			actor->SetPosition(DirectX::XMFLOAT3(Mathf::RandomRange(-100, 100), 3, Mathf::RandomRange(50, 150)));
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(0.05f, 0.05f, 0.05f));
			actor->SetWeight(9.0f);
			actor->SetRadius(3.0f);
			actor->SetHeight(5.0f);
			actor->SetActorType(ActorType::Enemy);
			actor->AddComponent<Enemy>();
		}
	}
}

void StageManager::MainStageUpdate(float elapsedTime)
{
}

void StageManager::MainStageRender()
{
}
#endif // MainS


