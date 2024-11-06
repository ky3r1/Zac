#include "DijkstraAlgorithm.h"
#include "Mathf.h"

void DijkstraAlgorithm::edge(int from, int to)
{
	DirectX::XMFLOAT3 start = waypoints.at(from).position;
    DirectX::XMFLOAT3 end = waypoints.at(to).position;
	edge_vault.push_back({ start, end });
	float distance = Mathf::Distance(waypoints[from].position, waypoints[to].position);
	nodes[from].neighbors[to] = distance;
	nodes[to].neighbors[from] = distance;
}

void DijkstraAlgorithm::run(int start)
{
	// Set starting node
	starting_node = start;

	// Reset graph nodes
	for (auto& node : nodes)
	{
		node.visited = false;
		node.shortest_distance = std::numeric_limits<float>::max(); // Initial value is infinity
		node.previous = -1;
	}

	nodes.at(start).shortest_distance = 0;

	std::priority_queue<std::pair<float/*distance*/, int/*node*/>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> queue; // Priority queue to store nodes with their distances, sorted by shortest distance
	queue.push({ 0.0f, start });

	while (!queue.empty())
	{
		int current = queue.top().second;
		queue.pop();

		if (nodes[current].visited)
			continue;

		nodes[current].visited = true;

		for (decltype(nodes.at(current).neighbors)::const_reference neighbor : nodes.at(current).neighbors)
		{
			int next = neighbor.first;
			float distance = neighbor.second;

			if (nodes[next].shortest_distance > nodes[current].shortest_distance + distance)
			{
				nodes[next].shortest_distance = nodes[current].shortest_distance + distance;
				nodes[next].previous = current;
				queue.push({ nodes[next].shortest_distance, next });
			}
		}
	}
}

void DijkstraAlgorithm::shortest_path(std::vector<int>& path, int end)
{
	assert(starting_node > -1);

	path.clear();

	int current = end;
	while (current != starting_node)
	{
		path.push_back(current);
		current = nodes[current].previous;
	}
	path.push_back(starting_node);

	std::reverse(path.begin(), path.end());
}

int DijkstraAlgorithm::GetNearWayPointId( DirectX::XMFLOAT3 position)
{
    int near_waypoint = -1;
    float min_distance = FLT_MAX;
    for (WayPoint way_p : waypoints)
    {
        float d = 0;
        d = Mathf::Distance(position, way_p.position);
        if (d < min_distance)
        {
            min_distance = d;
            near_waypoint = way_p.id;
        }
    }
	return near_waypoint;
}

std::vector<int> DijkstraAlgorithm::GetPath(DirectX::XMFLOAT3 position,  int target_id)
{
    int near_waypoint = GetNearWayPointId(position);
    run(near_waypoint);
    std::vector<int> path;
    shortest_path(path, target_id);
    return path;
}

void DijkstraAlgorithm::ReSetVisited(std::vector<bool>& visited)
{
	visited.clear();
	for (int i=0;i< waypoints.size();++i)
    {
        visited.push_back(false);
    }
}
