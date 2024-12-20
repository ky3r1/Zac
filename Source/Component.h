#pragma once
#include "Actor.h"

class Component
{
public:
	Component() {}
	virtual ~Component() {}

	// 名前取得
	virtual const char* GetName() const = 0;

	// 開始処理
	virtual void Start() {}

	// 更新処理
	virtual void Update(float elapsedTime) {}

	virtual void Render(ID3D11DeviceContext* dc, Shader* shader) {}

	// GUI描画
	virtual void DrawImGui() {}

	//デバッグプリミティブ描画
	virtual void DrawDebug(){}

	// アクター設定
	void SetActor(std::shared_ptr<Actor> actor) { this->actor = actor; }

	//初期化
    virtual void Reset() {}

	// アクター取得
	std::shared_ptr<Actor> GetActor() { return actor.lock(); }

private:
	std::weak_ptr<Actor>	actor;
};