#include "graph.hpp"
#include<iostream>

// -*-
namespace dsacpp{
// -
Node::Node(std::string name): m_name(name){}

// -*-
std::shared_ptr<Edge> Node::create_edge(uint32_t cost, std::shared_ptr<Node> target){
    std::shared_ptr<Edge> edge = std::make_shared<Edge>(cost, target);
    this->m_edgelist.push_back(edge);
    return edge;
}

// -*-
void Node::init_path_finding(bool startNode){
    if(startNode){
        this->m_bestcost = 0;
    }else{
        this->m_bestcost = 999999;
    }
    this->m_from = nullptr;
    this->m_visited = false;
}

// -
void Node::relax(){
    for(auto iter=m_edgelist.begin(); iter != m_edgelist.end(); ++iter){
        auto edge = *iter;
        if(edge != nullptr){
            std::shared_ptr<Node> target = edge->target();
            if(target->m_bestcost > m_bestcost + edge->cost()){
                target->m_bestcost = m_bestcost + edge->cost();
                target->m_from = this->get_ptr();
            }
        }
    }
    m_visited = true;
}

// -
std::shared_ptr<Node> Graph::create_node(std::string name){
    auto node = Node::create(name);
    m_nodelist.push_back(node);
    return node;
}

// -
std::shared_ptr<Node> Graph::find_cheapest_node(){
    uint32_t best = 99999999;
    std::shared_ptr<Node> node = nullptr;
    for(auto iter = m_nodelist.begin(); iter != m_nodelist.end(); ++iter){
        std::shared_ptr<Node> self = *iter;
        if(self != nullptr){
            if(self->m_visited == false && self->m_bestcost < best){
                node = self;
                best = self->m_bestcost;
            }
        }
    }

    return node;
}

// -
void Graph::find_path(std::shared_ptr<Node> from, std::shared_ptr<Node> to){
    if(this->init_path_finding(from)){
        auto node = this->find_cheapest_node();
        while(node != nullptr){
            node->relax();
            node = this->find_cheapest_node();
        }

        std::cout << "\n--------------------------\n";
        std::cout << "Calculated path from " << from->m_name;
        std::cout << " to " << to->m_name << "\n";

        // -
        auto path = to;
        while(path != nullptr){
            if(path->m_from == nullptr && path != from){
                std::cout << "NOT REACHABLE";
                break;
            }else{
                std::cout << path->m_name;
                path = path->m_from;
                if(path != nullptr){
                    std::cout << " <- ";
                }
            }
        }
        std::cout << "\n--------------------------\n";
    }
}

bool Graph::init_path_finding(std::shared_ptr<Node> from){
    bool result = false;
    for(auto iter=m_nodelist.begin(); iter != m_nodelist.end(); ++iter){
        auto node = *iter;
        if(node != nullptr){
            if(node == from){
                node->init_path_finding(true);
                result = true;
            }else{
                node->init_path_finding(false);
            }
        }
    }

    return result;
}

//
}
// -*-