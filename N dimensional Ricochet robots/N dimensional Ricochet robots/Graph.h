#pragma once
#include <iostream>
#include <vector>
#include <queue>

class Graph {
public:
	void AddEdge(const int& vertex1,const int& vertex2);
	void RemoveEdge(const int& vertex1, const int& vertex2);
	Graph(int size);
	std::vector<int> BFS(const int startVertex, const int endVertex);
	std::vector<int> ParallelBFS(const int startVertex, const int endVertex);
private:
	int size;
	std::vector<std::vector<int>> neighbours;
	void processVertex(const int processingVertex, std::queue<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found);
	void processDepth(std::queue<int>& inQueue, std::queue<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found);
};