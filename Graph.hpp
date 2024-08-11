#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <iostream>
#include <stdexcept>

namespace ariel {

    class Graph {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        size_t vertices;
        bool isDirected;
        bool isWeighted;
        size_t numberOfEdges;

        bool isSymmetric(const std::vector<std::vector<int>> &matrix) const;

    public:
        // Constructor
        Graph() : vertices(0), isDirected(false), isWeighted(false), numberOfEdges(0) {}

        // Load graph from adjacency matrix
        void loadGraph(const std::vector<std::vector<int>> &matrix);

        // Print the graph as a string
        std::string printGraph() const;

        // Getters
        bool getIsDirected() const;
        bool getIsWeighted() const;
        size_t getNumberOfVertices() const;
        std::vector<int> getNeighbors(int vertex) const;
        int getEdgeWeight(int from, int to) const;

        // Arithmetic operators
        Graph operator+(const Graph &other) const;
        Graph &operator+=(const Graph &other);
        Graph operator-(const Graph &other) const;
        Graph &operator-=(const Graph &other);
        Graph operator*(int scalar) const;
        Graph &operator*=(int scalar);
        Graph operator/(int scalar) const;
        Graph &operator/=(int scalar);
        Graph operator*(const Graph &other) const;

        // Unary operators
        Graph operator+() const;  // Unary plus
        Graph operator-() const;  // Unary minus

        // Comparison operators
        bool operator==(const Graph &other) const;
        bool operator!=(const Graph &other) const;
        bool operator<(const Graph &other) const;
        bool operator<=(const Graph &other) const;
        bool operator>(const Graph &other) const;
        bool operator>=(const Graph &other) const;

        // Increment/Decrement operators
        Graph &operator++();     // Prefix increment
        Graph operator++(int);   // Postfix increment
        Graph &operator--();     // Prefix decrement
        Graph operator--(int);   // Postfix decrement

        // Subgraph check
        bool isSubGraph(const Graph &other) const;

        // Output operator
        friend std::ostream &operator<<(std::ostream &out, const Graph &g);
    };

}

#endif // GRAPH_HPP