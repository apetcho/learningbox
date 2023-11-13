#include "graph.hpp"
#include<iostream>

// -*--------------------------*-
// -*- M A I N   D R I V E R  -*-
// -*--------------------------*-
int main(void){
    auto graph = new dsacpp::Graph();
    auto a = graph->create_node("A");
    auto b = graph->create_node("B");
    auto c = graph->create_node("C");
    auto d = graph->create_node("D");
    auto e = graph->create_node("E");

    // -
    auto ab = a->create_edge(1, b);
    auto ba = b->create_edge(5, a);
    auto ac = a->create_edge(2, c);
    auto ca = c->create_edge(2, a);
    auto cb = c->create_edge(1, b);
    auto bc = b->create_edge(3, c);
    auto cd = c->create_edge(2, d);
    auto dc = d->create_edge(2, c);
    auto ad = a->create_edge(4, d);

    std::cout << std::endl;
    std::cout << "-*------------------------------------------------*-\n";
    std::cout << "--- Example of Dijkstra's Algorithm to calculate ---\n";
    std::cout << "--- paths between connected nodes                ---\n";
    std::cout << "-*------------------------------------------------*-\n";
    graph->find_path(a, d);
    graph->find_path(d, a);
    graph->find_path(a, e);
    graph->find_path(a, a);

    return 0;
}