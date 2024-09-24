#include "SceneGame.h"

//Camera
#include "Camera.h"

//Character
#include "Player.h"

//Scene
#include "SceneManager.h"
#include "SceneLoading.h"
#include "SceneResult.h"

//Stage
//#include "StageManager.h"
#include "StageMain.h"
//#include "StageMapChip.h"
//#include "StageMapChip.h"

#include "ProjectileManager.h"

#include "Input/Input.h"
#include "Ui.h"

#include "CameraController.h"
#include "Object.h"
#include "CollisionObject.h"
#include "TrackingObject.h"
#include "SphereTrackingObject.h"
#include "AnimationComp.h"
#include "StateMachine.h"

#include "Mathf.h"

#include "EffectManager.h"
#include "MouseManager.h"

// 初期化
void SceneGame::Initialize()
{
	ID3D11Device* device = Graphics::Instance().GetDevice();
	float screenWidth = Graphics::Instance().GetScreenWidth();
	float screenHeight = Graphics::Instance().GetScreenHeight();

	//ステージ初期化
#ifdef ALLSTAGE
	// ステージ
	{
		const char* filename = "Data/Model/Stage/stage01.mdl";
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		actor->LoadModel(filename);
		actor->SetName("MainStage");
		actor->SetPosition(DirectX::XMFLOAT3(0, 0, 0));
		actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
		actor->SetScale(DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f));
		actor->SetRaycastFlg(true);
		actor->SetActorType(ActorType::Stage);
		actor->AddComponent<StageMain>();
	}
#endif // ALLSTAGE


#ifdef ALLPLAYER
	// プレイヤー
	{
		const char* filename = "Data/Model/Assets/Wizard/Wizard.mdl";
		//const char* filename = "Data/Model/GP5_UnityChan/unitychan.mdl";
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		actor->LoadModel(filename);
		actor->SetName("Player");
		actor->SetPosition(DirectX::XMFLOAT3(0, 0, -200));
		actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
		actor->SetScale(DirectX::XMFLOAT3(10.0f, 10.0f, 10.0f));
		actor->SetWeight(10.0f);
		actor->SetRadius(5.0f);
		actor->SetHeight(15.0f);
		actor->SetActorType(ActorType::Player);
		actor->AddComponent<Movement>();
		actor->AddComponent<VsCollision>();
		actor->AddComponent<AnimationComp>();
		actor->AddComponent<StateMachine>();
		actor->AddComponent<Character>();
		actor->AddComponent<Player>();
	}
#endif // PLAYER
	// カメラ
	{
		std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		actor->SetName("MainCamera");
		actor->SetActorType(ActorType::Camera);
		actor->AddComponent<Camera>();
	}
#ifdef ALLENEMY
	{
		for(int i = 0; i < 5; i++)
		// Enemy
		{
			const char* filename = "Data/Model/Slime/Slime.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			std::string name = std::string("Enemy:") + std::to_string(i);
			actor->SetName(name);
			actor->SetPosition(DirectX::XMFLOAT3(Mathf::RandomRange(-100,100), 3, Mathf::RandomRange(50, 150)));
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(0.05f, 0.05f, 0.05f));
			actor->SetWeight(9.0f);
			actor->SetRadius(3.0f);
			actor->SetHeight(5.0f);
			actor->SetActorType(ActorType::Enemy);
			actor->AddComponent<Movement>();
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Character>();
			actor->AddComponent<Enemy>();
		}
		//// Enemy
		//{
		//	const char* filename = "Data/Model/Slime/Slime.mdl";
		//	std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
		//	actor->LoadModel(filename);
		//	actor->SetName("Enemy01");
		//	actor->SetPosition(DirectX::XMFLOAT3(20, 00, 00));
		//	actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
		//	actor->SetScale(DirectX::XMFLOAT3(0.05f, 0.05f, 0.05f));
		//	actor->SetColor(DirectX::XMFLOAT4(0.0f, 0.05f, 1.05f, 1.0f));
		//	actor->SetWeight(5.0f);
		//	actor->SetRadius(3.0f);
		//	actor->SetHeight(5.0f);
		//	actor->SetActorType(ActorType::Enemy);
		//	actor->AddComponent<Movement>();
		//	actor->AddComponent<VsCollision>();
		//	actor->AddComponent<Enemy>();
		//}
	}
