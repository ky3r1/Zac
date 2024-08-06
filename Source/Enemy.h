#pragma once
#include "Graphics/Shader.h"
#include "Character.h"

class BehaviorTree;
class BehaviorData;
class NodeBase;

enum class EnemySlimeAnimation
{
	Hit,
	Walk,
	Attack01,
	Death,
};

enum
{
	Enemy01_Num,
	Enemy02_Num,
	Enemy03_Num,
	EnemyBoss_Num,
};

//エネミー
class Enemy : public Character
{
public:
	Enemy() {}
    ~Enemy() override {}
	// 名前取得
	virtual const char* GetName() const override { return "Enemy"; }

	// 開始処理
	void Start() override;

	// 更新処理
	void Update(float elapsedTime) override;

	void ShotObject();

	//Search
    bool Search(DirectX::XMFLOAT3 target_position_s);

	// GUI描画
	virtual void DrawImGui() override;
	// デバッグ描画
	void DrawDebug() override;
public:
    // 検索範囲
    float GetSearchRange() const { return search_range; }
    void SetSearchRange(float range) { search_range = range; }
	// 攻撃範囲
	float GetAdjacentAttackRange() const { return adjacent_attack_range; }
	void SetAdjacentAttackRange(float range) { adjacent_attack_range = range; }
    // タイマー
    float GetRunTimer() const { return run_timer; }
    void SetRunTimer(float timer) { run_timer = timer; }
    // ターゲット位置
    DirectX::XMFLOAT3 GetTargetPosition() const { return target_position; }
    void SetTargetPosition(DirectX::XMFLOAT3 position) { target_position = position; }
public:
	enum slimeAnimation
    {
		IdleNormal,
		IdleBattle,
        Attack01,
        Attack02,
		WalkFront,
        WalkBack,
        WalkLeft,
        WalkRight,
		Run,
		Search01,
        Search02,
        Taunt,
		Victory,
		GetHit,
		Dizzy,
		Die
    };
protected:
	float search_range = 50.0f;
	float adjacent_attack_range = 10.0f;//近接
	float remote_attack_range	= 40.0f;//遠距離
	float run_timer = 10.0f;
	DirectX::XMFLOAT3 target_position = { 0.0f, 0.0f, 0.0f };

	BehaviorTree* aiTree = nullptr;
	BehaviorData* behaviorData = nullptr;
	NodeBase* activeNode = nullptr;
};