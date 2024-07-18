#pragma once
#include "All.h"
#include "Collision.h"

enum class ActorType
{
	Player,
	Enemy,
	Stage,
	Object,
	Camera,
	None,
	All,
};
//�O���錾
class Component;

static struct Parameter
{
	DirectX::XMFLOAT4	rotation = DirectX::XMFLOAT4(0, 0, 0, 1);
	DirectX::XMFLOAT3	scale = DirectX::XMFLOAT3(1, 1, 1);
	DirectX::XMFLOAT4	color = DirectX::XMFLOAT4(1, 1, 1, 1);
	DirectX::XMFLOAT4X4	transform = DirectX::XMFLOAT4X4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	Cylinder collision_cylinder;
};

class Actor : public std::enable_shared_from_this<Actor>
{
public:
	Actor() {}
	virtual ~Actor() {};

	// �J�n����
	virtual void Start();

	// �X�V����
	virtual void Update(float elapsedTime);

	// �s��̍X�V
	virtual void UpdateTransform();

	// GUI�\��
	virtual void OnGUI();

	virtual void DrawDebug();

	//////////////////////////////////////////////////////////////////////////
	//							�Z�b�^�[�E�Q�b�^�[							//
	//////////////////////////////////////////////////////////////////////////

		// ���O�̃Z�b�^�[�E�Q�b�^�[
	void SetName(const char* name) { this->name = name; }
	const std::string GetName() const { return name; }

	// �ʒu�̃Z�b�^�[�E�Q�b�^�[
	void SetPosition(const DirectX::XMFLOAT3& position) { this->parameter.collision_cylinder.sphere.position = position; }
	const DirectX::XMFLOAT3& GetPosition() const { return parameter.collision_cylinder.sphere.position; }

	// ��]�̃Z�b�^�[�E�Q�b�^�[
	void SetRotation(const DirectX::XMFLOAT4& rotation) { this->parameter.rotation = rotation; }
	const DirectX::XMFLOAT4& GetRotation() const { return parameter.rotation; }

	// �X�P�[���̃Z�b�^�[�E�Q�b�^�[
	void SetScale(const DirectX::XMFLOAT3& scale) { this->parameter.scale = scale; }
	const DirectX::XMFLOAT3& GetScale() const { return parameter.scale; }

	//�F�̃Z�b�^�[�E�Q�b�^�[
	void SetColor(const DirectX::XMFLOAT4& color) { this->parameter.color = color; }
	const DirectX::XMFLOAT4& GetColor() const { return parameter.color; }

	// �s��̃Q�b�^�[
	const DirectX::XMFLOAT4X4& GetTransform() const { return parameter.transform; }

	// ���f���̃Z�b�^�[�E�Q�b�^�[
	void LoadModel(const char* filename);
	Model* GetModel() const { return model.get(); }

	// �^�C�v�̃Z�b�^�[�E�Q�b�^�[	
	void SetActorType(ActorType type) { this->type = type; }
	ActorType GetActorType() const { return type; }


	// �R���|�[�l���g�ǉ�
	template<class T, class... Args>
	std::shared_ptr<T> AddComponent(Args... args)
	{
		std::shared_ptr<T> component = std::make_shared<T>(args...);
		component->SetActor(shared_from_this());
		components.emplace_back(component);
		return component;
	}

	// �R���|�[�l���g�擾
	template<class T>
	std::shared_ptr<T> GetComponent()
	{
		for (std::shared_ptr<Component>& component : components)
		{
			std::shared_ptr<T> p = std::dynamic_pointer_cast<T>(component);
			if (p == nullptr) continue;
			return p;
		}
		return nullptr;
	}
private:
	std::string			name;
	Parameter			parameter;

	// �t�B���^�[�p�̃^�C�v
	ActorType type = ActorType::None;

	std::unique_ptr<Model>	model;
	std::vector<std::shared_ptr<Component>>	components;
};

class ActorManager
{
private:
	ActorManager() {}
	~ActorManager() {};

public:
	// �C���X�^���X�擾
	static ActorManager& Instance()
	{
		static ActorManager instance;
		return instance;
	}

	// �쐬
	std::shared_ptr<Actor> Create();

	// �폜
	void Remove(std::shared_ptr<Actor> actor);

	// �X�V
	void Update(float elapsedTime);

	// �s��X�V
	void UpdateTransform();

	// �`��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	// ����
	Actor* GetActor(std::string name);

	// �߂��̃A�N�^�[���擾
	Actor* GetNearActor(Actor origin, ActorType filter);

	// �A�N�^�[�����擾
	int GetActorCount(ActorType filter);

public:
	void DrawLister(ActorType filter);
	void DrawDetail();

	void DrawDebug();

private:
	std::vector<std::shared_ptr<Actor>>		startActors;
	std::vector<std::shared_ptr<Actor>>		updateActors;
	std::set<std::shared_ptr<Actor>>		selectionActors;
	std::set<std::shared_ptr<Actor>>		removeActors;

	bool					hiddenLister = false;
	bool					hiddenDetail = false;
};