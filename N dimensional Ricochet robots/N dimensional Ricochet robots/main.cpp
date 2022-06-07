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
	Graph g(27);
	/*g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(0, 3);
	g.AddEdge(1, 4);
	g.AddEdge(1, 5);
	g.AddEdge(2, 6);
	g.AddEdge(3, 6);
	g.AddEdge(6, 7);
	//g.AddEdge(1, 8);
	//g.RemoveEdge(6, 7);
	g.AddEdge(7, 8);
	g.AddEdge(8, 9);

	g.AddEdge(0, 10);
	g.AddEdge(0, 11);
	g.AddEdge(0, 12);
	g.AddEdge(0, 13);
	g.AddEdge(0, 14);*/

	//vector<int> solution = g.BFS(0, 8);
	//int i = 0;
	//printPath(solution.size() - 1, solution);
	g.MakeCube();
	int startNode = 0;
	int endNode = 25;


	auto startTime = chrono::high_resolution_clock::now();
	vector<int> solutionSerial = g.BFS(startNode, endNode);
	auto endTime = chrono::high_resolution_clock::now();
	printPath(startNode, endNode, solutionSerial);
	cout << "Serial time: " << (endTime - startTime).count() << endl;

	startTime = chrono::high_resolution_clock::now();
	vector<int> solutionParallel = g.ParallelBFS(startNode, endNode);
	endTime = chrono::high_resolution_clock::now();
	printPath(startNode, endNode, solutionParallel);
	cout << "Parallel time: " << (endTime - startTime).count();

}