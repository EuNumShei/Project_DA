#include "Graph.h"
#include "Station.h"

// Time complexity: O(n)
template<>
Vertex<Station> *Graph<Station>::findVertexwithCode(const string &in) const {
    for (auto v : vertexSet)
        if (v->getInfo().get_code() == in)
            return v;
    return NULL;
}
// Time complexity: O(n)
template<>
Vertex<Station> * Graph<Station>::findVertexWithID(const int &in) const {
    for (auto v : vertexSet)
        if (v->getInfo().get_id() == in)
            return v;
    return NULL;
}
