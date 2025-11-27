#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u, v, w;
};
// Bellman-Ford to find h values
bool bellmanFord(int V, vector<Edge>& edges, vector<int>& h) {
    h.assign(V + 1, INT_MAX);
    h[V] = 0; // Extra vertex
    vector<Edge> newEdges = edges;
    // Add zero-weight edges from extra vertex to all vertices
    for(int i=0;i<V;i++) newEdges.push_back({V, i, 0});
    int newV = V + 1;
    for(int i=0;i<newV-1;i++) {
        for(auto e: newEdges) {
            if(h[e.u] != INT_MAX && h[e.v] > h[e.u] + e.w)
                h[e.v] = h[e.u] + e.w;
        }
    }
    // Check negative cycle
    for(auto e: newEdges) {
        if(h[e.u] != INT_MAX && h[e.v] > h[e.u] + e.w)
            return false;
    }
    h.pop_back();
    return true;
}
// Dijkstra's algorithm
vector<int> dijkstra(int src, vector<vector<pair<int,int>>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    pq.push({0, src});
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d > dist[u]) continue;
        for(auto [v, w]: adj[u]) {
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
// Johnson's algorithm
vector<vector<int>> johnson(int V, vector<Edge>& edges) {
    vector<int> h;
    if(!bellmanFord(V, edges, h)) {
        cout << "Graph contains a negative weight cycle!" << endl;
        return {};
    }
    // Reweight edges
    vector<vector<pair<int,int>>> adj(V);
    for(auto e: edges) {
        int w_new = e.w + h[e.u] - h[e.v];
        adj[e.u].push_back({e.v, w_new});
    }
    // Run Dijkstra from each vertex
    vector<vector<int>> dist(V);
    for(int i=0;i<V;i++) {
        dist[i] = dijkstra(i, adj);
        for(int j=0;j<V;j++) {
            if(dist[i][j] != INT_MAX) dist[i][j] = dist[i][j] - h[i] + h[j];
        }
    }
    return dist;
}
int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;
    vector<Edge> edges(E);
    cout << "Enter each edge in format (u v w) with 0-based indexing:\n";
    for(int i=0;i<E;i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    vector<vector<int>> dist = johnson(V, edges);
    if(!dist.empty()) {
        cout << "\nAll-pairs shortest distances:\n";
        for(int i=0;i<V;i++) {
            for(int j=0;j<V;j++) {
                if(dist[i][j] == INT_MAX) cout << "INF ";
                else cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
