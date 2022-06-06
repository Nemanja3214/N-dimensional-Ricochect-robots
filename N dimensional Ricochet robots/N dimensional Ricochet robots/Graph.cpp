#include "Graph.h"
Graph::Graph(int size): size(size) {
	neighbours.resize(size);
}

void Graph::AddEdge(const int& vertex1, const int& vertex2) {
	if (vertex1 == vertex2)
		return;
	neighbours[vertex1].push_back(vertex2);
	neighbours[vertex2].push_back(vertex1);
}

void Graph::RemoveEdge(const int& vertex1, const int& vertex2) {
	if (vertex1 == vertex2)
		return;
	neighbours[vertex1].erase(std::remove(neighbours[vertex1].begin(), neighbours[vertex1].end(), vertex2));
	neighbours[vertex2].erase(std::remove(neighbours[vertex2].begin(), neighbours[vertex2].end(), vertex1));
}

std::vector<int> Graph::BFS(const int startVertex, const int endVertex) {
	std::queue<int> verticesToProcess;
	// added to cloud
	std::vector<bool> visited(size, false);
	verticesToProcess.push(startVertex);

	// remember the nodes that were before visited for path
	std::vector<int> predecessors(size);
	int processingVertex;

	while (!verticesToProcess.empty()) {
		processingVertex = verticesToProcess.front();
		verticesToProcess.pop();

		for(int neighbour : neighbours[processingVertex]){
			if (!visited[neighbour] && neighbour != processingVertex) {
				visited[neighbour] = true;
				predecessors[neighbour] = processingVertex;
				verticesToProcess.push(neighbour);
			}

			if (neighbour == endVertex)
				return predecessors;
		}
	}
	return std::vector<int>();
}

std::vector<int> Graph::ParallelBFS(const int startVertex, const int endVertex) {
	std::queue<int> verticesToProcess;
	// added to cloud
	std::vector<bool> visited(size, false);
	verticesToProcess.push(startVertex);

	// remember the nodes that were before visited for path
	std::vector<int> predecessors(size);
	int processingVertex;

	while (!verticesToProcess.empty()) {
		processingVertex = verticesToProcess.front();
		verticesToProcess.pop();

		for (int neighbour : neighbours[processingVertex]) {
			if (!visited[neighbour] && neighbour != processingVertex) {
				visited[neighbour] = true;
				predecessors[neighbour] = processingVertex;
				verticesToProcess.push(neighbour);
			}

			if (neighbour == endVertex)
				return predecessors;
		}
	}
	return std::vector<int>();
}