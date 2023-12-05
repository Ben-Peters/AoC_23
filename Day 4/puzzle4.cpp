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
  int cards [INPUT_GAMES][2][MINE];
  int num_copies[INPUT_GAMES];
  for(int i=0;i<INPUT_GAMES;i++){num_copies[i]=1;}
  if (myfile.is_open())
  {
    for (int i = 0; i < INPUT_GAMES; i++){
        int winning_nums [WINNERS] = {};
        int my_nums [MINE] = {};
        getline (myfile,line);
        //printf("Card %d: ", i+1);
        line = line.substr(10);
        for(int j = 0; j < WINNERS; j++){
            winning_nums[j] = stoi(line.substr(0,2));
            cards [i][0][j] = stoi(line.substr(0,2));
            line = line.substr(3);
        }
        line = line.substr(2);
        for(int j = 0; j < MINE; j++){
            my_nums[j] = stoi(line.substr(0,2));
            cards [i][1][j] = stoi(line.substr(0,2));
            if(line.length() >= 3)
                line = line.substr(3);
        }

#ifdef PART_1
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
#else
    }
    for (int i = 0; i < INPUT_GAMES; i++){
        int matches = 0;
        for (int j = 0; j < WINNERS; j++){
            for (int k = 0; k < MINE; k++){
                if (cards[i][0][j] == cards[i][1][k]){
                    matches ++;
                }
            }
        }
        for (int j = 1; j <= matches; j++){
            if(i+j >= INPUT_GAMES){
                break;
            }
            num_copies[i+j] += 1 * num_copies[i];
        }
        printf("Card %d: (%d, %d)\n", i+1, num_copies[i], matches);
        sum += num_copies[i];
    }
  #endif
}
  printf("SUM: %d\n", sum);
}