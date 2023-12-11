#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
using namespace std;
const string FILENAME = "puzzle8.input.txt";
const int NUM_NODES = 726;
const string START_NODE = "AAA";
const string END_NODE = "ZZZ";
//#define PART_2 1

struct Node{
    string name;
    Node* left;
    Node* right;
    Node(string n, Node* l, Node* r){
        name = n;
        left = l;
        right = r;
    }
};

const Node* startPoint = (Node*) malloc(sizeof(Node));

int find_node_from_str(string node, string nodes_arr [NUM_NODES][3]){
    for(int i = 0; i < NUM_NODES; i++){
        if(nodes_arr[i][0] == node){
            return i;
        }
    }
    return -1;
}

int main(){
  string line;
  ifstream myfile (FILENAME);
  string directions;
  string str_nodes [NUM_NODES][3] = {};
  Node* nodes [NUM_NODES] = {};
  Node* cur_node;
  int num_steps = 0;
  if (myfile.is_open())
  {
    getline(myfile,line);
    directions = line;
    getline(myfile,line);
    //This is a blank line so toss it
    for(int i = 0; i < NUM_NODES; i++){
        getline (myfile,line);
        str_nodes [i][0] = line.substr(0,3);
        str_nodes [i][1] = line.substr(7,3);
        str_nodes [i][2] = line.substr(12,3);
        nodes[i] = (Node*) malloc(sizeof(Node));
        nodes[i]->name = str_nodes[i][0];
        if(nodes[i]->name == START_NODE){
            cur_node = nodes[i];
        }
    }
    for(int i=0; i<NUM_NODES; i++){
        auto node_str = str_nodes[i];
        Node* l_node = nodes[find_node_from_str(node_str[1],str_nodes)];
        Node* r_node = nodes[find_node_from_str(node_str[2],str_nodes)];
        nodes[i]->left = l_node;
        nodes[i]->right = r_node;
    }
  }
  while(cur_node->name != END_NODE){
    if(directions[num_steps%directions.length()] == 'L'){
        cur_node = cur_node->left;
        printf("Going LEFT to %s\n", cur_node->name.c_str());
    }else {
        cur_node = cur_node->right;
        printf("Going RIGHT to %s\n", cur_node->name.c_str());
    }
    num_steps ++;
  }
  printf("It took %d steps to get from AAA to ZZZ\n", num_steps);
}