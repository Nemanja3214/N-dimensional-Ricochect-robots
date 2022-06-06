#include <iostream>
#include "Graph.h"
using namespace std;

void printPath(int end, vector<int>& path) {
	if (end <= 0) {
		cout << 0;
		return;
	}
	cout << end << endl;
	printPath(path[end], path);
}
int main() {
	cout << "Hello" << endl;
	Graph g(9);
	g.AddEdge(0, 1);
	g.AddEdge(0, 2);
	g.AddEdge(0, 3);
	g.AddEdge(1, 4);
	g.AddEdge(1, 5);
	g.AddEdge(2, 6);
	g.AddEdge(3, 6);
	g.AddEdge(6, 7);
	g.AddEdge(7, 8);
	vector<int> solution = g.BFS(0, 8);
	int i = 0;
	printPath(solution.size() - 1, solution);

}