#ifdef ENEMY01
	
#endif // ENEMY01
#ifdef ENEMY02

#endif // ENEMY02
#ifdef ENEMY03

#endif // ENEMY03
#ifdef ENEMYBOSS

#endif // ENEMYBOSS
#endif // ALLENEMY

#ifdef OBJECT	
	{
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object00");
			actor->SetPosition(DirectX::XMFLOAT3(300, 00, 00));
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(20.0f, 20.0f, 20.0f));
			actor->SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object01");
			actor->SetPosition(DirectX::XMFLOAT3(320, 00, 20));
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(20.0f, 20.0f, 20.0f));
			actor->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->SetFomXZ(FOM::Bounse);
			actor->SetFomY(FOM::Bounse);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object02");
			actor->SetPosition(DirectX::XMFLOAT3(360, 0.0f, 20));
			actor->SetRotation(DirectX::XMFLOAT4(3.14f * 0.0f, 3.14f * 0.0f, 3.14f * 0.25f, 1));
			actor->SetScale(DirectX::XMFLOAT3(20.0f, 20.0f, 20.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object03");
			actor->SetPosition(DirectX::XMFLOAT3(220, 20, 00));
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(20.0f, 100.0f, 20.0f));
			actor->SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->SetFomXZ(FOM::Friction);
			actor->SetFomY(FOM::Friction);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object04");
			actor->SetPosition(DirectX::XMFLOAT3(220, 20, -60));
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(20.0f, 100.0f, 20.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->SetFomXZ(FOM::Friction_One);
			actor->SetFomY(FOM::Friction_One);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object05");
			actor->SetPosition(DirectX::XMFLOAT3(400, 0.0f, 20));
			actor->SetRotation(DirectX::XMFLOAT4(3.14f * 0.25f, 3.14f * 0.0f, 3.14f * 0.0f, 1));
			actor->SetScale(DirectX::XMFLOAT3(20.0f, 20.0f, 20.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object06");
			actor->SetPosition(DirectX::XMFLOAT3(380, 0.0f, -100));
			actor->SetRotation(DirectX::XMFLOAT4(3.14f * 0.25f, 3.14f * 0.0f, 3.14f * 0.25f, 1));
			actor->SetScale(DirectX::XMFLOAT3(30.0f, 30.0f, 30.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.0f, 0.5f, 1.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
		// Object
		{
			const char* filename = "Data/Model/Cube/Cube.mdl";
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();
			actor->LoadModel(filename);
			actor->SetName("Object07");
			actor->SetPosition(DirectX::XMFLOAT3(380, 0.0f, 200));
			actor->SetRotation(DirectX::XMFLOAT4(3.14f * 0.0f, 3.14f * 0.0f, 3.14f * 0.25f, 1));
			actor->SetScale(DirectX::XMFLOAT3(100.0f, 100.0f, 100.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.5f, 0.5f, 1.0f, 1.0f));
			actor->SetRaycastFlg(true);
			actor->SetActorType(ActorType::Object);
			actor->AddComponent<VsCollision>();
			actor->AddComponent<Object>();
		}
	}
	{
		for (int i = 0; i < 10; i++)
		{
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();

			const char* filename = "Data/Model/Cube/Cube.mdl";
			actor->LoadModel(filename);
			std::string name = std::string("TrackingObject:") + std::to_string(i);
			actor->SetName(name);
			actor->SetPosition({ Mathf::RandomRange(-100.0f,100.0f), 3.0f, Mathf::RandomRange(-100.0f, 100.0f) });
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.0f, 0.5f, 1.0f, 0.5f));
			actor->SetRadius(3.0f);
			actor->SetActorType(ActorType::Object);

			actor->AddComponent<VsCollision>();

			actor->AddComponent<Movement>();

			actor->AddComponent<CollisionObject>();
			actor->GetComponent<CollisionObject>()->SetHitCollisionType(HitCollisionType::Heel);
			actor->GetComponent<CollisionObject>()->SetHitNum(1.0f);
			actor->GetComponent<CollisionObject>()->SetTargetActorType(ActorType::Player);

			actor->AddComponent<TrackingObject>();
			actor->GetComponent<TrackingObject>()->SetSphereRadius(FLT_MAX);
		}
	}
	{
		for (int i = 0; i < 10; i++)
		{
			std::shared_ptr<Actor> actor = ActorManager::Instance().Create();

			const char* filename = "Data/Model/Cube/Cube.mdl";
			actor->LoadModel(filename);
			std::string name = std::string("SphereTrackingObject:") + std::to_string(i);
			actor->SetName(name);
			actor->SetPosition({ Mathf::RandomRange(-200.0f,200.0f), 3.0f, Mathf::RandomRange(200.0f, 300.0f) });
			actor->SetRotation(DirectX::XMFLOAT4(0, 0, 0, 1));
			actor->SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));
			actor->SetColor(DirectX::XMFLOAT4(0.25f, 0.0f, 1.0f, 0.5f));
			actor->SetRadius(3.0f);
			actor->SetActorType(ActorType::Object);
			actor->AddComponent<VsCollision>();

			actor->AddComponent<Movement>();

			actor->AddComponent<CollisionObject>();
            actor->GetComponent<CollisionObject>()->SetHitCollisionType(HitCollisionType::Heel);
            actor->GetComponent<CollisionObject>()->SetHitNum(1.0f);
            actor->GetComponent<CollisionObject>()->SetTargetActorType(ActorType::Player);

			actor->AddComponent<TrackingObject>();

			actor->AddComponent<SphereTrackingObject>();
			actor->GetComponent<SphereTrackingObject>()->SetRadiusSearch(100.0f);
		}
	}
#endif // OBJECT
}

