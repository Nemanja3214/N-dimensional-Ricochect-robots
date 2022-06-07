#include "Graph.h"
const int CUT_OFF = 5;

Graph::Graph(int size): size(size) {
	neighbours.resize(size);
}

void Graph::AddEdge(const int& vertex1, const int& vertex2) {
	if (vertex1 == vertex2)
		return;
	neighbours[vertex1].insert(vertex2);
	neighbours[vertex2].insert(vertex1);
}

void Graph::RemoveEdge(const int& vertex1, const int& vertex2) {
	if (vertex1 == vertex2)
		return;
	neighbours[vertex1].erase(vertex2);
	neighbours[vertex2].erase(vertex1);
}

std::vector<int> Graph::BFS(const int startVertex, const int endVertex) {
	std::vector<int> inQueue;
	std::vector<int> outQueue;
	// added to cloud
	std::vector<bool> visited(size, false);
	visited[0] = true;
	inQueue.push_back(startVertex);

	// remember the nodes that were before visited for path
	std::vector<int> predecessors(size);
	bool found = false;
	while (!inQueue.empty()) {
		// we can't do all at once because we won't know the depth, here each iteration is one depth
		processQueueSerial(inQueue, outQueue, visited, predecessors, endVertex, found);
		if (found)
			return predecessors;

		// outQueue at the end of this iteration becomes inQueue for the next
		std::swap(outQueue, inQueue);
		std::vector<int>empty;
		std::swap(outQueue, empty);
	}
	return std::vector<int>();
}

std::vector<int> Graph::ParallelBFS(const int startVertex, const int endVertex) {
	std::vector<int> inQueue;
	std::vector<int> outQueue;
	// added to cloud
	std::vector<bool> visited(size, false);
	visited[0] = true;
	inQueue.push_back(startVertex);

	// remember the nodes that were before visited for path
	std::vector<int> predecessors(size);
	bool found = false;
	while (!inQueue.empty()) {
		// we can't do all at once because we won't know the depth, here each iteration is one depth
		processQueuePart(inQueue, outQueue, visited, predecessors, endVertex, found);
		if (found)
			return predecessors;
			 
		// outQueue at the end of this iteration becomes inQueue for the next
		std::swap(outQueue, inQueue);
		std::vector<int>empty;
		std::swap(outQueue, empty);
	}
	return std::vector<int>();
}

void Graph::processQueueSerial(std::vector<int>& inQueuePart, std::vector<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found) {
	while (!inQueuePart.empty()) {
		int processingVertex = inQueuePart.back();
		inQueuePart.pop_back();

		for (int neighbour : neighbours[processingVertex]) {
			// not dangerous data race
			if (!visited[neighbour] && neighbour != processingVertex) {
				visited[neighbour] = true;
				// also not dangerous because it doesn't matter which one will be predeccesor as long as they are on the same depth
				predecessors[neighbour] = processingVertex;

				std::unique_lock<std::mutex> l(queueMutex);
				outQueue.push_back(neighbour);
			}
			if (neighbour == endVertex)
				found = true;
		}
	}
}

void Graph::processQueuePart(std::vector<int>& inQueuePart, std::vector<int>& outQueue, std::vector<bool>& visited, std::vector<int>& predecessors, const int endVertex, bool& found) {
	// can parallel
	if (inQueuePart.size() < CUT_OFF) {
		processQueueSerial(inQueuePart, outQueue, visited, predecessors, endVertex, found);
	}
	else {
		tbb::task_group tg;
		std::vector<int> left(inQueuePart.begin(), inQueuePart.begin() + inQueuePart.size() / 2);
		std::vector<int> right(inQueuePart.begin() + inQueuePart.size() / 2, inQueuePart.end());
		tg.run([&]() { processQueuePart(left, outQueue, visited, predecessors, endVertex, found); });
		processQueuePart(right, outQueue, visited, predecessors, endVertex, found);
		//inQueuePart.clear();
		tg.wait();
	}
	
}


void Graph::MakeCube() {
	this->AddEdge(0, 1);
	this->AddEdge(0, 3);
	this->AddEdge(0, 9);

	this->AddEdge(1, 0);
	this->AddEdge(1, 2);
	this->AddEdge(1, 4);
	this->AddEdge(1, 10);

	this->AddEdge(2, 1);
	this->AddEdge(2, 5);
	this->AddEdge(2, 11);

	this->AddEdge(3, 0);
	this->AddEdge(3, 4);
	this->AddEdge(3, 8);
	this->AddEdge(3, 12);

	this->AddEdge(4, 1);
	this->AddEdge(4, 3);
	this->AddEdge(4, 5);
	this->AddEdge(4, 7);
	this->AddEdge(4, 13);

	this->AddEdge(5, 2);
	this->AddEdge(5, 4);
	this->AddEdge(5, 6);
	this->AddEdge(5, 14);

	this->AddEdge(6, 5);
	this->AddEdge(6, 7);
	this->AddEdge(6, 17);

	this->AddEdge(7, 4);
	this->AddEdge(7, 6);
	this->AddEdge(7, 8);
	this->AddEdge(7, 16);

	this->AddEdge(8, 3);
	this->AddEdge(8, 7);
	this->AddEdge(8, 15);

	this->AddEdge(9, 0);
	this->AddEdge(9, 10);
	this->AddEdge(9, 12);
	this->AddEdge(9, 18);

	this->AddEdge(10, 9);
	this->AddEdge(10, 11);
	this->AddEdge(10, 13);
	this->AddEdge(10, 19);

	this->AddEdge(11, 2);
	this->AddEdge(11, 10);
	this->AddEdge(11, 14);
	this->AddEdge(11, 20);
	
	/*this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);
	this->AddEdge(0, 1);*/

}