#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
// Structure to represent an edge
struct Edge {
    int u, v, weight;
};
// Disjoint Set Union (Union-Find) structure
struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 0; i <= n; ++i)
            parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return false; // Already connected
        // Union by rank
        if (rank[px] < rank[py])
            parent[px] = py;
        else if (rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
};
// Kruskal's algorithm
int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });
    DSU dsu(n);
    int mst_weight = 0;
    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst_weight += e.weight;
            cout << "Edge chosen: " << e.u << " - " << e.v << " with weight " << e.weight << "\n";
        }
    }
    return mst_weight;
}
int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    vector<Edge> edges(m);
    cout << "Enter edges in format: u v weight\n";
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    int mst_weight = kruskal(n, edges);
    cout << "Total weight of MST: " << mst_weight << "\n";
    return 0;
}
