#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
const string FILENAME = "puzzle2.input.txt";
const int RED_LIM = 12;
const int BLUE_LIM = 14;
const int GREEN_LIM = 13;

int main () {
  string line;
  ifstream myfile (FILENAME);
  int sum = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {    
      int red_max = 0;
      int blue_max = 0;
      int green_max = 0;  
      cout << line << '\n';
      int gameID = stoi(line.substr(5, line.find(":")-5));
      bool possible = true;
      //cout << gameID << endl;
      line = line.substr(line.find(":")+2);
      while (line.length() > 0 && possible){
          string set;
          if (line.find(";") == string::npos){
            set = line;
            line = "";
          }else {
            set = line.substr(0,line.find(";"));
            line = line.substr(line.find(";")+2);
          }
        while (set.length() > 0 && possible){
          string cubes;
          if (set.find(",") == string::npos){
            cubes = set;
            set = "";
          }else {
            cubes = set.substr(0,set.find(","));
            set = set.substr(set.find(",")+2);
          }
          //printf("%s\n", cubes.c_str());
          if(cubes.find("red") != string::npos){
            int num_red = stoi(cubes.substr(0, cubes.find(" ")));
            if(num_red > red_max){
              red_max = num_red;
            }
            //if(stoi(cubes.substr(0, cubes.find(" "))) > RED_LIM){
            //  possible = false;
            //  break;
            //}
          } else if(cubes.find("blue") != string::npos){
            int num_blue = stoi(cubes.substr(0, cubes.find(" ")));
            if(num_blue > blue_max){
              blue_max = num_blue;
            }
            //if(stoi(cubes.substr(0, cubes.find(" "))) > BLUE_LIM){
            //  possible = false;
            //  break;
            //}
          } else if(cubes.find("green") != string::npos){
            int num_green = stoi(cubes.substr(0, cubes.find(" ")));
            if(num_green > green_max){
              green_max = num_green;
            }
            //if(stoi(cubes.substr(0, cubes.find(" "))) > GREEN_LIM){
            //  possible = false;
            //  break;
            //}
          }
        }
      }
      //sum += possible * gameID;
      sum += red_max * blue_max * green_max;
      printf("SUM: %d\n", sum);
    }
  }
}