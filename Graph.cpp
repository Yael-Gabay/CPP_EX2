#include "Graph.hpp"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <numeric>

namespace ariel {

    bool Graph::isSymmetric(const std::vector<std::vector<int>> &matrix) const {
        for (size_t i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[i].size(); ++j) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }

    void Graph::loadGraph(const std::vector<std::vector<int>> &matrix) {
        if (matrix.empty() || matrix.size() != matrix[0].size()) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }

        this->isDirected = !isSymmetric(matrix);
        this->isWeighted = false;
        for (const auto &row : matrix) {
            for (int weight : row) {
                if (weight != 0 && weight != 1) {
                    this->isWeighted = true;
                    break;
                }
            }
            if (this->isWeighted) {
                break;
            }
        }

        this->adjacencyMatrix = matrix;
        this->vertices = matrix.size();
        this->numberOfEdges = 0;

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                if (this->adjacencyMatrix[i][j] != 0) {
                    this->numberOfEdges++;
                }
            }
        }

        if (!this->isDirected) {
            this->numberOfEdges /= 2;
        }
    }

    std::string Graph::printGraph() const {
        std::ostringstream oss;
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            oss << "[";
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                oss << adjacencyMatrix[i][j];
                if (j < adjacencyMatrix[i].size() - 1) {
                    oss << ", ";
                }
            }
            oss << "]";
            if (i < adjacencyMatrix.size() - 1) {
                oss << "\n";
            }
        }
        return oss.str();
    }

    bool Graph::getIsDirected() const {
        return this->isDirected;
    }

    bool Graph::getIsWeighted() const {
        return this->isWeighted;
    }

    size_t Graph::getNumberOfVertices() const {
        return this->vertices;
    }

    std::vector<int> Graph::getNeighbors(int vertex) const {
        std::vector<int> neighbors;
        if (vertex >= 0 && static_cast<size_t>(vertex) < this->vertices) {
            for (size_t i = 0; i < this->adjacencyMatrix[static_cast<size_t>(vertex)].size(); ++i) {
                if (this->adjacencyMatrix[static_cast<size_t>(vertex)][i] != 0) {
                    neighbors.push_back(static_cast<int>(i));
                }
            }
        }
        return neighbors;
    }

    int Graph::getEdgeWeight(int from, int to) const {
        if (from >= 0 && static_cast<size_t>(from) < this->vertices &&
            to >= 0 && static_cast<size_t>(to) < this->vertices) {
            return this->adjacencyMatrix[static_cast<size_t>(from)][static_cast<size_t>(to)];
        }
        return -1; // Invalid edge
    }

    // Arithmetic operators
    Graph Graph::operator+(const Graph &other) const {
        if (this->vertices != other.vertices) {
            throw std::invalid_argument("Graphs must have the same size.");
        }

        std::vector<std::vector<int>> resultMatrix(this->vertices, std::vector<int>(this->vertices, 0));

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                resultMatrix[i][j] = this->adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
            }
        }

        Graph result;
        result.loadGraph(resultMatrix);
        return result;
    }

    Graph &Graph::operator+=(const Graph &other) {
        *this = *this + other;
        return *this;
    }

    Graph Graph::operator-(const Graph &other) const {
        if (this->vertices != other.vertices) {
            throw std::invalid_argument("Graphs must have the same size.");
        }

        std::vector<std::vector<int>> resultMatrix(this->vertices, std::vector<int>(this->vertices, 0));

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                resultMatrix[i][j] = this->adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
            }
        }

        Graph result;
        result.loadGraph(resultMatrix);
        return result;
    }

    Graph &Graph::operator-=(const Graph &other) {
        *this = *this - other;
        return *this;
    }

    Graph Graph::operator*(int scalar) const {
        std::vector<std::vector<int>> resultMatrix(this->vertices, std::vector<int>(this->vertices, 0));

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                resultMatrix[i][j] = this->adjacencyMatrix[i][j] * scalar;
            }
        }

        Graph result;
        result.loadGraph(resultMatrix);
        return result;
    }

    Graph &Graph::operator*=(int scalar) {
        *this = *this * scalar;
        return *this;
    }

    Graph Graph::operator/(int scalar) const {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }

        std::vector<std::vector<int>> resultMatrix(this->vertices, std::vector<int>(this->vertices, 0));

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                resultMatrix[i][j] = this->adjacencyMatrix[i][j] / scalar;
            }
        }

        Graph result;
        result.loadGraph(resultMatrix);
        return result;
    }

    Graph &Graph::operator/=(int scalar) {
        if (scalar == 0) {
            throw std::invalid_argument("Division by zero is not allowed.");
        }

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                this->adjacencyMatrix[i][j] /= scalar;
            }
        }

        return *this;
    }

    Graph Graph::operator*(const Graph &other) const {
        if (this->vertices != other.vertices) {
            throw std::invalid_argument("Graphs must have the same size.");
        }

        std::vector<std::vector<int>> resultMatrix(this->vertices, std::vector<int>(this->vertices, 0));

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                for (size_t k = 0; k < this->vertices; ++k) {
                    resultMatrix[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                }
            }
        }

        Graph result;
        result.loadGraph(resultMatrix);
        return result;
    }

    Graph Graph::operator+() const {
        return *this;
    }

    Graph Graph::operator-() const {
        return *this * -1;
    }

    // Comparison operators
    bool Graph::operator==(const Graph &other) const {
        if (this->vertices != other.vertices) return false;
        return this->adjacencyMatrix == other.adjacencyMatrix;
    }

    bool Graph::operator!=(const Graph &other) const {
        return !(*this == other);
    }

    bool Graph::operator<(const Graph &other) const {
        if (this->vertices < other.vertices) return true;
        if (this->vertices > other.vertices) return false;
        return this->numberOfEdges < other.numberOfEdges;
    }

    bool Graph::operator<=(const Graph &other) const {
        return *this < other || *this == other;
    }

    bool Graph::operator>(const Graph &other) const {
        return !(*this <= other);
    }

    bool Graph::operator>=(const Graph &other) const {
        return !(*this < other);
    }

    // Increment/Decrement operators
    Graph &Graph::operator++() {  // Prefix increment
        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                if (this->adjacencyMatrix[i][j] != 0) {
                    this->adjacencyMatrix[i][j]++;
                }
            }
        }
        return *this;
    }

    Graph Graph::operator++(int) {  // Postfix increment
        Graph temp = *this;
        ++(*this);
        return temp;
    }

    Graph &Graph::operator--() {  // Prefix decrement
        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                if (this->adjacencyMatrix[i][j] != 0) {
                    this->adjacencyMatrix[i][j]--;
                }
            }
        }
        return *this;
    }

    Graph Graph::operator--(int) {  // Postfix decrement
        Graph temp = *this;
        --(*this);
        return temp;
    }

    // Subgraph check
    bool Graph::isSubGraph(const Graph &other) const {
        if (this->vertices > other.vertices) return false;

        for (size_t i = 0; i < this->vertices; ++i) {
            for (size_t j = 0; j < this->vertices; ++j) {
                if (this->adjacencyMatrix[i][j] > other.adjacencyMatrix[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    // Output operator
    std::ostream &operator<<(std::ostream &out, const Graph &g) {
        out << g.printGraph() << "\n"; // הוספת ירידת שורה בסיום
        return out;
    }

}