// 終了化
void SceneGame::Finalize()
{
	//ステージ終了化
	//StageManager::Instance().Clear();
	ActorManager::Instance().Clear();
	for (int i = 0; i < sizeof(checker_actor); i++)checker_actor[i] = false;
	checker_control = false;
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	//MouseManager::GetInstance().MouseTransform(dc, Camera::Instance().GetView(), Camera::Instance().GetProjection());

#ifdef  ALLPLAYER
    //Actor更新
	ActorManager::Instance().Update(elapsedTime);
	//if(Player::Instance().GetHealth() <= 0)SceneManager::Instance().ChangeScene(new SceneLoading(new SceneResult(false)));
	//Player* player = ActorManager::Instance().GetActor<Player>("Player");
	Actor* player=ActorManager::Instance().GetActor("Player");
	//if (player->GetComponent<Player>()->GetHealth() <= 0)SceneManager::Instance().ChangeScene(new SceneLoading(new SceneResult(true)));
	
	CameraController camera_controller;
	Camera* camera = ActorManager::Instance().GetActor("MainCamera")->GetComponent<Camera>().get();
	camera_controller.UpdateKey(elapsedTime,player->GetPosition(), *camera);


	////カメラ更新処理
	//camera_controller.Update(player->GetPosition());
#endif //  ALLPLAYER

#ifdef SPOWNENEMY
    spown->Update(elapsedTime);
	if(spown.get()->GetStageClear())SceneManager::Instance().ChangeScene(new SceneLoading(new SceneResult(true)));
#endif // SPOWNENEMY


	//エフェクト更新処理
	EffectManager::Instance().Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
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


	// 3Dモデル描画
	{
		Shader* shader = graphics.GetShader();
		shader->Begin(dc, rc);
		//ステージ描画
		//StageManager::Instance().Render(dc, shader);


		//プレイヤー描画
#ifdef  ALLPLAYER
	// アクター描画
		ActorManager::Instance().UpdateTransform();
		ActorManager::Instance().Render(dc, shader);
#endif //  ALLPLAYER
		shader->End(dc);
	}

	//3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}

	// 3Dデバッグ描画
	{
#ifdef  DEBUGIMGUI
		//プレイヤーデバッグプリミティブ描画
		ActorManager::Instance().DrawDebug();
		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, rc.view, rc.projection);
		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, rc.view, rc.projection);
