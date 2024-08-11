#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2;

    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 + g2;

    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}
    };

    CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph subtraction") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2;

    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    ariel::Graph g3 = g1 - g2;

    vector<vector<int>> expectedGraph = {
        {0, 2, -1},
        {2, 0, 1},
        {-1, 1, 0}
    };

    CHECK(g3.printGraph() == "[0, 2, -1]\n[2, 0, 1]\n[-1, 1, 0]");
}

TEST_CASE("Test scalar multiplication") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 * 2;

    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}
    };

    CHECK(g2.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
}

TEST_CASE("Test graph multiplication") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2;

    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}
    };
    g2.loadGraph(weightedGraph);

    ariel::Graph g4 = g1 * g2;

    vector<vector<int>> expectedGraph = {
        {1, 0, 2},
        {1, 3, 1},
        {1, 0, 2}
    };

    CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
}

TEST_CASE("Test graph equality") {
    ariel::Graph g1;

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;

    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g2.loadGraph(graph2);

    CHECK(g1 == g2);
}

TEST_CASE("Test graph inequality") {
    ariel::Graph g1;

    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph1);

    ariel::Graph g2;

    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g2.loadGraph(graph2);

    CHECK(g1 != g2);
}

TEST_CASE("Test subgraph detection") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2;

    vector<vector<int>> largerGraph = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    g2.loadGraph(largerGraph);

    CHECK(g1.isSubGraph(g2) == true);

    ariel::Graph g3;

    vector<vector<int>> nonSubGraph = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}
    };
    g3.loadGraph(nonSubGraph);

    CHECK(g1.isSubGraph(g3) == false);

    ariel::Graph g4;

    vector<vector<int>> smallerGraph = {
        {0, 1},
        {1, 0}
    };
    g4.loadGraph(smallerGraph);

    CHECK(g4.isSubGraph(g1) == true);
}

TEST_CASE("Test graph directedness") {
    ariel::Graph g1;

    vector<vector<int>> undirectedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(undirectedGraph);

    CHECK(g1.getIsDirected() == false);

    ariel::Graph g2;

    vector<vector<int>> directedGraph = {
        {0, 1, 0},
        {0, 0, 1},
        {0, 0, 0}
    };
    g2.loadGraph(directedGraph);

    CHECK(g2.getIsDirected() == true);
}

TEST_CASE("Test graph weight detection") {
    ariel::Graph g1;

    vector<vector<int>> unweightedGraph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    g1.loadGraph(unweightedGraph);

    CHECK(g1.getIsWeighted() == false);

    ariel::Graph g2;

    vector<vector<int>> weightedGraph = {
        {0, 2, 0},
        {2, 0, 3},
        {0, 3, 0}
    };
    g2.loadGraph(weightedGraph);

    CHECK(g2.getIsWeighted() == true);
}

TEST_CASE("Test scalar multiplication with zero") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {1, 2, 3},
        {2, 1, 4},
        {3, 4, 1}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 * 0;

    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]");
}

TEST_CASE("Test graph multiplication with identity matrix") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    g1.loadGraph(graph);

    ariel::Graph identity;

    vector<vector<int>> identityMatrix = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };
    identity.loadGraph(identityMatrix);

    ariel::Graph g2 = g1 * identity;

    CHECK(g1.printGraph() == g2.printGraph()); // Result of multiplication with identity matrix should be the same matrix
}

TEST_CASE("Test graph addition with zero matrix") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    g1.loadGraph(graph);

    ariel::Graph zeroMatrix;

    vector<vector<int>> zero = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    zeroMatrix.loadGraph(zero);

    ariel::Graph g2 = g1 + zeroMatrix;

    CHECK(g1.printGraph() == g2.printGraph()); // Adding zero matrix should return the original matrix
}

TEST_CASE("Test graph subtraction to zero matrix") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 - g1;

    CHECK(g2.printGraph() == "[0, 0, 0]\n[0, 0, 0]\n[0, 0, 0]"); // Subtracting the graph from itself should result in a zero matrix
}

TEST_CASE("Test scalar division by one") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 / 1;

    CHECK(g1.printGraph() == g2.printGraph()); // Dividing by 1 should return the original matrix
}

TEST_CASE("Test subgraph detection with all-zero subgraph") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2;

    vector<vector<int>> fullGraph = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    g2.loadGraph(fullGraph);

    CHECK(g1.isSubGraph(g2) == true); // An all-zero graph should be a subgraph of any graph
}

TEST_CASE("Test scalar division by non-zero scalar") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1 / 2;

    vector<vector<int>> expectedGraph = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    CHECK(g2.printGraph() == "[1, 2, 3]\n[4, 5, 6]\n[7, 8, 9]");
}

TEST_CASE("Test scalar division by zero throws exception") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}
    };
    g1.loadGraph(graph);

    CHECK_THROWS_AS(g1 / 0, std::invalid_argument);
    CHECK_THROWS_AS(g1 /= 0, std::invalid_argument);
}

TEST_CASE("Test increment (++) operator") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };
    g1.loadGraph(graph);

    ++g1;

    vector<vector<int>> expectedGraph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}
    };

    CHECK(g1.printGraph() == "[0, 2, 3]\n[2, 0, 4]\n[3, 4, 0]");
}

TEST_CASE("Test decrement (--) operator") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}
    };
    g1.loadGraph(graph);

    --g1;

    vector<vector<int>> expectedGraph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };

    CHECK(g1.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
}

TEST_CASE("Test post-increment (operator++)") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1++;

    vector<vector<int>> expectedGraph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}
    };

    CHECK(g1.printGraph() == "[0, 2, 3]\n[2, 0, 4]\n[3, 4, 0]");
    CHECK(g2.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
}

TEST_CASE("Test post-decrement (operator--)") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2 = g1--;

    vector<vector<int>> expectedGraph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };

    CHECK(g1.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
    CHECK(g2.printGraph() == "[0, 2, 3]\n[2, 0, 4]\n[3, 4, 0]");
}

TEST_CASE("Test compound assignment (operator+= and operator-=)") {
    ariel::Graph g1;

    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };
    g1.loadGraph(graph);

    ariel::Graph g2;

    vector<vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g2.loadGraph(graph2);

    g1 += g2;

    vector<vector<int>> expectedAddition = {
        {0, 2, 3},
        {2, 0, 4},
        {3, 4, 0}
    };

    CHECK(g1.printGraph() == "[0, 2, 3]\n[2, 0, 4]\n[3, 4, 0]");

    g1 -= g2;

    vector<vector<int>> expectedSubtraction = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0}
    };

    CHECK(g1.printGraph() == "[0, 1, 2]\n[1, 0, 3]\n[2, 3, 0]");
}
