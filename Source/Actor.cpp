#include "Actor.h"
#include "Component.h"
#include "Mathf.h"

// 開始処理
void Actor::Start()
{	
	for (std::shared_ptr<Component>& component : components)
	{
		component->Start();
	}
}

// 更新
void Actor::Update(float elapsedTime)
{
	// アニメーションの更新
	if (model != nullptr)
	{
		model->UpdateAnimation(elapsedTime);
	}
	for (std::shared_ptr<Component>& component : components)
	{
		component->Update(elapsedTime);
	}
}

// 行列の更新
void Actor::UpdateTransform()
{
	// ワールド行列の更新
	DirectX::XMVECTOR Q = DirectX::XMLoadFloat4(&parameter.rotation);
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(parameter.scale.x, parameter.scale.y, parameter.scale.z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(Q);
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(parameter.collision_cylinder.sphere.position.x, parameter.collision_cylinder.sphere.position.y, parameter.collision_cylinder.sphere.position.z);

	DirectX::XMMATRIX W = S * R * T;
	DirectX::XMStoreFloat4x4(&parameter.transform, W);

	// モデルの行列更新
	if (model != nullptr)
	{
		model->UpdateTransform(parameter.transform);
	}
}

void Actor::OnGUI()
{
	// 名前
	{
		char buffer[1024];
		::strncpy_s(buffer, sizeof(buffer), GetName().c_str(), sizeof(buffer));
		if (ImGui::InputText("Name", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			SetName(buffer);
		}
	}

	{
		// デバッグ文字列表示の変更
		std::string type_str = "";
		// 現在のステート番号に合わせてデバッグ文字列をstrに格納
		switch (type) 
		{
		case ActorType::Player:
			type_str = "Player";
			break;
		case ActorType::Enemy:
			type_str = "Enemy";
			break;
		case ActorType::Stage:
			type_str = "Stage";
			break;
		case ActorType::Object:
			type_str = "Object";
			break;
		case ActorType::Camera:
			type_str = "Camera";
			break;
		case ActorType::None:
			type_str = "None";
			break;
		default:
			type_str = "Unknown";
			break;
		}
		ImGui::Text(u8"ActorType:%s", type_str.c_str());
	}

	// トランスフォーム
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::InputFloat3("Position", &parameter.collision_cylinder.sphere.position.x);
		ImGui::InputFloat3("Rotation", &parameter.rotation.x);
		ImGui::InputFloat3("Scale", &parameter.scale.x);
		
        if (ImGui::Button("Reset"))
        {
			parameter.collision_cylinder.sphere.position = { 0.0f, 0.0f, 0.0f };
			parameter.rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
			parameter.scale = { 1.0f, 1.0f, 1.0f };
        }
	}

	// コンポーネント
	for (std::shared_ptr<Component>& component : components)
	{
		ImGui::Spacing();
		ImGui::Separator();

		if (ImGui::CollapsingHeader(component->GetName(), ImGuiTreeNodeFlags_DefaultOpen))
		{
			//ImGui::PushID(StringToHash(component->GetName()));
			component->DrawImGui();
			//ImGui::PopID();
		}
	}
}

void Actor::DrawDebug()
{
	for (std::shared_ptr<Component>& component : components)
	{
		component->DrawDebug();
	}
}

// モデルの読み込み
void Actor::LoadModel(const char* filename)
{
	model = std::make_unique<Model>(filename);
}

// 作成
std::shared_ptr<Actor> ActorManager::Create()
{
	std::shared_ptr<Actor> actor = std::make_shared<Actor>();
	{
		static int id = 0;
		char name[256];
		::sprintf_s(name, sizeof(name), "Actor%d", id++);
		actor->SetName(name);
	}
	startActors.emplace_back(actor);
	return actor;
}

// 削除
void ActorManager::Remove(std::shared_ptr<Actor> actor)
{
	removeActors.insert(actor);
}

// 更新
void ActorManager::Update(float elapsedTime)
{
	for (std::shared_ptr<Actor>& actor : startActors)
	{
		actor->Start();
		updateActors.emplace_back(actor);
	}
	startActors.clear();

	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor->Update(elapsedTime);
	}

	for (const std::shared_ptr<Actor>& actor : removeActors)
	{
		std::vector<std::shared_ptr<Actor>>::iterator itStart = std::find(startActors.begin(), startActors.end(), actor);
		if (itStart != startActors.end())
		{
			startActors.erase(itStart);
		}

		std::vector<std::shared_ptr<Actor>>::iterator itUpdate = std::find(updateActors.begin(), updateActors.end(), actor);
		if (itUpdate != updateActors.end())
		{
			updateActors.erase(itUpdate);
		}

		std::set<std::shared_ptr<Actor>>::iterator itSelection = selectionActors.find(actor);
		if (itSelection != selectionActors.end())
		{
			selectionActors.erase(itSelection);
		}
	}
	removeActors.clear();
}

