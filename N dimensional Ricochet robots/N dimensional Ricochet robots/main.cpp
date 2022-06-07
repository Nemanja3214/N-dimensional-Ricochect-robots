#include <iostream>
#include "Graph.h"
#include <chrono>

using namespace std;

void printPath(int start, int end, vector<int>& path) {
	if (path.empty()) {
		cout << "There is no path between two nodes" << endl;
		return;
	}
	if (end == start) {
		cout << end << endl;
		return;
	}
	cout << end << endl;
	printPath(start, path[end], path);
}



int main() {
	cout << "Started making graph" << endl;
	Graph g(1000000);
	g.LoadGraph("../Input/input.txt");
	cout << "Finished making graph" << endl;
	int startNode = 0;
	int endNode = 25;


	auto startTime = chrono::high_resolution_clock::now();
	vector<int> solutionSerial = g.BFS(startNode, endNode, false);
	auto endTime = chrono::high_resolution_clock::now();
	printPath(startNode, endNode, solutionSerial);
	cout << "Serial time: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << endl;

	startTime = chrono::high_resolution_clock::now();
	vector<int> solutionParallel = g.BFS(startNode, endNode, true);
	endTime = chrono::high_resolution_clock::now();
	printPath(startNode, endNode, solutionParallel);
	cout << "Parallel time: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << endl;

}