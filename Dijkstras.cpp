#include <iostream>
#include <vector>
#include <fstream>

#define INF 10000000

using namespace std;

class Node {
public:
  string id;
  Node* previous;
  int dist;
  Node(string name) {
    id = name;
    previous = NULL;
    dist = INF;
    // nodes.push_back(this);
  }
};

class Edge {
public:
  Node* node1;
  Node* node2;
  int dist;
  Edge(Node* n1, Node* n2, int d) {
    node1 = n1;
    node2 = n2;
    dist = d;
  }

  bool Connected(Node* n1, Node* n2) {
    return ((n1 == node1 && n2 == node2) || (n1 == node2 && n2 == node1));
  }
};

class Graph {
private:
  vector<Node*> nodes_cpy;
  vector<Node*> nodes;
  vector<Edge*> edges;
  vector<Node*> path;
public:
  Graph() {
    Node* can = new Node("CAN");
    Node* usa = new Node("USA");
    Node* mex = new Node("MEX");
    Node* blz = new Node("BLZ");
    Node* gtm = new Node("GTM");
    Node* hnd = new Node("HND");
    Node* slv = new Node("SLV");
    Node* nic = new Node("NIC");
    Node* cri = new Node("CRI");
    Node* pan = new Node("PAN");

    nodes.push_back(can);
    nodes.push_back(usa);
    nodes.push_back(mex);
    nodes.push_back(blz);
    nodes.push_back(gtm);
    nodes.push_back(hnd);
    nodes.push_back(slv);
    nodes.push_back(nic);
    nodes.push_back(cri);
    nodes.push_back(pan);


    Edge* e1 = new Edge(can, usa, 1);
    Edge* e2 = new Edge(usa, mex, 1);
    Edge* e3 = new Edge(mex, blz, 1);
    Edge* e4 = new Edge(mex, gtm, 1);
    Edge* e5 = new Edge(blz, gtm, 1);
    Edge* e6 = new Edge(gtm, slv, 1);
    Edge* e7 = new Edge(gtm, hnd, 1);
    Edge* e8 = new Edge(slv, hnd, 1);
    Edge* e9 = new Edge(hnd, nic, 1);
    Edge* e10 = new Edge(nic, cri, 1);
    Edge* e11 = new Edge(cri, pan, 1);

    edges.push_back(e1);
    edges.push_back(e2);
    edges.push_back(e3);
    edges.push_back(e4);
    edges.push_back(e5);
    edges.push_back(e6);
    edges.push_back(e7);
    edges.push_back(e8);
    edges.push_back(e9);
    edges.push_back(e10);
    edges.push_back(e11);

    usa->dist = 0;  // set start node
    nodes_cpy = nodes;
  }

  Node* GetNode(string name) {
    for (int i = 0; i < nodes_cpy.size(); i++) {
      // cout << "ID: " << nodes_cpy[i]->id << endl;
      if (name == nodes_cpy[i]->id) {
        return nodes_cpy[i];
      }
    }
    // printf("Country does not exist\n");
    // exit(0);
    return NULL;
  }

  Node* ExtractSmallest(vector<Node*>& nodes) {
    int smallest_i = 0;
    Node* smallest = nodes.at(0);
    for (int i = 0; i < nodes.size(); i++) {
      Node* curr = nodes.at(i);
      if (curr->dist < smallest->dist) {
        smallest = curr;
        smallest_i = i;
      }
    }
    nodes.erase(nodes.begin() + smallest_i);
    return smallest;
  }

  bool Contains(vector<Node*>& nodes, Node* node) {
    const int size = nodes.size();
    for (int i = 0; i < size; i++) {
      if (node == nodes.at(i)) {
        return true;
      }
    }
    return false;
  }

  vector<Node*>* AdjacentRemainingNodes(Node* node) {
    vector<Node*>* adjNodes = new vector<Node*>();
    for (int i = 0; i < edges.size(); i++) {
      Edge* edge = edges.at(i);
      Node* adj = NULL;
      if (edge->node1 == node) {
        adj = edge->node2;
      } else if (edge->node2 == node) {
        adj = edge->node1;
      }
      if (adj && Contains(nodes, adj)) {
        adjNodes->push_back(adj);
      }
    }
    return adjNodes;
  }

  int Distance(Node* node1, Node* node2) {
    const int size = edges.size();
    for (int i = 0; i < size; i++) {
      Edge* edge = edges.at(i);
      if (edge->Connected(node1, node2)) {
        return edge->dist;
      }
    }
    return -1;
  }

  void GetPathTo(Node* dest) {
    Node* prev = dest;
    // cout << "Distance from start: " << dest->dist << endl;
    while (prev) {
      path.push_back(prev);
      prev = prev->previous;
    }
    cout << endl;
  }

  string SendPath() {
    // ofstream file("output.txt");
    string result = "<ul>";
    for (int i = path.size() - 1; i >= 0; i--) {
      // file << path[i]->id << endl;
      result +=  "<li>";
      result += path[i]->id;
      result += "</li>";
    }
    result += "</ul><br>";

    // file.close();
    return result;
  }

  void Dijkstras() {
    while(nodes.size() > 0) {
      Node* smallest = ExtractSmallest(nodes);
      vector<Node*>* adj = AdjacentRemainingNodes(smallest);

      for (int i = 0; i < adj->size(); ++i) {
        Node* a = adj->at(i);
        int distance = Distance(smallest, a) + smallest->dist;
        if (distance < a->dist) {
          a->dist = distance;
          a->previous = smallest;
        }
      }
      delete adj;
    }
  }
};

int main() {
  // cout << "HELLO WORLD \n";
  Graph* g = new Graph();
  g->Dijkstras();
  // Node* dest = g->GetNode("PAN");

  string input;

  cin >> input;  // Input is taken in from node server (server.js);

  Node* dest = g->GetNode(input);
  g->GetPathTo(dest);
  string result;
  if (dest != NULL) {
    result = g->SendPath();
    cout << result << endl;
    return 0;
  } else {
    result = "That Country is not in the map. <br>";
    cout << result << endl;
    return 0;
  }
}
