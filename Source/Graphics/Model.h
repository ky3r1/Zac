﻿#pragma once

#include <memory>
#include <vector>
#include <DirectXMath.h>
#include "Graphics/ModelResource.h"

//アニメーション
struct Animation
{
	int state = 0;		// 再生アニメーション番号
	bool loop = false;	// ループフラグ
	float blend = 0;	// ブレンド時間
	bool stop = false;	// 停止フラグ(モーション中停止したら問題ある場合:true,モーション中停止しても問題ない場合:false)
};

// モデル
class Model
{
public:
	Model(const char* filename);
	Model(std::shared_ptr<ModelResource> res);
	~Model() {}

	struct Node
	{
		const char* name = "";
		Node* parent = nullptr;
		DirectX::XMFLOAT3	scale = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		DirectX::XMFLOAT4	rotate = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
		DirectX::XMFLOAT3	translate = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		DirectX::XMFLOAT4X4	localTransform;
		DirectX::XMFLOAT4X4	worldTransform;

		std::vector<Node*>	children;
	};

	// 行列計算
	void UpdateTransform(const DirectX::XMFLOAT4X4& transform);


	// ノードリスト取得
	const std::vector<Node>& GetNodes() const { return nodes; }
	std::vector<Node>& GetNodes() { return nodes; }
	// リソース取得
	const ModelResource* GetResource() const { return resource.get(); }
	// リソース取得
	std::shared_ptr<ModelResource> GetResourceShare() const { return resource; }
	//ノード検索
	Node* FindNode(const char* name);


	// アニメーション更新処理
	void UpdateAnimation(float elapsedTime);
	// アニメーション再生
	void PlayAnimation(int playerNo, bool loop, float blendSeconds = 0.2f);
	void PlayAnimation(Animation anim);
    // アニメーション停止
    void StopAnimation();
	// 再生アニメーション番号取得
	int GetPlayAnimationNo() { return currentAnimationIndex; }
	int GetPrevPlayAnimationNo() { return prevAnimationIndex; }
	//現在のアニメーション再生時間取得
	float GetCurrentAnimationSeconds() const { return currentAnimationSeconds; }
	// アニメーション再生中か
	bool IsPlayAnimation()const;

private:
	std::shared_ptr<ModelResource>	resource;
	std::vector<Node>				nodes;

	int currentAnimationIndex = -1;
	int prevAnimationIndex = -1;
	float currentAnimationSeconds = 0.0f;
	bool animationLoopFlag = false;
	bool animationEndFlag = false;
	float animationBlendTime = 0.0f;
	float animationBlendSeconds = 0.0f;
};