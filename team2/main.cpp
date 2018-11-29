/* Shortest Path Algorithm Testing in C++11
 * Group 2: Kevin Doak, Brian Kungl, Brian Phillips, and Matthew Grossman
 * Code is modified from GeeksforGeeks Source Code.
 * This code will allow the user to pick from running either:
 * 1. Dijkstra's Algorithm
 * 2. Bellman-Ford's Algorithm
 * 3. Floyd-Warshall's Algorithm
 * The time reported is ONLY the time taken to run the algorithm through the trials.
 * The time does not include graph creation.
 * 
 * The graphs used by these algorithms are randomized and weighted/unweighted to
 * fit the algorithm.
 * 
 * Multiple constants can be changed to change the output of the code such as:
 * V - The # of vertices that each graph will have.
 * TRIALS - The # of times a new random graph will be created for an algorithm to run.
 * SHOW - 0 = OFF, 1 = ON, Toggles solution printing for each graph/algorithm trial
 *
 */

#include <cstdlib>
#include <stdio.h> 
#include <limits.h>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <bits/stdc++.h> 
using namespace std;
using namespace std::chrono;

#define V 10 // Vertices used for Graph Making, changeable!
#define TRIALS 1000000 // Amount of trials to be completed by an algorithm, changable!
#define INF 99999 // Floyd-Warshall's constant, don't change!
#define SHOW 0 // Shows the computed answers of algortithm, changable!

// Bellman-Ford: weighted edge in graph 
struct Edge {
    int src, dest, weight;
};

// Bellman-Ford: weighted graph 
struct Graph {
    // Ver-> Number of vertices, E-> Number of edges 
    int Ver, E;

    // graph is represented as an array of edges. 
    struct Edge* edge;
};

// Bellman-Ford: Creates a graph with V vertices and E edges 
struct Graph* createGraph(int Ver, int E) {
    struct Graph* graph = new Graph;
    graph->Ver = Ver;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

// Dijkstra Helper Function to find the vertex with minimum distance value.
int DminDistance(int dist[], bool sptSet[]) {
    // Initialize min value 
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v], min_index = v;
        }
    }
    return min_index;
}

// Dijkstra Helper Function to print solution 
int DprintSolution(int dist[], int n) {
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t%d\n", i, dist[i]);
    }
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // The output array
    bool sptSet[V]; // True if vertex is included in shortest path tree/shortest distance is finalized 
    // Initialize all distances as INFINITE and stpSet[] as false 
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX, sptSet[i] = false;
    }
    dist[src] = 0;
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = DminDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                    && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    if(SHOW == 1) DprintSolution(dist, V);
}

// Bellman-Ford Helper Function used to print solution 
void BprintSolution(int dist[], int n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i) {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}

