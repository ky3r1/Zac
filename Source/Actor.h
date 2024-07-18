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
//前方宣言
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

	// 開始処理
	virtual void Start();

	// 更新処理
	virtual void Update(float elapsedTime);

	// 行列の更新
	virtual void UpdateTransform();

	// GUI表示
	virtual void OnGUI();

	virtual void DrawDebug();

	//////////////////////////////////////////////////////////////////////////
	//							セッター・ゲッター							//
	//////////////////////////////////////////////////////////////////////////

		// 名前のセッター・ゲッター
	void SetName(const char* name) { this->name = name; }
	const std::string GetName() const { return name; }

	// 位置のセッター・ゲッター
	void SetPosition(const DirectX::XMFLOAT3& position) { this->parameter.collision_cylinder.sphere.position = position; }
	const DirectX::XMFLOAT3& GetPosition() const { return parameter.collision_cylinder.sphere.position; }

	// 回転のセッター・ゲッター
	void SetRotation(const DirectX::XMFLOAT4& rotation) { this->parameter.rotation = rotation; }
	const DirectX::XMFLOAT4& GetRotation() const { return parameter.rotation; }

	// スケールのセッター・ゲッター
	void SetScale(const DirectX::XMFLOAT3& scale) { this->parameter.scale = scale; }
	const DirectX::XMFLOAT3& GetScale() const { return parameter.scale; }

	//色のセッター・ゲッター
	void SetColor(const DirectX::XMFLOAT4& color) { this->parameter.color = color; }
	const DirectX::XMFLOAT4& GetColor() const { return parameter.color; }

	// 行列のゲッター
	const DirectX::XMFLOAT4X4& GetTransform() const { return parameter.transform; }

	// モデルのセッター・ゲッター
	void LoadModel(const char* filename);
	Model* GetModel() const { return model.get(); }

	// タイプのセッター・ゲッター	
	void SetActorType(ActorType type) { this->type = type; }
	ActorType GetActorType() const { return type; }


	// コンポーネント追加
	template<class T, class... Args>
	std::shared_ptr<T> AddComponent(Args... args)
	{
		std::shared_ptr<T> component = std::make_shared<T>(args...);
		component->SetActor(shared_from_this());
		components.emplace_back(component);
		return component;
	}

	// コンポーネント取得
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

	// フィルター用のタイプ
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
	// インスタンス取得
	static ActorManager& Instance()
	{
		static ActorManager instance;
		return instance;
	}

	// 作成
	std::shared_ptr<Actor> Create();

	// 削除
	void Remove(std::shared_ptr<Actor> actor);

	// 更新
	void Update(float elapsedTime);

	// 行列更新
	void UpdateTransform();

	// 描画
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	// 検索
	Actor* GetActor(std::string name);

	// 近くのアクターを取得
	Actor* GetNearActor(Actor origin, ActorType filter);

	// アクター数を取得
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