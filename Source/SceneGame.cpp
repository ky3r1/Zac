#include "SceneGame.h"

#include "StageManager.h"
// 初期化
void SceneGame::Initialize()
{
	StageManager::Instance().SetStageNum(StageNumber::MainStage);
    //ステージ初期化
    StageManager::Instance().Initialize();

}

// 終了化
void SceneGame::Finalize()
{
	//ステージ終了化
	StageManager::Instance().Finalize();
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	//ステージ終了化
	StageManager::Instance().Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
{
	//ステージ終了化
	StageManager::Instance().Render();
}