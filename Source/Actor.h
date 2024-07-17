#pragma once
#include "All.h"

//�O���錾
class Component;

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

	//////////////////////////////////////////////////////////////////////////
	//							�Z�b�^�[�E�Q�b�^�[							//
	//////////////////////////////////////////////////////////////////////////
	// ���O�̃Z�b�^�[�E�Q�b�^�[
	void SetName(const char* name) { this->name = name; }
	const char* GetName() const { return name.c_str(); }

	// �ʒu�̃Z�b�^�[�E�Q�b�^�[
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
	const DirectX::XMFLOAT3& GetPosition() const { return position; }

	// ��]�̃Z�b�^�[�E�Q�b�^�[
	void SetRotation(const DirectX::XMFLOAT4& rotation) { this->rotation = rotation; }
	const DirectX::XMFLOAT4& GetRotation() const { return rotation; }

	// �X�P�[���̃Z�b�^�[�E�Q�b�^�[
	void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//�F�̃Z�b�^�[�E�Q�b�^�[
    void SetColor(const DirectX::XMFLOAT4& color) { this->color = color; }
    const DirectX::XMFLOAT4& GetColor() const { return color; }

	// �s��̃Q�b�^�[
	const DirectX::XMFLOAT4X4& GetTransform() const { return transform; }

	// ���f���̃Z�b�^�[�E�Q�b�^�[
	void LoadModel(const char* filename);
	Model* GetModel() const { return model.get(); }

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
	DirectX::XMFLOAT3	position = DirectX::XMFLOAT3(0, 0, 0);
	DirectX::XMFLOAT4	rotation = DirectX::XMFLOAT4(0, 0, 0, 1);
	DirectX::XMFLOAT3	scale = DirectX::XMFLOAT3(1, 1, 1);
	DirectX::XMFLOAT4	color=DirectX::XMFLOAT4(1, 1, 1, 1);
	DirectX::XMFLOAT4X4	transform = DirectX::XMFLOAT4X4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

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

public:
	void DrawLister();
	void DrawDetail();

private:
	std::vector<std::shared_ptr<Actor>>		startActors;
	std::vector<std::shared_ptr<Actor>>		updateActors;
	std::set<std::shared_ptr<Actor>>		selectionActors;
	std::set<std::shared_ptr<Actor>>		removeActors;

	bool					hiddenLister = false;
	bool					hiddenDetail = false;
};