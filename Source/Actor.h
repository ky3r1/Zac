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

enum class FOM//feeling of material(�I�u�W�F�N�g�̎���)
{
	Normal,//����������~�܂�(Y��:�d�͏����Z)
	Bounse,//���������甽������
	Friction,//���C��������
	Friction_One,//����������~�܂�(Y��:�d�͏���X) ->Y���̏����Ɏg����Friction�Ɠ���
	None,
};

//�O���錾
class Component;

struct Parameter
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

	//�f�o�b�O�v���~�e�B�u
	virtual void DrawDebug();

	//DelayTime�X�V
	void UpdateDelayTime(DelayTime& delaytime, float maxtime);
public:
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
	void SetRotation(const DirectX::XMFLOAT4& rotation){ this->parameter.rotation = rotation;}
	const DirectX::XMFLOAT4& GetRotation() const { return parameter.rotation; }

	// �X�P�[���̃Z�b�^�[�E�Q�b�^�[
	void SetScale(const DirectX::XMFLOAT3& scale){ this->parameter.scale = scale; }
	const DirectX::XMFLOAT3& GetScale() const { return parameter.scale; }

	//�F�̃Z�b�^�[�E�Q�b�^�[
	void SetColor(const DirectX::XMFLOAT4& color){ this->parameter.color = color; }
	const DirectX::XMFLOAT4& GetColor() const { return parameter.color; }

	// �s��̃Q�b�^�[
	const DirectX::XMFLOAT4X4& GetTransform() const { return parameter.transform; }

	//�d��
    float GetWeight() const { return parameter.collision_cylinder.sphere.weight; }
	void SetWeight(float weight) {parameter.collision_cylinder.sphere.weight = weight;}

	//����
    float GetHeight() const { return parameter.collision_cylinder.height; }
    void SetHeight(float height) {	parameter.collision_cylinder.height = height;}

	//���a
    float GetRadius() const { return parameter.collision_cylinder.sphere.radius; }
    void SetRadius(float radius) { parameter.collision_cylinder.sphere.radius = radius;}

	//Sphere
    Sphere GetSphere() const { return parameter.collision_cylinder.sphere; }
    void SetSphere(const Sphere& sphere) { parameter.collision_cylinder.sphere = sphere; }

	//Cylinder
    Cylinder GetCylinder() const { return parameter.collision_cylinder; }
    void SetCylinder(const Cylinder& cylinder) {parameter.collision_cylinder = cylinder;}


	// ���f���̃Z�b�^�[�E�Q�b�^�[
	void LoadModel(const char* filename);
	Model* GetModel() const { return model.get(); }

	// �^�C�v�̃Z�b�^�[�E�Q�b�^�[	
	void SetActorType(ActorType type) { this->type = type; }
	ActorType GetActorType() const { return type; }

	//FOM_Y
    void SetFomY(FOM f) { fom_Y = f; }
    FOM GetFomY() const { return fom_Y; }

	//FOM_XZ
	void SetFomXZ(FOM f) { fom_XZ = f; }
	FOM GetFomXZ() const { return fom_XZ; }

	// ���C�L���X�g�t���O�̃Z�b�^�[�E�Q�b�^�[
    void SetRaycastFlg(bool flg) { raycast_flg = flg; }
    bool GetRaycastFlg() const { return raycast_flg; }

	//old_transform
    void SetOldTransform(const DirectX::XMFLOAT4X4& transform) { old_transform = transform; }
    const DirectX::XMFLOAT4X4& GetOldTransform() const { return old_transform; }

	//Animation�Z�b�^�[�E�Q�b�^�[
    void SetAnimation(Animation animation) { this->animation = animation; }
	void SetAnimation(int state, bool loop,bool stop) { this->animation.state = state; this->animation.loop = loop; this->animation.stop = stop; }
	void SetAnimation(int state, bool loop, float blend,bool stop) { this->animation.state = state; this->animation.loop = loop; this->animation.blend = blend;	 this->animation.stop = stop;}
	Animation GetAnimation() const { return animation; }

    //////////////////////////////////////////////////////////////////////////
    //							�R���|�[�l���g							//
    //////////////////////////////////////////////////////////////////////////

	// �R���|�[�l���g�ǉ�
	template<class T, class... Args>
	std::shared_ptr<T> AddComponent(Args... args)
	{
		parameter_backup = parameter;
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
	Parameter			parameter_backup;
	bool				raycast_flg = false;
	DirectX::XMFLOAT4X4 old_transform = { 
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };

	// �t�B���^�[�p�̃^�C�v
	ActorType type = ActorType::None;
	//����
    FOM fom_Y = FOM::Normal;
	FOM fom_XZ = FOM::Normal;
	Animation  animation;

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

	//�S�폜
    void Clear();

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
	bool GetNearActor(Actor* origin,Actor& result, ActorType filter);
	Actor* GetNearActor(Actor* origin, ActorType filter);
	//std::unique_ptr<Actor> GetNearActor(Actor* origin, ActorType filter);

	//RayCast�p�A�N�^�[�擾
	bool GetNearActorRayCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, HitResult& hit_result,Actor** reactor);
	bool GetNearActorRayCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, HitResult& hit_result);
	//SphereCast�p�A�N�^�[�擾
	bool GetNearActorSphereCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,float radius, HitResult& hit_result, Actor** reactor);

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