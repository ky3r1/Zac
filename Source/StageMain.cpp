#include"StageMain.h"
#include "StageManager.h"
#include "Mathf.h"

StageMain::StageMain()
{
}

StageMain::~StageMain()
{
}

void StageMain::Start()
{
    //������
    if(StageManager::Instance().GetDijkstraAlgorithm() != nullptr)StageManager::Instance().SetDijkstraAlgorithm(nullptr);
    float points = 50;
    std::vector<WayPoint>     waypoints =
    {
                                    //        0        1         2
        {{-points,0,points},0},     //    // �E�[�[�[�[ �E�[�[�[�[�E
        {{0,0,points},1},           //    // �b        �b        �b
        {{points,0,points},2},      //    // �b        �b        �b
        {{points,0,0},3},           //    // �b       8�b        �b
        {{points,0,-points},4},     //    //7�E�[�[�[�[ �E�[�[�[�[�E3
        {{0,0,-points},5},          //    // �b        �b        �b
        {{-points,0,-points},6},    //    // �b        �b        �b
        {{-points,0,0},7},          //    // �b        �b        �b
        {{0,0,0},8},                //    // �E�[�[�[�[ �E�[�[�[�[�E
                                    //        6        5         4
    };
    DijkstraAlgorithm* dijkstra = new DijkstraAlgorithm(waypoints);
    auto add_edge = [&](int from, int to)
    {
        dijkstra->edge(from, to);
    };
    add_edge(0, 1);
    add_edge(0, 7);
    add_edge(1, 2);
    add_edge(1, 8);
    add_edge(2, 3);
    add_edge(3, 4);
    add_edge(3, 8);
    add_edge(4, 5);
    add_edge(5, 6);
    add_edge(5, 8);
    add_edge(6, 7);
    add_edge(7, 8);
    StageManager::Instance().SetDijkstraAlgorithm(dijkstra);
}

void StageMain::Update(float elapsedTime)
{
}

void StageMain::DrawDebug()
{
    DijkstraAlgorithm* dijkstra = StageManager::Instance().GetDijkstraAlgorithm();
    for (WayPoint way_p : dijkstra->GetWayPoints())
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.7f, 0.4f, 0.2f, 1);
        //�����蔻��p�̃f�o�b�O����`��
        Graphics::Instance().GetDebugRenderer()->DrawSphere(way_p.position, way_p.radius, color);
    }
    for (Edge e : dijkstra->GetEdgeVault())
    {
        DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(0.75f, 0.6f, 0.2f, 1);
        DirectX::XMFLOAT3 start = { e.from.x,e.from.y + 0.1f,e.from.z };
        DirectX::XMFLOAT3 end = { e.to.x,e.to.y + 0.1f,e.to.z };
        //�����蔻��p�̃f�o�b�O����`��
        Graphics::Instance().GetLineRenderer()->Line(start, end, color);
    }
}

void StageMain::DrawImGui()
{
}
