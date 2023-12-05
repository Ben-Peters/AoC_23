#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
const string FILENAME = "puzzle3.input.txt";
const int INPUT_COL = 140;
const int INPUT_ROW = 140;
//#define PART_1 1;

int find_number(char grid[][INPUT_COL], int i, int j){
    int start;
    int num  = 0;
    for(start = j; (grid[i][j] >= 48 && grid[i][j] <= 57); j--){
        if (j < 0){
            break;
        }
        start = j;
    }
    for(j = start; (grid[i][j] >= 48 && grid[i][j] <= 57); j++){
        if(j >= INPUT_COL){
            break;
        }
        num = (num * 10) + grid[i][j] - 48;;
    }
    return num;
}

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
  #ifdef PART_1
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
  #else
    for (int i = 0; i < INPUT_ROW; i++){
    for (int j = 0; j < INPUT_COL; j++){
        if (grid[i][j] == 42){
            int num_parts = 0;
            int part_loc [2][2];
            bool same_num = false;
            for (int y_offset = -1; y_offset <= 1; y_offset++){
                for (int x_offset = -1;x_offset <= 1; x_offset++){
                    if ((i + y_offset < 0 || i + y_offset >= INPUT_ROW) || (j + x_offset < 0 || j + x_offset >= INPUT_COL)){
                        continue;
                    }
                    char c = grid[i + y_offset][j + x_offset];
                    if (c >= 48 && c <= 57){
                        if (same_num){
                            continue;
                        }
                        same_num = true;
                        if (num_parts < 2) {
                            part_loc [num_parts][0] = i + y_offset;
                            part_loc [num_parts][1] = j + x_offset;
                        }
                        num_parts ++;
                    } else {
                        same_num = false;
                    }
                }
                same_num = false;
            }
            if (num_parts == 2){
                int num1 = find_number(grid, part_loc[0][0], part_loc[0][1]);
                int num2 = find_number(grid, part_loc[1][0], part_loc[1][1]);
                sum += (num1 * num2);
            }
            printf("*");
        } else {
            if (grid[i][j] >= 48 && grid[i][j] <= 57){
                printf("%c", grid[i][j]);
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
  #endif
  printf("SUM: %d", sum);
}
