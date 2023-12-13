#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
using namespace std;
const string FILENAME = "puzzle10.input.txt";
const int GRID_LEN = 140;
const int GRID_WID = 140;

int start_x, start_y;

enum dir {
    NORTH,
    SOUTH,
    EAST,
    WEST,
    NONE
};

struct pipe {
    dir dir1;
    dir dir2;
    pipe* con1 = nullptr;
    pipe* con2 = nullptr;
    bool con_to_start = false;
    int dist_to_start;

    pipe(char c){
        switch (c){
        case '|':
            dir1 = NORTH;
            dir2 = SOUTH;
            break;
        case 'L':
            dir1 = NORTH;
            dir2 = EAST;
            break;
        case 'J':
            dir1 = NORTH;
            dir2 = WEST;
            break;
        case '7':
            dir1 = SOUTH;
            dir2 = WEST;
            break;
        case 'F':
            dir1 = SOUTH;
            dir2 = EAST;
            break;
        case '-':
            dir1 = EAST;
            dir2 = WEST;
            break;
        case 'S':
            dir1 = NORTH;
            dir2 = WEST;
            //dir1=SOUTH;
            //dir2=EAST;
            con_to_start = true;
            dist_to_start = 0;
            return;
            break;
        default:
            dir1 = NONE;
            dir2 = NONE;
        }
        dist_to_start = 0;
        con_to_start = 0;
    }
};

vector< vector<pipe> > grid;

char pipe_to_char(pipe p){
    if(p.dir1 == NORTH){
        if (p.dir2 == SOUTH)
            return 'l';
        else if (p.dir2 == EAST)
            return 'L';
        else if (p.dir2 == WEST)
            return 'J';
    } else if(p.dir1 == SOUTH){
        if (p.dir2 == EAST)
            return 'F';
        else if (p.dir2 == WEST)
            return '7';
    } else if (p.dir1 == EAST){
        if (p.dir2 == WEST)
            return '-';
    } else if (p.dir1 == NONE){
        if (p.con_to_start)
            return 'S';
        else
            return '.';
    }
    return '?';
}

void dump_grid(bool dist = false, bool filter = false){
    for(vector<pipe> line : grid){
        for(pipe p : line){
            if(dist){
                if (p.dir1 == NONE && !p.con_to_start){
                    printf(".");
                }else{
                    printf("%d",p.dist_to_start);
                }
            }
            else{
                if(p.con_to_start){
                    printf("%c", pipe_to_char(p));
                } else {
                    printf(".");
                }
            }
        }
        printf("\n");
    }
}

int** pipe_to_vect(pipe p, int (&vectors)[2][2]){
    if(p.dir1 == NORTH){
        vectors[0][0] = 0;
        vectors[0][1] = -1;
        if (p.dir2 == SOUTH){
            vectors[1][0] = 0;
            vectors[1][1] = 1;
        }
        else if (p.dir2 == EAST){
            vectors[1][0] = 1;
            vectors[1][1] = 0;
        }
        else if (p.dir2 == WEST){
            vectors[1][0] = -1;
            vectors[1][1] = 0;
        }
    } else if(p.dir1 == SOUTH){
        vectors[0][0] = 0;
        vectors[0][1] = 1;
        if (p.dir2 == EAST){
            vectors[1][0] = 1;
            vectors[1][1] = 0;
        }
        else if (p.dir2 == WEST){
            vectors[1][0] = -1;
            vectors[1][1] = 0;
        }
    } else if (p.dir1 == EAST){
        vectors[0][0] = 1;
        vectors[0][1] = 0;
        if (p.dir2 == WEST){
            vectors[1][0] = -1;
            vectors[1][1] = 0;
        }
    }
}

int find_max_dist(){
    while(true){
        
    }
}

dir rev(dir d){
    switch (d){
        case NORTH:
            return SOUTH;
        case SOUTH:
            return NORTH;
        case EAST:
            return WEST;
        case WEST:
            return EAST;
    }
    return NONE;
}

