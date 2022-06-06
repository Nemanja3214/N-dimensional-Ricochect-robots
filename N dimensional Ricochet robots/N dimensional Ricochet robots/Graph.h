#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <tbb/task_group.h>
#include <set>

class Graph {
public:
	void AddEdge(const int& vertex1,const int& vertex2);
	void RemoveEdge(const int& vertex1, const int& vertex2);
	Graph(int size);
	std::vector<int> BFS(const int startVertex, const int endVertex);
	std::vector<int> ParallelBFS(const int startVertex, const int endVertex);
	void MakeCube();
private:
	int size;
	std::mutex queueMutex;
	std::vector<std::set<int>> neighbours;
	void processQueuePart(std::vector<int>& inQueuePart, std::vector<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found);

};