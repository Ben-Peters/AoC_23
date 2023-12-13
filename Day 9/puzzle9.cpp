#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
using namespace std;
const string FILENAME = "puzzle9.input.txt.test";
const int NUM_SEQS = 200;
#define PART_2 1

vector<int> find_diffs(vector<int> hist){
    vector<int> diffs;
    for(int i=1; i<hist.size(); i++){
        diffs.push_back(hist[i]-hist[i-1]);
    }
    return diffs;
}

bool check_all_zero(vector<int> l){
    bool flag = true;
    for(int i : l){
        flag &= (i == 0);
    }
    return flag;
}

int find_next_val(vector<int> hist){
    int next_val = 0;
    vector<int> diffs = find_diffs(hist);
    if(check_all_zero(diffs)){
        return hist.back();
    }else {
        return (find_next_val(diffs) + hist.back());
    }
}

int find_prev_val(vector<int> hist){
    int next_val = 0;
    vector<int> diffs = find_diffs(hist);
    if(check_all_zero(diffs)){
        next_val = hist.front();
    }else {
        next_val = (hist.front() - find_prev_val(diffs));
    }
    return next_val;
}

int main(){
    string line;
    ifstream myfile (FILENAME);
    int sum = 0;
    vector< vector<int> > input;
    while(getline(myfile,line)){
        vector<int> history;
        while(line.length() != 0){
            history.push_back(stoi(line.substr(0,line.find(" "))));
            if(line.find(" ") == string::npos){
                line = "";
            } else{
                line = line.substr(line.find(" ")+1);
            }
        }
        input.push_back(history);
    }
    for(vector<int> hist: input){
        #ifdef PART_2
        sum += find_prev_val(hist);
        #else
        sum += find_next_val(hist);
        #endif
        printf("SUM: %d\n", sum);
    }
}