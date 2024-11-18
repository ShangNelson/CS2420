
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
        vector<vector<int>> getPathRecursive(T source, T target, vector<int> hitNodes, int length); 
        bool vectorContainsNot(vector<T> vect, T target, vector<int> hitNodes);
        bool vectorContains(vector<T> vect, T target);
    public:
        Graph(); //Constructor to create an empty graph.
        void addVertex(T vertex); // Adds a vertex to the graph
        void addEdge(T source, T target); // adds an edge from the source to the target.
        int getVertexPos(T  vertex); // Helper method to allow you to find where the vertex is contained within the list of vertices
        int getNumVertices() { return vertices; }; // Returns the number of vertices contained in the graph
        vector<T> getPath(T source, T target); // returns all vertices in the shortest path from the source to the target (includes source and target) 
        friend ostream& operator << <>(ostream& out, const Graph<T> g); // used for debugging, displays a list of vertices and edges
        bool isEdge(T source, T dest);
};

template <typename T>
Graph<T>::Graph() {
    graph = * new vector<vector<T>>;
    vertices = 0;
}

template <typename T>
void Graph<T>::addVertex(T vertex) {
    vertices++; //Increase the count for vertices
    head.push_back(vertex); // Add the new column/vertex to the heading row
    for (vector<int> otherVector : graph) { // Add another column to all other vectors
        otherVector.push_back(0);
    }
    vector<T> temp = new vector<int>; // Initialize the new row
    for (int i = 0; i < vertices; i++) { // Fill it with all the columns needed
        temp.push_back(0);
    }
    graph.push_back(temp); // Add the new row to the whole matrix
}

template <typename T>
void Graph<T>::addEdge(T source, T dest) {
    int sourcePos = getVertexPos(source); // Get the heading position of the source
    int destPos = getVertexPos(dest); // Get the heading position of the destination
    graph[sourcePos][destPos] = 1; // Set the position to 1 to indicate an edge
    graph[destPos][sourcePos] = 1; // Make it undirectional.
}

template <typename T>
int Graph<T>::getVertexPos(T vertex) {
    for (int i = 0; i < vertices; i++) { // Loop through all the vertices
        if (head[i] == vertex) { // If current vertex is the one we are looking for
            return i; // Return the index
        }
    }
}

template <typename T>
bool Graph<T>::vectorContains(vector<T> vect, T target) {
    for (T item : vect) {
        if (item == target) {
            return true;
        }
    }
    return false;
}

template <typename T>
bool Graph<T>::vectorContainsNot(vector<T> vect, T target, vector<int> hitNodes) {
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i] == target && !vectorContains(hitNodes, i)) {
            return true;
        }
    }
    return false;
}

template <typename T>
vector<T> Graph<T>::getPath(T source, T dest) {
    vector<vector<int>> quickestPath = getPathRecursive(source, dest, new vector<int>, 0);
    return quickestPath[1];
}

/// @brief Recursively loops through all possible paths from a starting node to a finish and finds the shortest. 
/// @param source The starting node for this iteration 
/// @param dest The ending node that we are looking for
/// @param hitNodes All the node that have been hit already in recursion
/// @return A vector of the indecies of vertices in the quickest route from finish to start.
template <typename T>
vector<vector<int>> Graph<T>::getPathRecursive(T source, T dest, vector<int> hitNodes, int length) {
    int sourcePos = getVertexPos(source); // Get the heading position of the source
    hitNodes.push_back(sourcePos); // Add current vertex to the vertices that have been hit (Avoid infinite loops)
    if (!vectorContainsNot(graph[sourcePos], 1, hitNodes)) { // Check if there are any other connecting vertices
        return vector<vector<int>>({{-1}}); // If not (hit dead end) return -1 to indicate a dead end
    }
    if (source == dest) {
        return vector<vector<int>>({{length}, {sourcePos}}); // If we are at the destination node, stop and return the length and the end of the path
    }
    vector<vector<vector<int>>> possiblePaths = * new vector<vector<vector<int>>>;
    for (int i = 0; i < graph[sourcePos].size(); i++) { // Loop through all the connecting vertices
        if (graph[sourcePos][i] > 0) { // If there is a connecting vertex
            possiblePaths.push_back(getPathRecursive(head[i], dest, hitNodes, length+graph[sourcePos][i])); // Recurse through that node and add each option to possiblePaths.
        }
    }
    int minimumPath = numeric_limits<int>::max(); // Set the minimum path starting at infinity
    vector<vector<int>> quickestPath = * new vector<vector<int>>; // Intialize a quickest path
    for (vector<vector<int>> path : possiblePaths) { // Loop through all the possible paths
        if (path[0][0] < minimumPath && path[0][0] > 0) { // If the current path is shorter than the current minimum
            minimumPath = path[0][0]; // Set the current minimum to the current length
            quickestPath = path; // Set the quickest path to the current path
        }
    }
    return quickestPath; // Return the quickest current route
}

template <typename T>
bool Graph<T>::isEdge(T source, T dest) {
    int sourcePos = getVertexPos(source); // Get the heading position of the source
    int destPos = getVertexPos(dest); // Get the heading position of the destination
    if (graph[sourcePos][destPos] > 0) {
        return true;
    }
    return false;
}

template <typename T>
ostream& operator<<(ostream& out, Graph<T>& g) {
    out << "Vertices: ";
    for (T vertex : g.head) {
        out << vertex << ", ";
    }
    out << endl;
    return out;
}