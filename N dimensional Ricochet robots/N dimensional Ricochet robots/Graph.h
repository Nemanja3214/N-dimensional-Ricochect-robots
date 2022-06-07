#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <tbb/task_group.h>
#include <set>
#include <string>
#include <fstream>
#include <sstream>

class Graph {
public:
	void AddEdge(const int& vertex1,const int& vertex2);
	void RemoveEdge(const int& vertex1, const int& vertex2);
	Graph(int size);
	std::vector<int> BFS(const int startVertex, const int endVertex, bool parallel);
	void MakeCube();
	void LoadGraph(std::string path);
private:
	int size;
	std::mutex queueMutex;
	std::vector<std::set<int>> neighbours;
	void processQueuePart(std::vector<int>::iterator startIt, std::vector<int>::iterator endIt, std::vector<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found);
	void processQueueSerial(std::vector<int>::iterator startIt, std::vector<int>::iterator endIt, std::vector<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found);
};