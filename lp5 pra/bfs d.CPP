#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// --------------------- Parallel BFS ---------------------
void parallelBFS(const vector<vector<int>> &graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Parallel BFS: ";

    while (!q.empty()) {
        int levelSize = q.size();

        #pragma omp parallel for
        for (int i = 0; i < levelSize; ++i) {
            int curr;

            #pragma omp critical
            {
                if (!q.empty()) {
                    curr = q.front();
                    q.pop();
                } else {
                    continue;
                }
            }

            cout << curr << " ";

            for (int neighbor : graph[curr]) {
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
    }
    cout << endl;
}

// --------------------- Parallel DFS ---------------------
void parallelDFSUtil(const vector<vector<int>> &graph, int node, vector<bool> &visited) {
    visited[node] = true;
    cout << node << " ";

    #pragma omp parallel for
    for (int i = 0; i < graph[node].size(); ++i) {
        int neighbor = graph[node][i];
        if (!visited[neighbor]) {
            #pragma omp task
            parallelDFSUtil(graph, neighbor, visited);
        }
    }
}

void parallelDFS(const vector<vector<int>> &graph, int start) {
    int n = graph.size();
    vector<bool> visited(n, false);

    cout << "Parallel DFS: ";

    #pragma omp parallel
    {
        #pragma omp single
        parallelDFSUtil(graph, start, visited);
    }

    cout << endl;
}

// --------------------- Main ---------------------
int main() {
    int n, e, start;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> graph(n);
    cout << "Enter " << e << " undirected edges (u v):" << endl;
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    cout << "Enter starting node: ";
    cin >> start;

    parallelBFS(graph, start);
    parallelDFS(graph, start);

    return 0;
}
