#include <iostream>
#include <vector>
#include <array>

template <class T>
class Graph {
public:
    using WeightType = T;
    using Index = std::size_t;

    // Constructor 
    Graph() = delete;
    Graph(Index size) : adj_list{size} {}

    // This type is not copyable or movable
    Graph(const Graph&) = delete;
    Graph(Graph&&) = delete;
    Graph& operator=(const Graph&) = delete;

    void add_edge(Index src, Index dest, WeightType weight) {
        adj_list.at(src).push_back({ dest, weight });
    }

    void print_graph() {
        for (Index i = 0; i < adj_list.size(); i++) {
            std::cout << "Vertex " << i << ":" << std::endl;
            for (const auto& edge : adj_list.at(i)) {
                std::cout << "\t Vertex " << edge.first << " with weight " << edge.second << std::endl;
            }
        }
    }

private:
    std::vector<std::vector<std::pair<Index, WeightType>>> adj_list;
};