#endif //DEBUGIMGUI
	}

	// 2Dスプライト描画
	{
#ifdef HPGAUGE
		RenderEnemyGauge(dc, rc.view, rc.projection);
		RenderPlayerGauge(dc, rc.view, rc.projection);
#endif // HPGAUGE
#ifdef ENEMYADD
		CrickEnemyAdd(dc, rc.view, rc.projection);
#endif // ENEMYADD
		Ui::Instance().game(dc);
#ifdef SPOWNENEMY
		spown->render(dc);
#endif // SPOWNENEMY
	}

#ifdef DEBUGIMGUI
	//static bool checker_actor[6] = {};
	//static bool checker_control = {};
	static bool actor_open = {};
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Actor"))
		{
			ImGui::MenuItem("All",    "", &checker_actor[0]);
			ImGui::MenuItem("Player", "", &checker_actor[1]);
			ImGui::MenuItem("Enemy",  "", &checker_actor[2]);
			ImGui::MenuItem("Stage",  "", &checker_actor[3]);
			ImGui::MenuItem("Camera", "", &checker_actor[4]);
			ImGui::MenuItem("Object", "", &checker_actor[5]);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Control"))
		{
			ImGui::MenuItem("Enemy", "", &checker_control);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

    // デバッグGUI描画
	if (checker_actor[0])
	{
		ActorManager::Instance().DrawDetail();
		ActorManager::Instance().DrawLister(ActorType::All);
	}
	if (checker_actor[1]&&!checker_actor[0])
	{
		ActorManager::Instance().DrawDetail();
		ActorManager::Instance().DrawLister(ActorType::Player);
	}
	if (checker_actor[2] && !checker_actor[0])
	{
		ActorManager::Instance().DrawDetail();
		ActorManager::Instance().DrawLister(ActorType::Enemy);
	}	
	if (checker_actor[3] && !checker_actor[0])
	{
		ActorManager::Instance().DrawDetail();
		ActorManager::Instance().DrawLister(ActorType::Stage);
	}
	if (checker_actor[4] && !checker_actor[0])
	{
		ActorManager::Instance().DrawDetail();
		ActorManager::Instance().DrawLister(ActorType::Camera);
	}
	if (checker_actor[5] && !checker_actor[0])
	{
		ActorManager::Instance().DrawDetail();
		ActorManager::Instance().DrawLister(ActorType::Object);
	}
	for (int i = 0; i < sizeof(checker_actor); i++)
	{
		if (checker_actor[i])
		{
			actor_open = true;
			break;
		}
		else actor_open = false;
	}
	if (actor_open)
	{
		if (ImGui::Begin("Actor Lister", nullptr, ImGuiWindowFlags_None))
		{
			if (ImGui::Button("Close"))
			{
				for (int i = 0; i < sizeof(checker_actor); i++)
				{
					checker_actor[i] = false;
				}
				actor_open = false;
			}
			//if (ImGui::Button("AllOpen"))
			//{
			//	for (int i = 0; i < sizeof(checker_actor); i++)
			//	{
			//		checker_actor[i] = true;

			//	}
			//}
		}
		ImGui::End();
	}
	if(checker_control)spown->DrawDebugGUI();
#endif // DebugImGui
}

//エネミーHPゲージ描画
void SceneGame::RenderEnemyGauge(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{
	////すべての敵の頭上にHPゲージを表示
	//EnemyManager& enemyManager = EnemyManager::Instance();
	//int enemyCount = enemyManager.GetEnemyCount();
	//DirectX::XMFLOAT4 color = { 1,0,1,1 }; //ゲージの色
	//for (int i = 0; i < enemyCount; ++i)
	//{
	//	Enemy* enemy = enemyManager.GetEnemy(i);
	//	DirectX::XMFLOAT3 enemy_position = enemy->GetPosition();
	//	enemy_position.y += 3.0f;
	//	CharacterGauge(dc, view, projection, enemy_position, enemy->GetHealth(), color);
	//}
}

//プレイヤーHPゲージ描画
void SceneGame::RenderPlayerGauge(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{

	//DirectX::XMFLOAT3 player_position = Player::Instance().GetPosition();
	//DirectX::XMVECTOR PlayerPosition = DirectX::XMLoadFloat3(&player_position);
	//DirectX::XMFLOAT4 color = { 1,0.5,0,1 };//ゲージの色
	//CharacterGauge(dc, view, projection, player_position, Player::Instance().GetHealth(), color);
}

void SceneGame::CharacterGauge(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection, DirectX::XMFLOAT3 position,int health, DirectX::XMFLOAT4 gaugecolor)
{
	//ビューポート
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//変換行列
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();

	//DirectX::XMFLOAT3 player_position = Player::Instance().GetPosition();
	//player_position.y = 1.0f;
	//DirectX::XMVECTOR PlayerPosition = DirectX::XMLoadFloat3(&player_position);
	DirectX::XMVECTOR Position = DirectX::XMLoadFloat3(&position);

	//ワールド座標からスクリーン座標へ変換する関数
	Position = DirectX::XMVector3Project(
		Position,
		viewport.TopLeftX,
		viewport.TopLeftY,
		viewport.Width,
		viewport.Height,
		viewport.MinDepth,
		viewport.MaxDepth,
		Projection,
		View,
		World
	);
	DirectX::XMStoreFloat3(&position, Position);

	//Player::Instance().SetScreenPos(position);

	for (int i = 0; i < health; ++i)
	{
		gauge->Render(
			dc,
			position.x - 25 + i * 10, position.y,
			9, 10,
			100, 100,
			25, 10,
			0,
			gaugecolor.x, gaugecolor.y, gaugecolor.z, gaugecolor.w);
		gauge->Render(
			dc,
			position.x - 25 + i * 10, position.y,
			1, 10,
			100, 100,
			25, 10,
			0,
			0, 0, 0, 1);
	}
}

void SceneGame::CrickEnemyAdd(ID3D11DeviceContext* dc, const DirectX::XMFLOAT4X4& view, const DirectX::XMFLOAT4X4& projection)
{	//ビューポート
	D3D11_VIEWPORT viewport;
	UINT numViewports = 1;
	dc->RSGetViewports(&numViewports, &viewport);

	//変換行列
	DirectX::XMMATRIX View = DirectX::XMLoadFloat4x4(&view);
	DirectX::XMMATRIX Projection = DirectX::XMLoadFloat4x4(&projection);
	DirectX::XMMATRIX World = DirectX::XMMatrixIdentity();


	//エネミー配置処理
	GamePad& gamePad = Input::Instance().GetGamePad();
	Mouse& mouse = Input::Instance().GetMouse();
	if (mouse.GetButtonDown() & Mouse::BTN_LEFT)
	{
		//マウスカーソル座標取得
		DirectX::XMFLOAT3 screenPosition;
		screenPosition.x = static_cast<float>(mouse.GetPositionX());
		screenPosition.y = 1;
		screenPosition.z = static_cast<float>(mouse.GetPositionY());

		DirectX::XMVECTOR ScreenCursor = DirectX::XMLoadFloat3(&screenPosition);

		DirectX::XMVECTOR WorldPosition = DirectX::XMVector3Unproject
		(
			ScreenCursor,
			viewport.TopLeftX,
			viewport.TopLeftY,
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,
			viewport.MaxDepth,
			Projection,
			View,
			World
		);
		DirectX::XMFLOAT3 world_position_start;
		DirectX::XMStoreFloat3(&world_position_start, WorldPosition);

		screenPosition.z = 1;
		ScreenCursor = DirectX::XMLoadFloat3(&screenPosition);
		WorldPosition = DirectX::XMVector3Unproject
		(
			ScreenCursor,
			viewport.TopLeftX,
			viewport.TopLeftY,
			viewport.Width,
			viewport.Height,
			viewport.MinDepth,
			viewport.MaxDepth,
			Projection,
			View,
			World
		);
		DirectX::XMFLOAT3 world_position_end;
		DirectX::XMStoreFloat3(&world_position_end, WorldPosition);

		HitResult hit;
		//StageMain stage_main;
		//if (stage_main.RayCast(world_position_start, world_position_end, hit))
		//{
		//	EnemyManager& enemyManager = EnemyManager::Instance();
		//	Enemy01* slime = new Enemy01(GREEN);
		//	slime->SetPosition(DirectX::XMFLOAT3(world_position_start.x, world_position_start.y, world_position_start.z));
		//	enemyManager.Register(slime);
		//}
	}
}
