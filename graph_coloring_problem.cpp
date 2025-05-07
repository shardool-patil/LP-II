#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int n;
    unordered_map<int, vector<int>> adjList;

    Graph(int nodes) : n(nodes) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    bool isSafe(int node, int color, unordered_map<int, int>& color_assignment) {
        for (int neighbour : adjList[node]) {
            if (color_assignment[neighbour] == color)
                return false;
        }
        return true;
    }

    bool colorGraph(int node, int maxColors, unordered_map<int, int>& color_assignment) {
        if (node == n)
            return true;

        for (int color = 1; color <= maxColors; color++) {
            if (isSafe(node, color, color_assignment)) {
                color_assignment[node] = color;
                if (colorGraph(node + 1, maxColors, color_assignment))
                    return true;
                color_assignment[node] = 0; // backtrack
            }
        }
        return false;
    }

    void solveGraphColoring(int maxColors) {
        unordered_map<int, int> color_assignment;
        // Initialize all nodes as unassigned (color 0)
        for (int i = 0; i < n; i++) {
            color_assignment[i] = 0;
        }

        bool solved = false;
        int minColorsUsed = 0;

        for (int colors = 1; colors <= maxColors; colors++) {
            // Reset colors
            for (int i = 0; i < n; i++) {
                color_assignment[i] = 0;
            }

            if (colorGraph(0, colors, color_assignment)) {
                solved = true;
                minColorsUsed = colors;
                break;
            }
        }

        if (solved) {
            cout << "\nSolution found with " << minColorsUsed << " colors:\n";
            for (int i = 0; i < n; i++) {
                cout << "Node " << i << " -> Color " << color_assignment[i] << endl;
            }

            set<int> unique_colors;
            for (const auto& entry : color_assignment) {
                unique_colors.insert(entry.second);
            }

            cout << "\n{Colors Used: " << unique_colors.size() << "} Used as follows:\n";
            for (int color : unique_colors) {
                cout << "Color " << color << endl;
            }
        } else {
            cout << "\nNo solution possible with " << maxColors << " colors.\n";
        }
    }

    void printAdjacencyList() {
        cout << "\nAdjacency List:\n";
        for (const auto& pair : adjList) {
            cout << "Node " << pair.first << ": ";
            for (int neighbour : pair.second)
                cout << neighbour << " ";
            cout << endl;
        }
    }
};

int main() {
    int n, e, maxColors;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> e;

    Graph g(n);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "Enter number of colors available: ";
    cin >> maxColors;

    g.printAdjacencyList();
    g.solveGraphColoring(maxColors);

    return 0;
}
