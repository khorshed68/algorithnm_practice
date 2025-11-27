#include <iostream>
#include <vector>
#include <iomanip> // for std::setw

using namespace std;

const int INF = 1e9; // Representation of "infinity"

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    // Initialize distance matrix
    vector<vector<int>> dist(n, vector<int>(n, INF));

    // Distance to self is 0
    for (int i = 0; i < n; i++)
        dist[i][i] = 0;

    cout << "Enter edges (u v weight) 0-based indexing:\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dist[u][v] = w; // For directed graph
        // dist[v][u] = w; // Uncomment if undirected graph
    }

    // Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) { // avoid overflow
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Print shortest distance matrix
    cout << "\nShortest distances between every pair of vertices:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << setw(5) << "INF";
            else
                cout << setw(5) << dist[i][j];
        }
        cout << "\n";
    }

    return 0;
}