// Bellman-Ford's Algorithm
void BellmanFord(struct Graph* graph, int src) {
    int Ver = graph->Ver;
    int E = graph->E;
    int dist[Ver];

    // Step 1: Initialize distances from src to all other vertices as INFINITE 
    for (int i = 0; i < Ver; i++){
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    // Step 2: Relax all edges |Ver| - 1 times
    for (int i = 1; i <= Ver - 1; i++){
        for (int j = 0; j < E; j++){
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int weight = graph->edge[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
            }
        }
    }

    // Step 3: check for negative-weight cycles 
    for (int i = 0; i < E; i++) {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int weight = graph->edge[i].weight;
        /*
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
            printf("Graph contains negative weight cycle");
        }
        */
    }
    if (SHOW == 1) BprintSolution(dist, Ver);
}

// Floyd-Warshall Helper Function to print solution
void FprintSolution(int dist[][V]) {
    cout << "The following matrix shows the shortest distance between every pair of vertices \n" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) cout << dist[i][j] << "\t";
            else cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Floyd-Warshall's Algorithm
void floydWarshall(int graph[][V]) {
    int dist[V][V], i, j, k;
    // Initialize the solution matrix same as input graph matrix.
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }
    // Add all vertices one by one to the set of intermediate vertices. 
    for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one 
        for (i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source 
            for (j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    if (SHOW == 1) FprintSolution(dist);
}

int main(int argc, char** argv) {
    int choice; // Algorithm choice, either a 1, 2, or 3 for respective algorithms
    cout << "Which algorithm would you like to run?\n" << endl;
    cout << "1 for Dijkstra's.\n2 for Bellman-Ford's.\n3 for Floyd-Warshall's." << endl;
    cin >> choice;
    cout << "Testing on " << V << "-vertex graphs for " << TRIALS << " trials." << endl;
    if (choice == 1) { // Dijkstra's Algorithm
        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - high_resolution_clock::now());
        for (int t = 0; t < TRIALS; t++){
            // Creating random unweighted Graph and running
            srand (time(NULL));
            int graph[V][V];
            int k = 0;
            for (int i = 0; i < V; i++){
                for (int j = k; j < V; j++){
                    graph[i][j] = (rand() % 20);
                    if (graph[i][j] > 10)graph[i][j] = 0;
                    if (i == j)graph[i][j] = 0;
                }
                k++;
            }
            k = 0;
            for (int i = 0; i < V; i++){
                for (int j = 0; j < k; j++){
                    graph[i][j] = graph[j][i];
                }
                k++;
            }  /*FOR PRINTING GRAPH
            for (int i = 0; i < V; i++){
                for (int j = 0; j < V; j++){
                    cout << graph[i][j] << "\t";
                }
                cout << endl;
            }*/
            // Timing the execution of Dijkstra's
            auto start = high_resolution_clock::now(); 
            dijkstra(graph, 0);
            auto stop = high_resolution_clock::now();
            duration += duration_cast<milliseconds>(stop - start);
        }
        cout << "Finished Dijkstra's Algorithm!\n\nTotal Time: " << duration.count() << " ms" << endl;
    } else if (choice == 2) {// Bellman-Ford's Algorithm
        // Creating random weighted Graph and running
        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - high_resolution_clock::now());
        for (int t = 0; t < TRIALS; t++){
            srand (time(NULL));
            int edges = rand() % ((V*V)-(2*V)+1); //0
            // Get rid of the rand() and replace with a specific number in the rand() range
            // to control how many extra edges the Bellman-Ford Algorithm has to deal with.
            // Since time complexity is O(V*E), no extra edges would result in fastest time.
            // (V*V)-(2*V) would be the maximum amount of edges allowed and longest time.
            int counter;
            int edgecounter = V;
            struct Graph* graph = createGraph(V, (edges + V));
            
            for (int i = 0; i < V; i++){
                graph->edge[i].src = i;
                graph->edge[i].dest = (i+1)% V;
                int number = (rand() % 15);
                if (number > 10) number -= 15;
                if (number == 0) number = 1;
                graph->edge[i].weight = number;
                if (edges >= V) counter = V-2;
                else counter = edges;
                for (int j = 0; j < counter % V; j++){
                    graph->edge[edgecounter].src = i;
                    graph->edge[edgecounter].dest = (i+2+j)% V;
                    int number = (rand() % 12);
                    if (number > 10) number -= 12;
                    if (number == 0) number = 1;
                    graph->edge[edgecounter].weight = number;
                    edges--;
                    edgecounter++;
                }
            }
            auto start = high_resolution_clock::now();
            BellmanFord(graph, 0);
            auto stop = high_resolution_clock::now();
            duration += duration_cast<milliseconds>(stop - start);
        }
        cout << "Finished Bellman-Ford's Algorithm!\n\nTotal Time: " << duration.count() << " ms" << endl;
    } else if (choice == 3) {// Floyd-Warshall's Algorithm
        auto duration = duration_cast<milliseconds>(high_resolution_clock::now() - high_resolution_clock::now());
        for (int t = 0; t < TRIALS; t++){
            srand (time(NULL));
            int graph[V][V];
            for (int i = 0; i < V; i++){
                for (int j = 0; j < V; j++){
                    graph[i][j] = (rand() % 20);
                    if (graph[i][j] > 10 || graph[i][j] == 0) graph[i][j] = INF;
                    if (i == j)graph[i][j] = 0;
                }
            } /* FOR PRINTING GRAPH
            for (int i = 0; i < V; i++){
                for (int j = 0; j < V; j++){
                    if (graph[i][j] == INF)cout << "INF\t";
                    else cout << graph[i][j] << "\t";
                }
                cout << endl;
            }*/
            auto start = high_resolution_clock::now();
            floydWarshall(graph);
            auto stop = high_resolution_clock::now();
            duration += duration_cast<milliseconds>(stop - start);
        }
        cout << "Finished Floyd-Warshall's Algorithm!\n\nTotal Time: " << duration.count() << " ms" << endl;
    }
    return 0;
} 