// 行列更新
void ActorManager::UpdateTransform()
{
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor->UpdateTransform();
	}
}

// 描画
void ActorManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	//Graphics& graphics = Graphics::Instance();
	//Shader* shader = graphics.GetShader();
	//ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	//// ライトの方向
	//DirectX::XMFLOAT3 lightDirection = DirectX::XMFLOAT3(0.2f, -0.8f, 0.0f);

	// 描画
	//shader->Begin(dc, /*view, projection,*/ lightDirection);

	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		// モデルがあれば描画
		Model* model = actor->GetModel();
		if (model != nullptr)
		{
			shader->Draw(dc, actor->GetModel(), actor->GetColor());
		}
	}

	//shader->End(dc);

	//// リスター描画
	//DrawLister();

	//// 詳細描画
	//DrawDetail();

}

template<class T>
T* ActorManager::GetActor(std::string name)
{
	for (std::shared_ptr<T> actor : updateActors)
	{
		if (actor->GetName() == name)
		{
			return actor.get();
		}
	}
	return nullptr;
}

Actor* ActorManager::GetActor(std::string name)
{
	for (std::shared_ptr<Actor> actor : updateActors)
	{
		if (actor->GetName() == name)
		{
			return actor.get();
		}
	}
	return nullptr;
}

Actor* ActorManager::GetNearActor(Actor origin, ActorType filter)
{
	float min = FLT_MAX;
	float distance=0.0f;
    Actor* minActor = nullptr;
	for (std::shared_ptr<Actor> actor : updateActors)
	{
		if (actor->GetActorType() == filter||filter==ActorType::All)
        {
            distance = Mathf::Distance(origin.GetPosition(), actor->GetPosition());
            if (distance < min)
            {
                min = distance;
                minActor = actor.get();
            }
        }
	}
	return minActor;
}

int ActorManager::GetActorCount(ActorType filter)
{
	int count = 0;
	for (std::shared_ptr<Actor> actor : updateActors)
	{
		if (actor->GetActorType() == filter || filter == ActorType::All)
		{
            count++;
		}
	}
	return count;
}



// リスター描画
void ActorManager::DrawLister(ActorType filter)
{
	ImGui::SetNextWindowPos(ImVec2(30, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

	hiddenLister = !ImGui::Begin("Actor Lister", nullptr, ImGuiWindowFlags_None);
	if (!hiddenLister)
	{
		for (std::shared_ptr<Actor>& actor : updateActors)
		{
			if (filter == ActorType::All||filter == actor.get()->GetActorType())
			{
				ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf;

				if (selectionActors.find(actor) != selectionActors.end())
				{
					nodeFlags |= ImGuiTreeNodeFlags_Selected;
				}

				ImGui::TreeNodeEx(actor.get(), nodeFlags, actor->GetName().c_str());

				if (ImGui::IsItemClicked())
				{
					// 単一選択だけ対応しておく
					ImGuiIO& io = ImGui::GetIO();
					selectionActors.clear();
					selectionActors.insert(actor);
				}

				ImGui::TreePop();
			}
		}
	}
	ImGui::End();
}

// 詳細描画
void ActorManager::DrawDetail()
{
	ImGui::SetNextWindowPos(ImVec2(950, 50), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(600, 600), ImGuiCond_FirstUseEver);

	hiddenDetail = !ImGui::Begin("Actor Detail", nullptr, ImGuiWindowFlags_None);
	if (!hiddenDetail)
	{
		std::shared_ptr<Actor> lastSelected = selectionActors.empty() ? nullptr : *selectionActors.rbegin();
		if (lastSelected != nullptr)
		{
			lastSelected->OnGUI();
		}
	}
	ImGui::End();
}

void ActorManager::DrawDebug()
{
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor.get()->DrawDebug();
	}
}
