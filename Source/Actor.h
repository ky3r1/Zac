#pragma once
#include "All.h"
//#include "Collision.h"

enum class ActorType
{
	Player,
	Enemy,
	Stage,
	Object,
	Bullet,
	Camera,
	None,
	All,
};

enum class FOM//feeling of material(オブジェクトの質感)
{
	Normal,//当たったら止まる(Y軸:重力処理〇)
	Bounse,//当たったら反発する
	Friction,//摩擦がかかる
	Friction_One,//当たったら止まる(Y軸:重力処理X) ->Y軸の処理に使うとFrictionと同じ
	None,
};

enum class AnimationState //アニメーション状態
{
    Idle,
    Walk,
    Run,
    Jump,
    Attack,
	Spown,
	Land,
	GoesDown,
	Death,
	None,
};

struct HitResult
{
	DirectX::XMFLOAT3 position = { 0,0,0 }; //レイとポリゴンの交点
	DirectX::XMFLOAT3 normal = { 0,0,0 };   //衝突したポリゴンの法線ベクトル
	float             distance = 0.0f;      //レイの始点から交点までの距離
	int               materialIndex = -1;   //衝突したポリゴンのマテリアル番号
	DirectX::XMFLOAT3 rotation = { 0,0,0 };   //角度
};

struct Sphere
{
	DirectX::XMFLOAT3 position = { 0,0,0 };
	float             radius = 0.0f;
	float             weight = 0.0f;
};

struct Cylinder
{
	Sphere            sphere;
	float             height = 0.0f;
};

struct DelayTime
{
	float time;
	bool checker = false;
};

//前方宣言
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

	// 開始処理
	virtual void Start();

	// 更新処理
	virtual void Update(float elapsedTime);

	// 行列の更新
	virtual void UpdateTransform();

	virtual void Render(ID3D11DeviceContext* dc, Shader* shader);

	// GUI表示
	virtual void OnGUI();

	//デバッグプリミティブ
	virtual void DrawDebug();

	//DelayTime更新
	void UpdateDelayTime(DelayTime& delaytime, float maxtime);
public:
	//////////////////////////////////////////////////////////////////////////
	//							セッター・ゲッター							//
	//////////////////////////////////////////////////////////////////////////

	// 名前のセッター・ゲッター
	void SetName(const char* name) { this->name = name; }
	void SetName(std::string name) { this->name = name.c_str(); }
	const std::string GetName() const { return name; }

	// 位置のセッター・ゲッター
	void SetPosition(const DirectX::XMFLOAT3& position) { this->parameter.collision_cylinder.sphere.position = position; }
	const DirectX::XMFLOAT3& GetPosition() const { return parameter.collision_cylinder.sphere.position; }

	// 回転のセッター・ゲッター
	void SetRotation(const DirectX::XMFLOAT4& rotation){ this->parameter.rotation = rotation;}
	const DirectX::XMFLOAT4& GetRotation() const { return parameter.rotation; }

	// スケールのセッター・ゲッター
	void SetScale(const DirectX::XMFLOAT3& scale){ this->parameter.scale = scale; }
	const DirectX::XMFLOAT3& GetScale() const { return parameter.scale; }

	//色のセッター・ゲッター
	void SetColor(const DirectX::XMFLOAT4& color){ this->parameter.color = color; }
	const DirectX::XMFLOAT4& GetColor() const { return parameter.color; }

	// 行列のゲッター
	const DirectX::XMFLOAT4X4& GetTransform() const { return parameter.transform; }

	//重さ
    float GetWeight() const { return parameter.collision_cylinder.sphere.weight; }
	void SetWeight(float weight) {parameter.collision_cylinder.sphere.weight = weight;}

	//高さ
    float GetHeight() const { return parameter.collision_cylinder.height; }
    void SetHeight(float height) {	parameter.collision_cylinder.height = height;}

	//半径
    float GetRadius() const { return parameter.collision_cylinder.sphere.radius; }
    void SetRadius(float radius) { parameter.collision_cylinder.sphere.radius = radius;}

	//Sphere
    Sphere GetSphere() const { return parameter.collision_cylinder.sphere; }
    void SetSphere(const Sphere& sphere) { parameter.collision_cylinder.sphere = sphere; }

	//Cylinder
    Cylinder GetCylinder() const { return parameter.collision_cylinder; }
    void SetCylinder(const Cylinder& cylinder) {parameter.collision_cylinder = cylinder;}


	// モデルのセッター・ゲッター
	void LoadModel(const char* filename);
	Model* GetModel() const { return model.get(); }

	// タイプのセッター・ゲッター	
	void SetActorType(ActorType type) { this->type = type; }
	ActorType GetActorType() const { return type; }

	//FOM_Y
    void SetFomY(FOM f) { fom_Y = f; }
    FOM GetFomY() const { return fom_Y; }

	//FOM_XZ
	void SetFomXZ(FOM f) { fom_XZ = f; }
	FOM GetFomXZ() const { return fom_XZ; }

	// レイキャストフラグのセッター・ゲッター
    void SetRaycastFlg(bool flg) { raycast_flg = flg; }
    bool GetRaycastFlg() const { return raycast_flg; }

	//old_transform
    void SetOldTransform(const DirectX::XMFLOAT4X4& transform) { old_transform = transform; }
    const DirectX::XMFLOAT4X4& GetOldTransform() const { return old_transform; }

    //姿勢制御フラグ
	void SetAttitudeControlFlag(bool flag) { attitude_control = flag; }
    bool GetAttitudeControlFlag() { return attitude_control; }

	//レイポジション
    void SetRayPosition(const DirectX::XMFLOAT3& position) { ray_position = position; }
    const DirectX::XMFLOAT3& GetRayPosition() const { return ray_position; }

	//アニメーションスピード
    void SetAnimationSpeed(float speed) { animspeed = speed; }
    float GetAnimationSpeed() const { return animspeed; }

