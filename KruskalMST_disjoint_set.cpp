#include<iostream>
#include<algorithm>
using namespace std;

struct Edge {
	int src, dest, weight;
};

class Graph {
public:
	int v, e;
	Edge* edge;
};

Graph* CreateGraph(int v, int e) {
	Graph* g = new Graph;
	g->v = v;
	g->e = e;
	g->edge = new Edge[e];
	return g;
}

bool Compare2(Edge e1, Edge e2) {
	return e1.weight < e2.weight;
}

int find(int* parent, int vert) {
	while (vert != parent[vert]) {
		parent[vert] = parent[parent[vert]];	//path-compression
		vert = parent[vert];
	}
	return vert;
}

void weighted_union(int* parent, int* size, int subset1, int subset2) {
	if (size[subset1] > size[subset2]) {
		parent[subset2] = subset1;
		size[subset1] += size[subset2];
	}
	else {
		parent[subset1] = subset2;
		size[subset2] += size[subset1];
	}
}

void KruskalMST(Graph* g) {
	int* parent = new int[g->v];
	int* size = new int[g->v];

	Edge* mst = new Edge[g->v];

	for (int i = 0; i < g->v; ++i) {
		parent[i] = i;
		size[i] = 1;
	}

	sort(g->edge, g->edge + g->e, Compare2);
	int j = 0;
	for (int i = 0; i < g->e; ++i) {
		int x = find(parent, g->edge[i].src);
		int y = find(parent, g->edge[i].dest);

		if (x == y)
			continue;

		mst[j].src = g->edge[i].src;
		mst[j].dest = g->edge[i].dest;
		mst[j].weight = g->edge[i].weight;
		j++;
		
		weighted_union(parent, size, x, y);
	}

	for (int i = 0; i < j; ++i) {
		cout << mst[i].src << "->" << mst[i].dest << ":" << mst[i].weight << endl;
	}

}

int main() {
	Graph* graph = CreateGraph(9, 14);
//	   1--2----3
//	 / |  |\   |\
//	0  |  8 \  | 4
//   \ | /|  \ |/
//     7--6----5
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = 4;

	graph->edge[1].src = 1;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 8;

	graph->edge[2].src = 2;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 7;

	graph->edge[3].src = 3;
	graph->edge[3].dest = 4;
	graph->edge[3].weight = 9;

	graph->edge[4].src = 4;
	graph->edge[4].dest = 5;
	graph->edge[4].weight = 10;

	graph->edge[5].src = 5;
	graph->edge[5].dest = 6;
	graph->edge[5].weight = 2;

	graph->edge[6].src = 6;
	graph->edge[6].dest = 7;
	graph->edge[6].weight = 1;

	graph->edge[7].src = 7;
	graph->edge[7].dest = 0;
	graph->edge[7].weight = 8;

	graph->edge[8].src = 1;
	graph->edge[8].dest = 7;
	graph->edge[8].weight = 11;

	graph->edge[9].src = 7;
	graph->edge[9].dest = 8;
	graph->edge[9].weight = 7;

	graph->edge[10].src = 8;
	graph->edge[10].dest = 6;
	graph->edge[10].weight = 6;

	graph->edge[11].src = 2;
	graph->edge[11].dest = 8;
	graph->edge[11].weight = 2;

	graph->edge[12].src = 2;
	graph->edge[12].dest = 5;
	graph->edge[12].weight = 4;

	graph->edge[13].src = 5;
	graph->edge[13].dest = 3;
	graph->edge[13].weight = 14;
	KruskalMST(graph);

	cin.get();
}
