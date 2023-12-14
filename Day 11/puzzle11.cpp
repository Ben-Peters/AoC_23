#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;
const string FILENAME = "puzzle11.input.txt";
const int GRID_LEN = 140;
const int GRID_WID = 140;

struct coordinate{
    int x;
    int y;

    coordinate(int newX, int newY){
        x = newX;
        y = newY;
    }
    coordinate(){
        x = -1;
        y = -1;
    }
};

struct galaxy{
    coordinate location;

    galaxy(int x, int y){
        location = coordinate(x,y);
    }
};

list<galaxy> galaxies;
list< pair<galaxy,galaxy> > pairs;


void expand(bool vertical, int thresh){
    for(galaxy &g: galaxies){
        if(g.location.x > thresh && vertical){
            g.location.x +=1;
        }else if(g.location.y > thresh && !vertical){
            g.location.y +=1;
        }
    }
}

int main(){
    string line;
    ifstream myfile (FILENAME);
    for(int row=0; row < GRID_LEN; row++){
        getline(myfile,line);
        for(int col=0; col< GRID_WID; col++){
            switch (line[col]){
                case '#':
                    galaxies.push_back(galaxy(col,row));
                    break;
                default:
                    continue;
            }
        }
    }
    int row_col_grid[2][GRID_LEN] = {};
    for(galaxy g: galaxies){
        row_col_grid[0][g.location.x] +=1;
        row_col_grid[1][g.location.y] +=1;
    }
    int x_offset = 0;
    int y_offset = 0;
    for(int i=0; i<GRID_LEN; i++){
        if (!row_col_grid[0][i]){
            expand(true, i+x_offset);
            x_offset++;
        }else if(!row_col_grid[1][i]){
            expand(false, i+y_offset);
            y_offset++;
        }
    }
    for(list<galaxy>::iterator it1 = galaxies.begin(); it1 != galaxies.end(); it1++){
        list<galaxy>::iterator it2 = it1;
        for(it2++; it2 != galaxies.end();  it2++){
            pairs.push_back(make_pair(*it1,*it2));
        }
    }
    int sum = 0;
    for(pair<galaxy, galaxy> p: pairs){
        int dist = abs(p.first.location.x - p.second.location.x) + abs(p.first.location.y - p.second.location.y);
        sum += dist;
    }
    printf("SUM: %d\n",sum);
}