#include "Actor.h"
#include "Component.h"
#include "Mathf.h"
#include "Collision.h"

// �J�n����
void Actor::Start()
{	
	for (std::shared_ptr<Component>& component : components)
	{
		component->Start();
	}
}

// �X�V
void Actor::Update(float elapsedTime)
{
	old_transform = parameter.transform;
	// �A�j���[�V�����̍X�V
	if (model != nullptr)
	{
		model->UpdateAnimation(elapsedTime);
	}
	for (std::shared_ptr<Component>& component : components)
	{
		component->Update(elapsedTime);
	}
}

// �s��̍X�V
void Actor::UpdateTransform()
{
	//�X�P�[���s����쐬
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(parameter.scale.x, parameter.scale.y, parameter.scale.z);
	//��]�s����쐬
	DirectX::XMMATRIX X = DirectX::XMMatrixRotationX(parameter.rotation.x);
	DirectX::XMMATRIX Y = DirectX::XMMatrixRotationY(parameter.rotation.y);
	DirectX::XMMATRIX Z = DirectX::XMMatrixRotationZ(parameter.rotation.z);
	DirectX::XMMATRIX R = Y * X * Z;
	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(parameter.collision_cylinder.sphere.position.x, parameter.collision_cylinder.sphere.position.y, parameter.collision_cylinder.sphere.position.z);
	//3�̍s���g�ݍ��킹�A���[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;
	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&parameter.transform, W);

	// ���f���̍s��X�V
	if (model != nullptr)
	{
		model->UpdateTransform(parameter.transform);
	}
}

void Actor::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	for (std::shared_ptr<Component>& component : components)
	{
		component->Render(dc,shader);
	}
}

void Actor::OnGUI()
{
	// ���O
	{
		char buffer[1024];
		::strncpy_s(buffer, sizeof(buffer), GetName().c_str(), sizeof(buffer));
		if (ImGui::InputText("Name", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue))
		{
			SetName(buffer);
		}
	}

	{
		// �f�o�b�O������\���̕ύX
		std::string type_str = "";
		// ���݂̃X�e�[�g�ԍ��ɍ��킹�ăf�o�b�O�������str�Ɋi�[
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
		case ActorType::Bullet:
			type_str = "Bullet";
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
	if (raycast_flg)
	{
		{
			// �f�o�b�O������\���̕ύX
			std::string type_str = "";
			// ���݂̃X�e�[�g�ԍ��ɍ��킹�ăf�o�b�O�������str�Ɋi�[
			switch (fom_Y)
			{
			case FOM::Normal:
				type_str = "Normal";
				break;
			case FOM::Bounse:
				type_str = "Bounse";
				break;
			case FOM::Friction:
				type_str = "Friction";
				break;
			case FOM::Friction_One:
				type_str = "Friction_One";
				break;
			case FOM::None:
				type_str = "None";
				break;
			default:
				type_str = "Unknown";
				break;
			}
			ImGui::Text(u8"FOM Axis-Y:%s", type_str.c_str());
		}
		{
			// �f�o�b�O������\���̕ύX
			std::string type_str = "";
			// ���݂̃X�e�[�g�ԍ��ɍ��킹�ăf�o�b�O�������str�Ɋi�[
			switch (fom_XZ)
			{
			case FOM::Normal:
				type_str = "Normal";
				break;
			case FOM::Bounse:
				type_str = "Bounse";
				break;
			case FOM::Friction:
				type_str = "Friction";
				break;
			case FOM::Friction_One:
				type_str = "Friction_One";
				break;
			case FOM::None:
				type_str = "None";
				break;
			default:
				type_str = "Unknown";
				break;
			}
			ImGui::Text(u8"FOM Axis-XZ:%s", type_str.c_str());
		}
	}

	// �g�����X�t�H�[��
	if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::InputFloat3("Position_Input", &parameter.collision_cylinder.sphere.position.x);
		ImGui::SliderFloat3("Position_Slider", &parameter.collision_cylinder.sphere.position.x,-200.0f,200.0f);
		ImGui::SliderFloat3("Rotation", &parameter.rotation.x, -3.14f, 3.14f);
		ImGui::SliderFloat3("Scale", &parameter.scale.x, 0.001f, 10.0f);
		ImGui::SliderFloat("Radius", &parameter.collision_cylinder.sphere.radius, 0.1f, 10.0f);
		ImGui::SliderFloat("Height", &parameter.collision_cylinder.height, 0.1f, 10.0f);
		ImGui::SliderFloat("Weight", &parameter.collision_cylinder.sphere.weight, 0.1f, 10.0f);
		ImGui::SliderFloat("health", &current_health, 0.0f, max_health);
        if (ImGui::Button("Reset"))
        {
			parameter = parameter_backup;
        }
	}

	// �R���|�[�l���g
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

void Actor::UpdateDelayTime(DelayTime& delaytime, float maxtime)
{
	//checker��false�ꍇ�̓^�C�������炷
	//checker��true�ꍇ��checker��true�ɂ��ă^�C�������Z�b�g
	if (!delaytime.checker)
	{
		delaytime.time--;
	}
	if (delaytime.time < 0)
	{
		delaytime.checker = true;
		delaytime.time = maxtime;
	}
}

void Actor::TakeDamage(float damage)
{
	current_health -= damage;
}

void Actor::TakeHeel(float heel)
{
	current_health += heel;
}

// ���f���̓ǂݍ���
void Actor::LoadModel(const char* filename)
{
	model = std::make_unique<Model>(filename);
}

// �쐬
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

void ActorManager::Clear()
{
	startActors.clear();
	updateActors.clear();
	removeActors.clear();
}

// �폜
void ActorManager::Remove(std::shared_ptr<Actor> actor)
{
	removeActors.insert(actor);
}

// �X�V
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

// �s��X�V
void ActorManager::UpdateTransform()
{
	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		actor->UpdateTransform();
	}
}

