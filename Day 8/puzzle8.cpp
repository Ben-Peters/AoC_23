#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <numeric>
using namespace std;
const string FILENAME = "puzzle8.input.txt";
const int NUM_NODES = 726;
const string START_NODE = "AAA";
const string END_NODE = "ZZZ";
#define PART_2 1
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
  vector<Node*> cur_nodes_list;
  long long num_steps = 0;
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
        #ifdef PART_2 
        if(nodes[i]->name[2] == 'A'){
            cur_nodes_list.push_back(nodes[i]);
        }
        #else
        if(nodes[i]->name == START_NODE){
            cur_node = nodes[i];
        }
        #endif
    }
    for(int i=0; i<NUM_NODES; i++){
        auto node_str = str_nodes[i];
        Node* l_node = nodes[find_node_from_str(node_str[1],str_nodes)];
        Node* r_node = nodes[find_node_from_str(node_str[2],str_nodes)];
        nodes[i]->left = l_node;
        nodes[i]->right = r_node;
    }
  }
  int num_done = 0;
  int *loop_size = (int*) calloc(cur_nodes_list.size(), sizeof(int));
  bool loop_found [6] = {0,0,0,0,0,0};
  #ifdef PART_2
  while(num_done < cur_nodes_list.size()){
  #else
  while(cur_node->name != END_NODE){
  #endif

    if(directions[num_steps%directions.length()] == 'L'){
        #ifdef PART_2
        for(int i=0; i < cur_nodes_list.size(); i++){
            cur_nodes_list[i] = cur_nodes_list[i]->left;
            if(cur_nodes_list[i]->name[2] == 'Z' && loop_found[i] == false){
                printf("Sarting Node %d found a solution after %lld steps\n", i, num_steps+1);
                loop_size[num_done] = num_steps;
                loop_found[i]=true;
                num_done++;
            }
        }
        #else
        cur_node = cur_node->left;
        printf("Going LEFT to %s\n", cur_node->name.c_str());
        #endif
    }else {
        #ifdef PART_2
        for(int i=0; i < cur_nodes_list.size(); i++){
            cur_nodes_list[i] = cur_nodes_list[i]->right;
            if(cur_nodes_list[i]->name[2] == 'Z' && loop_found[i] == false){
                printf("Sarting Node %d found a solution after %lld steps\n", i, num_steps+1);
                loop_size[num_done] = num_steps;
                loop_found[i]=true;
                num_done++;
            }
        }
        #else
        cur_node = cur_node->right;
        printf("Going RIGHT to %s\n", cur_node->name.c_str());
        #endif
    }
    num_steps ++;
    if(num_done>2){
       // printf("%lld: %d done\n", num_steps, num_done);
    }
  }
  long long least_mult[6];
  bool done = false;
  while(!done){
    done = true;
    for(int i=0; i<6; i++){
        least_mult[i] += loop_size[i];
        while(least_mult[i] < least_mult[5]){
            least_mult[i] += loop_size[i];
        }
    }
    for(long long n : least_mult){
        done &= (n == least_mult[0]);
        //printf("%lld, ",n);
    }
    if((least_mult[0] % 1000000000)==0) {
        printf("%lld\n", least_mult[0]);
    }
  }
  printf("It took %lld steps\n", least_mult[0]);
}