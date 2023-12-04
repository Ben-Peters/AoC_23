#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
const string FILENAME = "puzzle3.input.txt";
const int INPUT_COL = 140;
const int INPUT_ROW = 140;

int main () {
  string line;
  ifstream myfile (FILENAME);
  int sum = 0;
  char grid [INPUT_ROW][INPUT_COL] = {""};
  if (myfile.is_open())
  {
    for (int i = 0; i < INPUT_ROW; i++){
        getline (myfile,line);
        for (int j = 0; j < INPUT_COL; j++){
            grid[i][j] = line[j];
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
  }
  int number = 0;
  bool adjacent = false;
  for (int i = 0; i < INPUT_ROW; i++){
    for (int j = 0; j < INPUT_COL; j++){
        if (grid[i][j] >= 48 && grid[i][j] <= 57){
            number = (number * 10) + grid[i][j] - 48;
            for (int y_offset = -1; y_offset <= 1; y_offset++){
                for (int x_offset = -1;x_offset <= 1; x_offset++){
                    char c = grid[min(max(i + y_offset,0),INPUT_ROW-1)][min(max(j + x_offset,0),INPUT_COL-1)];
                    if (c <= 64 && c != 46 && !(c >= 48 && c <= 57)){
                        adjacent = true;
                    }
                }
            }
        } else {
            if (number && adjacent){
                printf("%d",number);
                sum += number;
            } else if (number){
                printf("~~~");
            }
            number = 0;
            adjacent = false;
            if (grid[i][j] <= 64 && grid[i][j] != 46){
            printf("*");
            } else {
            printf(" ");
            }
        }
    }
    if (number && adjacent){
                printf("%d",number);
                sum += number;
            } else if (number){
                printf("~~~");
            }
            number = 0;
            adjacent = false;
    printf("\n");
  }
  printf("SUM: %d", sum);
}