// �`��
void ActorManager::Render(ID3D11DeviceContext* dc, Shader* shader)
{
	//Graphics& graphics = Graphics::Instance();
	//Shader* shader = graphics.GetShader();
	//ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	//// ���C�g�̕���
	//DirectX::XMFLOAT3 lightDirection = DirectX::XMFLOAT3(0.2f, -0.8f, 0.0f);

	// �`��
	//shader->Begin(dc, /*view, projection,*/ lightDirection);

	for (std::shared_ptr<Actor>& actor : updateActors)
	{
		// ���f��������Ε`��
		Model* model = actor->GetModel();
		if (model != nullptr)
		{
			shader->Draw(dc, actor->GetModel(), actor->GetColor());
		}
		actor->Render(dc, shader);
		
	}

	//shader->End(dc);

	//// ���X�^�[�`��
	//DrawLister();

	//// �ڍו`��
	//DrawDetail();

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

void ActorManager::DaedUpdate()
{
	for(std::shared_ptr<Actor>& actor : updateActors)
    {
		if (actor->GetDeadFlag())Remove(actor);
    }
}

bool ActorManager::GetNearActor(Actor* origin, Actor& result,ActorType filter)
{
	float min = FLT_MAX;
	float distance=0.0f;
	Actor* result_copy = nullptr;
	for (std::shared_ptr<Actor> actor : updateActors)
	{
		if (actor->GetActorType() == filter||filter==ActorType::All)
        {
            distance = Mathf::Distance(origin->GetPosition(), actor->GetPosition());
            if (distance < min)
            {
                min = distance;
				result_copy = actor.get();
            }
        }
	}
	if(result_copy !=nullptr)
    {
		//result = result_copy;
		return true;
    }
	return false;
}

Actor* ActorManager::GetNearActor(Actor* origin, ActorType filter)
{
	float min = FLT_MAX;
	float distance = 0.0f;
	Actor* result = nullptr;
	for (std::shared_ptr<Actor> actor : updateActors)
	{
		if (actor->GetActorType() == filter || filter == ActorType::All)
		{
			if (origin == actor.get())continue;
			distance = Mathf::Distance(origin->GetPosition(), actor->GetPosition());
			if (distance < min)
			{
				min = distance;
				result=actor.get();
			}
		}
	}
	return result;
}

bool ActorManager::GetNearActorRayCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, HitResult& hit_result, Actor** reactor)
{
    float min = FLT_MAX;
    float distance = 0.0f;
    Actor* result = nullptr;
	HitResult local_hit_result;
    for (std::shared_ptr<Actor> actor : updateActors)
    {
		//Actor��������RayCastFlg��ݒ肷��
        if (actor->GetRaycastFlg())
        {
			if (Collision::IntersectRayVsModel(start, end, actor->GetModel(), local_hit_result))
			{
				if (hit_result.distance < min)
				{
					min= local_hit_result.distance;
					hit_result = local_hit_result;
					result = actor.get();
					*reactor = actor.get();
				}
			}
        }
    }
	if (result != nullptr)return true;
    return false;
}

bool ActorManager::GetNearActorRayCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, HitResult& hit_result)
{
	Actor* result = nullptr;
	return GetNearActorRayCast(start, end, hit_result, &result);
}

bool ActorManager::GetNearActorSphereCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, float radius, HitResult& hit_result, Actor** reactor)
{
	float min = FLT_MAX;
	float distance = 0.0f;
	Actor* result = nullptr;
	HitResult local_hit_result;
	for (std::shared_ptr<Actor> actor : updateActors)
	{
		//Actor��������RayCastFlg��ݒ肷��
		if (actor->GetRaycastFlg())
		{
			if (Collision::IntersectSphereVsModel(start, end,radius, actor->GetModel(), local_hit_result))
			{
				if (hit_result.distance < min)
				{
					min = local_hit_result.distance;
					hit_result = local_hit_result;
					result = actor.get();
					*reactor = actor.get();
				}
			}
		}
	}
	if (result != nullptr)return true;
	return false;
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



// ���X�^�[�`��
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
					// �P��I�������Ή����Ă���
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

// �ڍו`��
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