dir check_connection(pipe *p1, pipe *p2){
    if (p1->con1 == p2 || p2->con1 == p1){
        return p2->dir1;
    }else if (p1->con2 == p2 || p2->con2 == p1){
        return p2->dir2;
    }
    //int p1vect[2][2];
    //pipe_to_vect(*p1,p1vect);
    //int p2vect[2][2]; 
    //pipe_to_vect(*p2,p2vect);
    if(p1->con1 == nullptr){
        if(p1->dir1 == rev(p2->dir1)){
            p1->con1 = p2;
            p2->con1 = p1;
            return p2->dir1;
        }else if(p1->dir1 == rev(p2->dir2)){
            p1->con1 = p2;
            p2->con2 = p1;
            return p2->dir2;
        }
    }else if(p1->con2 == nullptr){
        if(p1->dir2 == rev(p2->dir1)){
            p1->con2 = p2;
            p2->con1 = p1;
            return p2->dir1;
        }else if(p1->dir2 == rev(p2->dir2)){
            p1->con2 = p2;
            p2->con2 = p1;
            return p2->dir2;
        }
    }
    return NONE;
}
    // if(p1vect[0][0] + p2vect[0][0] == 0 && p1vect[0][1] + p2vect[0][1] == 0){
    //     p1->con1 = p2;
    //     p2->con1 = p1;
    //     return p2->dir1;
    // }else if(p1vect[1][0] + p2vect[1][0] == 0 && p1vect[1][1] + p2vect[1][1] == 0){
    //     p1->con2 = p2;
    //     p2->con2 = p1;
    //     return p2->dir2;
    // }else if(p1vect[0][0] + p2vect[1][0] == 0 && p1vect[0][1] + p2vect[1][1] == 0){
    //     p1->con1 = p2;
    //     p2->con2 = p1;
    //     return p2->dir2;
    // }else if(p1vect[1][0] + p2vect[0][0] == 0 && p1vect[1][1] + p2vect[0][1] == 0){
    //     p1->con2 = p2;
    //     p2->con1 = p1;
    //     return p2->dir1;
    // }
//     return NONE;
// }

int main(){
    ifstream myfile (FILENAME);
    for(int i=0; i<GRID_LEN; i++){
        vector<pipe> pipe_line;
        string line;
        getline(myfile,line);
        for(int j=0; j<GRID_WID; j++){
            if(line[j] == 'S'){
                start_x = j;
                start_y = i;
            }
            pipe_line.push_back(pipe(line[j]));
        }
        grid.push_back(pipe_line);
    }
    pipe *cur_pipe = &grid[start_y][start_x];
    //int cur_vect[2][2] = {0, -1, 
    //                     -1, 0};
    int cur_vect[2][2];
    pipe_to_vect(*cur_pipe, cur_vect);
    int next_x = start_x + cur_vect[0][0];
    int next_y = start_y + cur_vect[0][1];
    int dist = 0;
    pipe *next_pipe = &grid[next_y][next_x];
    dir last_dir = SOUTH;
    while (next_pipe != &grid[start_y][start_x]){
        last_dir = check_connection(cur_pipe, next_pipe);
        if (last_dir != NONE){
            dist++;
            next_pipe->con_to_start = true;
            next_pipe->dist_to_start = dist;
            cur_pipe = next_pipe;
            pipe_to_vect(*cur_pipe, cur_vect);
            if(cur_pipe->dir2 == last_dir){
                next_x += cur_vect[0][0];
                next_y += cur_vect[0][1];
                next_pipe = &grid[next_y][next_x];
            }else if(cur_pipe->dir1 == last_dir){
                next_x += cur_vect[1][0];
                next_y += cur_vect[1][1];
                next_pipe = &grid[next_y][next_x];
            }else{
                printf("We hit a loop but shouldn't have\n");
            }
        }
        else{
            printf("we are looking off the track\n");
        }
        //dump_grid(false, true);
        //printf("\x1b[2J");
    }
    dump_grid(false, true);
    printf("Max Dist = %d / 2 = %d\n", dist+1, (dist+1)/2);
    // vector<int[2]> past_cord;
    // 
    // for (vector<pipe> line : grid){
    //     for(pipe p : line){
    //         int **vect = pipe_to_vect(p);
    //         pipe next_pipe = grid[cur_y + vect[0][1]][cur_x + vect[0][0]];
    //         int **next_vect = pipe_to_vect(next_pipe);
    //         if((vect[0][1] + next_vect[0][1] == 0 && vect[0][0] + next_vect[0][0]
    //             || (vect[0][1] + next_vect[1][1] == 0 && vect[0][0] + next_vect[1][0]))){
    //             cur_x = cur_x + vect[0][0];
    //             cur_y = cur_y + vect[0][1];
    //             p.con1 = &next_pipe;
    //         }else {
    //             next_pipe = grid[cur_y + vect[1][1]][cur_x + vect[1][0]];
    //             next_vect = pipe_to_vect(next_pipe);
    //             if((vect[1][1] + next_vect[0][1] == 0 && vect[1][0] + next_vect[0][0]
    //             || (vect[1][1] + next_vect[1][1] == 0 && vect[1][0] + next_vect[1][0]))){
    //                 cur_x = cur_x + vect[1][0];
    //                 cur_y = cur_y + vect[1][1];
    //                 p.con2 = &next_pipe;
    //             }
    //         }
    //     }
    // }
}