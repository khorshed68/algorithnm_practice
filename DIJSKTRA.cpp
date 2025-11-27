#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;
// Pair: {distance, vertex}
typedef pair<int, int> pii;
void dijkstra(int n, vector<vector<pii>>& adj, int src) {
    vector<int> dist(n + 1, INT_MAX);  // Distance from source to each vertex
    dist[src] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, src});
    while (!pq.empty()) {
        int u_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (u_dist > dist[u]) continue;  // Skip if outdated
        for (auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    // Print shortest distances
    cout << "Vertex\tDistance from Source " << src << "\n";
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX)
            cout << i << "\tINF\n";
        else
            cout << i << "\t" << dist[i] << "\n";
    }
}
int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;
    vector<vector<pii>> adj(n + 1);  // 1-based indexing
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});  // Remove this line if the graph is directed
    }
    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    dijkstra(n, adj, src);
    return 0;
}
