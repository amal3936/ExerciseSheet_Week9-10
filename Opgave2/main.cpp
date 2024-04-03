#include <iostream>
#include "ClassesFromWeek09/graph_class.h"

using namespace std;

int main() {
    Graph graph(4);
    vector<int> dist(4);
    vector<int> path(4);

    graph.addWeightedEdge(0, 1, 5);
    graph.addWeightedEdge(0, 2, 2);
    graph.addWeightedEdge(1, 2, -10);
    graph.addWeightedEdge(1, 3, 1);
    graph.addWeightedEdge(2, 3, 5);
    graph.addWeightedEdge(3, 2, 5);

    // Dijkstra algorithm
    /*cout << "Dijkstra's Algorithm:" << endl;
    graph.dijkstra(0, path, dist);*/
    
    // Bellman-Ford algorithm
    // Bellman-Ford algorithm
    graph.bellmanFord(0, path, dist);
    cout << "Bellman-Ford Algorithm:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Distance from 0 to " << i << " is " << dist[i] << endl;
    }

    return 0;
};