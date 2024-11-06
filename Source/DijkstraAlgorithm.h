#pragma once

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <assert.h>
#include <DirectXMath.h>

struct WayPoint
{
	DirectX::XMFLOAT3 position;
	int id = -1;
	float radius = 0.5f;
};
struct Edge
{
	DirectX::XMFLOAT3 from;
    DirectX::XMFLOAT3 to;
};

class DijkstraAlgorithm
{
public:
    DijkstraAlgorithm(std::vector<WayPoint> way) : waypoints(way), nodes(way.size()), starting_node(-1) {}
    ~DijkstraAlgorithm() {}
public:
	void edge(int from, int to);
	void run(int start);
	void shortest_path(std::vector<int/*node*/>& path, int end);
	//���ݒn����ł��߂�WayPoint��Id��Ԃ�
	int GetNearWayPointId( DirectX::XMFLOAT3 position);
	//���ݒn����ł��߂�WayPoint->target_id�ւ̍ŒZ�o�H��Ԃ�
	std::vector<int> GetPath(DirectX::XMFLOAT3 position,int target_id);
	void ReSetVisited(std::vector<bool>& visited);
private:
	struct node
	{
		std::unordered_map<int/*node*/, float/*distance*/> neighbors; // Map to store the neighboring Waypoints and their distances
		bool visited;
		float shortest_distance;
		int previous;
	};
	std::vector<node> nodes;
	int starting_node;
public:
	std::vector<WayPoint> GetWayPoints() { return waypoints; }
	//void SetWayPoints(std::vector<WayPoint> _waypoints) { waypoints = _waypoints; }
	void AddWatpoints(WayPoint w){ waypoints.push_back(w); }
	std::vector<Edge> GetEdgeVault(){return edge_vault;}
private:
	std::vector<WayPoint> waypoints;
	std::vector<Edge> edge_vault;
};