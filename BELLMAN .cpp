#include <iostream>
#include <vector>
#include <climits>
using namespace std;
struct Edge {
    int u, v, weight; // Edge from u -> v with given weight
};
bool bellmanFord(int n, int m, vector<Edge>& edges, int src) {
    vector<int> dist(n + 1, INT_MAX); // Distance from source
    dist[src] = 0;
    // Relax all edges n-1 times
    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < m; j++) {
            int u = edges[j].u;
            int v = edges[j].v;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    // Check for negative weight cycle
    for (int j = 0; j < m; j++) {
        int u = edges[j].u;
        int v = edges[j].v;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            cout << "Graph contains a negative weight cycle.\n";
            return false;
        }
    }
    // Print distances
    cout << "Vertex distances from source " << src << ":\n";
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX)
            cout << "Vertex " << i << ": INF\n";
        else
            cout << "Vertex " << i << ": " << dist[i] << "\n";
    }
    return true;
}
int main() {
    int n, m; // n = number of vertices, m = number of edges
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    cout << "Enter edges in format (u v weight):\n";
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    bellmanFord(n, m, edges, src);
    return 0;
}
