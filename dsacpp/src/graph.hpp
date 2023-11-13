#ifndef DSACPP_GRAPH_H
#define DSACPP_GRAPH_H

#include<string>
#include<vector>
#include<memory>

// -*-
namespace dsacpp{
// -
class Edge;
class Graph;
// -

// --
class Node : public std::enable_shared_from_this<Node>{
public:
    Node(std::string name);
    virtual ~Node(){}

    std::shared_ptr<Edge> create_edge(uint32_t cost, std::shared_ptr<Node> target);
    void init_path_finding(bool startNode);

    std::shared_ptr<Node> get_ptr(){
        return shared_from_this();
    }

    static std::shared_ptr<Node> create(std::string name){
        return std::shared_ptr<Node>(new Node(name));
    }

private:
    friend class Graph;

private:
    std::string m_name;
    std::vector<std::shared_ptr<Edge>> m_edgelist;
    void relax();
    uint32_t m_bestcost;
    std::shared_ptr<Node> m_from;
    bool m_visited;
};

// -*-
class Edge{
public:
    Edge(uint32_t cost, std::shared_ptr<Node> target)
    : m_cost(cost), m_target(target){}

    virtual ~Edge(){}
    
    std::shared_ptr<Node> target() const {
        return this->m_target;
    }

    uint32_t cost() const{
        return this->m_cost;
    }

private:
    uint32_t m_cost;
    std::shared_ptr<Node> m_target;
};

// -
class Graph{
public:
    Graph(){}
    virtual ~Graph(){}

    std::shared_ptr<Node> create_node(std::string name);
    void find_path(std::shared_ptr<Node> from, std::shared_ptr<Node> to);

private:
    std::vector<std::shared_ptr<Node>> m_nodelist;
    
    bool init_path_finding(std::shared_ptr<Node> from);
    std::shared_ptr<Node> find_cheapest_node();
};

// -
}
// -*-

#endif