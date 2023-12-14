#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;
const string FILENAME = "puzzle11.input.txt";
const int GRID_LEN = 140;
const int GRID_WID = 140;

#define PART_2

struct coordinate{
    long long x;
    long long y;

    coordinate(long long newX, long long newY){
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


void expand(bool vertical, long long thresh){
    for(galaxy &g: galaxies){
        if(g.location.x > thresh && vertical){
            #ifdef PART_2
            g.location.x +=999999;
            #else
            g.location.x +=1;
            #endif
        }else if(g.location.y > thresh && !vertical){
            #ifdef PART_2
            g.location.y +=999999;
            #else
            g.location.y +=1;
            #endif
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
    long long x_offset = 0;
    long long y_offset = 0;
    for(long long i=0; i<GRID_LEN; i++){
        if (!row_col_grid[0][i]){
            expand(true, i+x_offset);
            #ifdef PART_2
            x_offset += 999999;
            #else
            x_offset += 1;
            #endif
            printf("Exanding x\n");
        }else if(!row_col_grid[1][i]){
            expand(false, i+y_offset);
            #ifdef PART_2
            y_offset += 999999;
             #else
            y_offset += 1;
            #endif
            printf("Exanding y\n");
        }
    }
    for(list<galaxy>::iterator it1 = galaxies.begin(); it1 != galaxies.end(); it1++){
        list<galaxy>::iterator it2 = it1;
        for(it2++; it2 != galaxies.end();  it2++){
            pairs.push_back(make_pair(*it1,*it2));
        }
    }
    long long sum = 0;
    for(pair<galaxy, galaxy> p: pairs){
        long long dist = abs(p.first.location.x - p.second.location.x) + abs(p.first.location.y - p.second.location.y);
        sum += dist;
    }
    printf("SUM: %lld\n",sum);
}