#include<iostream>
#include<limits.h>
#include<vector>
#include<queue>

using namespace std;

void AddEdge(vector<pair<int, int>> adjl[], const int& u, const int& v, const int& weight) {
	adjl[u].push_back({ v,weight });
	adjl[v].push_back({ u,weight });
}

void Dijkstra(vector<pair<int, int>> adjl[], int v) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	int* dist = new int[v];
	for (int i = 0; i < v; ++i)
		dist[i] = INT_MAX;

	dist[0] = 0;
	pq.push({ dist[0], 0 });	//weight vertex

	while (!pq.empty()) {
		pair<int,int> u = pq.top();
		pq.pop();

		for (pair<int,int> v : adjl[u.second]) {
			if (dist[v.first] > dist[u.second] + v.second) {
				dist[v.first] = dist[u.second] + v.second;
				pq.push({ dist[v.first],v.first });
			}
		}
	}

	for (int i = 0; i < v; ++i) {
		cout << i << " " << dist[i] << endl;
	}
}

int main() {
	const int v = 9;
	vector<pair<int, int>> adjl[v];	//pair of vertex and its wieight
	AddEdge(adjl, 0, 1, 4);
	AddEdge(adjl, 0, 7, 8);
	AddEdge(adjl, 1, 2, 8);
	AddEdge(adjl, 1, 7, 11);
	AddEdge(adjl, 2, 3, 7);
	AddEdge(adjl, 2, 8, 2);
	AddEdge(adjl, 2, 5, 4);
	AddEdge(adjl, 3, 4, 9);
	AddEdge(adjl, 3, 5, 14);
	AddEdge(adjl, 4, 5, 10);
	AddEdge(adjl, 5, 6, 2);
	AddEdge(adjl, 6, 7, 1);
	AddEdge(adjl, 6, 8, 6);
	AddEdge(adjl, 7, 8, 7);

	Dijkstra(adjl, v);
	
	cin.get();
}
