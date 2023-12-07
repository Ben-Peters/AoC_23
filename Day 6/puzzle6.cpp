#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int NUM_RACES = 1;
long long times[NUM_RACES] = {44707080};//{7, 15, 30};{71530};
long long dists[NUM_RACES] = {283113411341491};//{9, 40, 200};{940200};
//#define PART_1 1

int main(){
    int total_wins = 0;
    int wins = 0;
    for (int i=0; i<NUM_RACES; i++){
        for(int time_held=1; time_held < times[i]; time_held++){
            if(time_held*(times[i]-time_held) > dists[i]){
                wins++;
            } else if(wins != 0){
                //break;
            }
        }
        if(total_wins == 0){
            total_wins = wins;
        } else {
            total_wins *= wins;
        }
        wins = 0;
    }
    printf("%d\n", total_wins);
}