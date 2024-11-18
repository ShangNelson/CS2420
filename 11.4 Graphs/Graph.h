#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

template <typename T>
class Graph;

template <typename T>
ostream& operator <<(ostream& out, Graph<T> g); // used for debugging, displays a list of vertices and edges

template <typename T>
class Graph {
    private:
        vector<T> head;
        vector<vector<int>> graph;
        int vertices;
        vector<int> getPathRecursive(T& source, T& target, vector<int>& hitNodes, int length); 
        int countVertices(T source);
    public:
        Graph(); //Constructor to create an empty graph.
        ~Graph();
        void printGraph();
        void addVertex(T vertex); // Adds a vertex to the graph
        void addEdge(T source, T target); // adds an edge from the source to the target.
        bool vectorContains(vector<int> vect, int target) const;
        int getVertexPos(T  vertex); // Helper method to allow you to find where the vertex is contained within the list of vertices
        int getNumVertices() { return vertices; }; // Returns the number of vertices contained in the graph
        vector<T> getPath(T source, T target); // returns all vertices in the shortest path from the source to the target (includes source and target) 
        friend ostream& operator << <>(ostream& out, const Graph<T> g); // used for debugging, displays a list of vertices and edges
        bool isEdge(T source, T dest);
};

template <typename T>
Graph<T>::~Graph() {
    cout << "Finished using graph" << endl;
}

template <typename T>
Graph<T>::Graph() : vertices(0) {}

template <typename T>
void Graph<T>::addVertex(T vertex) {
    vertices++; //Increase the count for vertices
    head.push_back(vertex); // Add the new column/vertex to the heading row
    for (vector<int>& otherVector : graph) { // Add another column to all other vectors
        otherVector.push_back(0);
    }
    graph.emplace_back(vertices, 0); // Add the new row to the whole matrix
    /*for (int i = 0; i < vertices; i++) {
        cout << head[i];
    }
    cout << endl;*/
}

template <typename T>
void Graph<T>::addEdge(T source, T dest) {
    int sourcePos = getVertexPos(source); // Get the heading position of the source
    int destPos = getVertexPos(dest); // Get the heading position of the destination
    graph[sourcePos][destPos] = 1; // Set the position to 1 to indicate an edge
}

template <typename T>
int Graph<T>::getVertexPos(T vertex) {
    for (int i = 0; i < vertices; i++) { // Loop through all the vertices
        if (head[i] == vertex) { // If current vertex is the one we are looking for
            return i; // Return the index
        }
    }
    return -1; // Vertex doesn't exist/not found
}

template <typename T>
bool Graph<T>::vectorContains(vector<int> vect, int target) const {
    for (int item : vect) {
        if (item == target) {
            return true;
        }
    }
    return false;
}

template <typename T>
vector<T> Graph<T>::getPath(T source, T dest) {
    vector<int> hitNodes;
    vector<int> quickestPath = getPathRecursive(source, dest, hitNodes, 0); // Get the list of the quickest path
    vector<T> actualPath;
    for (int i = quickestPath.size()-1; i >= 0; i--) {
        actualPath.push_back(head[quickestPath[i]]);
    }
    return actualPath;
}

/// @brief Recursively loops through all possible paths from a starting node to a finish and finds the shortest. 
/// @param source The starting node for this iteration 
/// @param dest The ending node that we are looking for
/// @param hitNodes All the node that have been hit already in recursion
/// @param length The amount of vertices in that path
/// @return A vector of the indecies of vertices in the quickest route from finish to start.
template <typename T>
vector<int> Graph<T>::getPathRecursive(T& source, T& dest, vector<int>& hitNodes, int length) {
    int sourcePos = getVertexPos(source); // Get the heading position of the source
    int destPos = getVertexPos(dest);
    if (vectorContains(hitNodes, sourcePos)) {
        return {-1};
    }
    if (sourcePos == destPos) {
        return {sourcePos}; // If we are at the destination node, stop and return the end of the path, or the dest
    }
    hitNodes.push_back(sourcePos); // Add current vertex to the vertices that have been hit (Avoid infinite loops)
    
    vector<vector<int>> possiblePaths; // Initialize a new vector that will hold a list of the possible paths
    
    for (int i = 0; i < vertices; i++) { // Loop through all the connecting vertices and edges
        if (graph[sourcePos][i] > 0) { // If there is a connecting vertex and it has not been visited
            // Recurse through that node and add each option to possiblePaths.
            vector<int> currPath = getPathRecursive(head[i], dest, hitNodes, length + graph[sourcePos][i]); // Get a recursed path down to the destination of leaf node and return the path back to that node
            if (currPath[0] == -1) { // If it lead to a leaf node
                continue;
            }
            currPath.push_back(sourcePos); // Add the current node to the path
            possiblePaths.push_back(currPath); // Pass that path into the list of all paths from that point
        }
    }
    //cout << "# of Possible Paths: " << possiblePaths.size() << endl;
    int minimumPath = std::numeric_limits<int>::max(); // Set the minimum path starting at infinity
    vector<int> quickestPath = {-1};
    for (const vector<int>& path : possiblePaths) { // Loop through all the possible paths
        if (path.size() < minimumPath) { // If the current path is shorter than the current minimum
            minimumPath = path.size(); // Set the current minimum to the current length
            quickestPath = path; // Set the quickest path to the current path
        }
    }
    return quickestPath; // Return the quickest current route
}

template <typename T>
bool Graph<T>::isEdge(T source, T dest) {
    int sourcePos = getVertexPos(source); // Get the heading position of the source
    int destPos = getVertexPos(dest); // Get the heading position of the destination
    if (sourcePos == -1 || destPos == -1) {
        return false;    
    }
    return graph[sourcePos][destPos] > 0;
}

template <typename T> 
void Graph<T>::printGraph() {
    cout << "Vertices: ";
    for (T vertex : head) {
        cout << vertex << " ";
    }
    cout << endl << endl << "Graph: " << endl << "   ";
    for (T val : head) {
        cout << val << " ";
    }
    cout << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << head[i] << ": ";
        for (int j = 0; j < graph[i].size(); j++) {
            if (j != graph[i].size()-1) {
                cout << graph[i][j] << " ";
            } else {
                cout << graph[i][j];
            }
        }
        cout << endl;
    }
}

template <typename T>
ostream& operator<<(ostream& out, Graph<T>& g) {
    out << "Vertices: ";
    for (T vertex : g.head) {
        out << vertex << " ";
    }
    out << endl << endl << "Graph: " << endl;
    for (int i = 0; i < g.graph.size(); i++) {
        out << head[i] << ": ";
        for (int j = 0; j < g.graph[i].size(); j++) {
            if (j != g.graph[i].size()-1) {
                out << g.graph[i][j] << " ";
            } else {
                out << g.graph[i][j];
            }
        }
        out << endl;
    }
    return out;
}