public:
    //////////////////////////////////////////////////////////////////////////
    //							コンポーネント							//
    //////////////////////////////////////////////////////////////////////////

	// コンポーネント追加
	template<class T, class... Args>
	std::shared_ptr<T> AddComponent(Args... args)
	{
		parameter_backup = parameter;
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
	Parameter			parameter_backup;
	
	bool 				attitude_control = false;
	DirectX::XMFLOAT4X4 old_transform = { 
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };

	// フィルター用のタイプ
	ActorType type = ActorType::None;
	//質感
    FOM fom_Y = FOM::Normal;
	FOM fom_XZ = FOM::Normal;
	//Ray情報
	bool			  raycast_flg = false;
    DirectX::XMFLOAT3 ray_position = { 0,0,0 };

	float animspeed = 1.0f;

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

	//全削除
    void Clear();

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

	//Player
    Actor* GetPlayer()
    {
        return GetActor("Player");
    }

	// 近くのアクターを取得
	bool GetNearActor(Actor* origin,Actor& result, ActorType filter);
	Actor* GetNearActor(Actor* origin, ActorType filter);
	//std::unique_ptr<Actor> GetNearActor(Actor* origin, ActorType filter);

	//RayCast用アクター取得
	bool GetNearActorRayCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, HitResult& hit_result,Actor** reactor);
	bool GetNearActorRayCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end, HitResult& hit_result);
	//SphereCast用アクター取得
	bool GetNearActorSphereCast(DirectX::XMFLOAT3 start, DirectX::XMFLOAT3 end,float radius, HitResult& hit_result, Actor** reactor);

	// アクター数を取得
	int GetActorCount(ActorType filter);

	//ヒットストップ管理
	void ActorHitStop(float elapsedTime);

public:
	void SetHitStop(ActorType filter,float timer,float anim_speed)
	{ 
		hit_stop = true;					//使いたいときtrue
		hit_stop_filter = filter;			//ヒットストップ掛けたいタイプにフィルター
		hit_stop_timer = timer;				//ヒットストップする時間
		hit_stop_anim_speed = anim_speed;	//ヒットストップで減速するアニメーションの倍率(0.0f~1.0f)
	}
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
	bool					guichecker = false;

	//hitstop用
	bool					hit_stop = false;
	ActorType				hit_stop_filter = ActorType::All;
	float					hit_stop_timer = 1.0f;
	float					hit_stop_anim_speed = 1.0f;
};