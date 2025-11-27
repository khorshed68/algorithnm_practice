#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(const vector<int>& key, const vector<bool>& mstSet, int V) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the MST stored in parent[]
void printMST(const vector<int>& parent, const vector<vector<int>>& graph, int V) {
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " - " << i << "\t" << graph[i][parent[i]] << endl;
    }
}

// Function to construct MST using Prim's algorithm
void primMST(const vector<vector<int>>& graph, int V) {
    vector<int> parent(V);   // Stores MST
    vector<int> key(V, INT_MAX); // Key values used to pick minimum weight edge
    vector<bool> mstSet(V, false); // To represent set of vertices included in MST

    key[0] = 0;      // Start from vertex 0
    parent[0] = -1;  // First node is root of MST

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet, V); // Pick minimum key vertex
        mstSet[u] = true;               // Add it to MST

        // Update key and parent of adjacent vertices
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printMST(parent, graph, V);
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter adjacency matrix (0 if no edge):\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    primMST(graph, V);

    return 0;
}
