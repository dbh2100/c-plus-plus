#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <cassert>
using namespace std;

class Node{
    
protected:
    map<Node*, int> connections;
    
public:
    Node(string);
    void add_connection(Node*, int);
    int find_distance(Node*, unordered_set<Node*>);
    
};

Node::Node(string _name) {
    string name = _name;
}

void Node::add_connection(Node* node, int distance) {
    connections[node] = distance;
}

int Node::find_distance(Node* endpoint, unordered_set<Node*> _previous) {
    if (connections.find(endpoint) != connections.end())
        return connections[endpoint];
    unordered_set<Node*> previous = _previous;
    previous.insert(this);
    int min_distance = -1;
    for (map<Node*, int>::iterator it = connections.begin(); it!= connections.end(); it++) {
        Node* midpoint = it->first;
        if (previous.find(midpoint) == previous.end()) {
            int end_distance = midpoint->find_distance(endpoint, previous);
            if (end_distance > -1) {
                int total_distance = it->second + end_distance;
                if (min_distance == -1)
                    min_distance = total_distance;
                else
                    min_distance = min(total_distance, min_distance);
            }
        }
    }
    return min_distance;
}

class Graph{
    
protected:
    unordered_map<string, Node*> nodes; //map the key to the node in the linked list

public:
    void add_connection(string, string, int);
    int find_distance(string, string);
    
};

void Graph::add_connection(string name1, string name2, int distance) {
    Node* node1; Node* node2;
    if (nodes.find(name1) == nodes.end()) {
        node1 = new Node(name1);
        nodes[name1] = node1;
    }
    else
        node1 = nodes[name1];
    if (nodes.find(name2) == nodes.end()) {
        node2 = new Node(name2);
        nodes[name2] = node2;
    }
    else
        node2 = nodes[name2];
    node1->add_connection(node2, distance);
    node2->add_connection(node1, distance);
}

int Graph::find_distance(string name1, string name2) {
    if (nodes.find(name1) == nodes.end())
        return -1;
    if (nodes.find(name2) == nodes.end())
        return -1;
    unordered_set<Node*> empty_set;
    return nodes[name1]->find_distance(nodes[name2], empty_set);
}

int main() {
    
    Graph graph;
    
    graph.add_connection("a", "b", 3);
    graph.add_connection("a", "c", 5);
    graph.add_connection("b", "d", 8);
    graph.add_connection("c", "d", 2);
    graph.add_connection("e", "f", 20);
    
    cout << graph.find_distance("a", "b") << endl;
    cout << graph.find_distance("a", "d") << endl;
    cout << graph.find_distance("a", "e") << endl;
    cout << graph.find_distance("d", "g") << endl;
    cout << graph.find_distance("f", "e") << endl;
    
    return 0;
    
}
