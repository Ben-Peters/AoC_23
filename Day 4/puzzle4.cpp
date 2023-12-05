#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
const string FILENAME = "puzzle4.input.txt";
const int INPUT_GAMES = 197;
const int WINNERS = 10;
const int MINE = 25;
//#define PART_1 1;

int main(){
  string line;
  ifstream myfile (FILENAME);
  int sum = 0;
  if (myfile.is_open())
  {
    for (int i = 0; i < INPUT_GAMES; i++){
        int winning_nums [WINNERS] = {};
        int my_nums [MINE] = {};
        getline (myfile,line);
        printf("Card %d: ", i+1);
        line = line.substr(10);
        for(int j = 0; j < WINNERS; j++){
            winning_nums[j] = stoi(line.substr(0,2));
            line = line.substr(3);
        }
        line = line.substr(2);
        for(int j = 0; j < MINE; j++){
            my_nums[j] = stoi(line.substr(0,2));
            if(line.length() >= 3)
                line = line.substr(3);
        }

        uint points = 0;
        for (int j = 0; j < WINNERS; j++){
            for (int k = 0; k < MINE; k++){
                if (winning_nums[j] == my_nums[k]){
                    if(!points){
                        points += 1;
                    } else {
                        points *= 2;
                    }
                }
            }
        }
        printf("%u", points);
        sum += points;
        printf("\n");
    }
  }
  printf("SUM: %d\n", sum);
}