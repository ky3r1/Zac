#pragma once
#include "CameraController.h"
#include "DijkstraAlgorithm.h"

enum class StageNumber
{
    MainStage,
    None,
};
class StageManager
{
private:
    StageManager() {}
    ~StageManager() {}
public:
    //唯一のインスタンス取得
    static StageManager& Instance()
    {
        static StageManager instance;
        return instance;
    }
    void Initialize();
    void Finalize();
    void Update(float elapsedTime);
    void Render();

private:
    void NoneInitialize();
    void NoneUpdate(float elapsedTime);
    void NoneRender();

    void MainStageInitialize();
    void MainStageUpdate(float elapsedTime);
    void MainStageRender();
public:
    StageNumber GetStageNum() { return stage_num; }
    void SetStageNum(StageNumber num) { stage_num = num; }
private:
    StageNumber stage_num = StageNumber::None;
    CameraController camera_controller;
private:
    bool actor_imgui_checker[static_cast<int>(ActorType::All) + 1];
    float screenWidth = 0;
    float screenHeight = 0;
public:
    DijkstraAlgorithm* GetDijkstraAlgorithm() { return dijkstra_algorithm.get(); }
    void SetDijkstraAlgorithm(DijkstraAlgorithm* dijkstra) { dijkstra_algorithm.reset(dijkstra); }
private:
    std::shared_ptr<DijkstraAlgorithm> dijkstra_algorithm = nullptr;
};