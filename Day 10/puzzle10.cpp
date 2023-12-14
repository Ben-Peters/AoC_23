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
    bool inside_loop = false;
    pipe* next_pipe = nullptr;
    dir exit_dir;
    dir ent_dir;
    int grid_pos[2];

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
                    if(p.inside_loop){
                        printf("I");
                    }else{
                        printf(".");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void dir_to_vect(dir d, int (&v)[2]){
    switch (d){
        case NORTH:
            v[0] = 0;
            v[1] = -1;
            break;
        case SOUTH:
            v[0] = 0;
            v[1] = 1;
            break;
        case EAST:
            v[0] = 1;
            v[1] = 0;
            break;
        case WEST:
            v[0] = -1;
            v[1] = 0;
            break;
        default:
            printf("\nDIR TO VECT RUN ON NONE\n");
            break;
    }
}

void pipe_to_vect(pipe p, int (&vectors)[2][2]){
    dir_to_vect(p.dir1, vectors[0]);
    dir_to_vect(p.dir2, vectors[1]);
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
        default:
            return NONE;
    }
    return NONE;
}

dir check_connection(pipe *p1, pipe *p2){
    if (p1->con1 == p2 || p2->con1 == p1){
        return p2->dir1;
    }else if (p1->con2 == p2 || p2->con2 == p1){
        return p2->dir2;
    }
    p1->next_pipe = p2;
    if(p1->con1 == nullptr){
        p1->exit_dir = p1->dir1;
        p1->ent_dir = p1->dir2;
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
        p1->exit_dir = p1->dir2;
        p1->ent_dir = p1->dir1;
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

dir anti_normal(dir d){
    switch (d){
        case NORTH:
            return WEST;
        case WEST:
            return SOUTH;
        case SOUTH:
            return EAST;
        case EAST:
            return NORTH;
        default:
            return NONE;
    }
}

void propogate_inside(pipe* p){
    for(int i=-1; i <= 1; i +=2){
        for(int j=-1; j <= 1; j +=2){
            pipe* adj = &grid[p->grid_pos[1]+i][p->grid_pos[0]+j];
            if(!adj->con_to_start && !adj->inside_loop){
                //Found an adjacent ground square that isn't marked
                adj->inside_loop = true;
                propogate_inside(adj);
            }
        }
    }
}

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
            pipe p = pipe(line[j]);
            p.grid_pos[0] = j;
            p.grid_pos[1] = i;
            pipe_line.push_back(p);
        }
        grid.push_back(pipe_line);
    }
    pipe *cur_pipe = &grid[start_y][start_x];
    int cur_vect[2][2];
    pipe_to_vect(*cur_pipe, cur_vect);
    int next_x = start_x + cur_vect[0][0];
    int next_y = start_y + cur_vect[0][1];
    cur_pipe->grid_pos[0] = start_x;
    cur_pipe->grid_pos[1] = start_y;
    int dist = 0;
    pipe *next_pipe = &grid[next_y][next_x];
    dir last_dir = rev(cur_pipe->dir1);
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
            return -1;
        }
        //dump_grid(false, true);
        //printf("\n");
    }
    check_connection(cur_pipe, next_pipe);
    dump_grid(false, true);
    printf("Max Dist = %d / 2 = %d\n", dist+1, (dist+1)/2);
    cur_pipe = &grid[start_y][start_x];
    next_pipe = cur_pipe->next_pipe;
    int shoestirng = 0;
    while(cur_pipe != &grid[start_y][start_x] || shoestirng == 0){
        int ant_norm[2];
        dir_to_vect(anti_normal(cur_pipe->exit_dir), ant_norm);
        pipe* inside_node = &grid[cur_pipe->grid_pos[1]+ant_norm[1]][cur_pipe->grid_pos[0]+ant_norm[0]];
        if(!inside_node->con_to_start){
            inside_node->inside_loop=true;
        }
        // Check if 90 pipe has ground next to it in the other direction
        dir_to_vect(anti_normal(rev(cur_pipe->ent_dir)), ant_norm);
        inside_node = &grid[cur_pipe->grid_pos[1]+ant_norm[1]][cur_pipe->grid_pos[0]+ant_norm[0]];
        if(!inside_node->con_to_start){
            inside_node->inside_loop=true;
        }
        shoestirng += (((cur_pipe->grid_pos[0]+1)*(next_pipe->grid_pos[1]+1))-((cur_pipe->grid_pos[1]+1)*(next_pipe->grid_pos[0]+1)));
        cur_pipe = next_pipe;
        next_pipe = cur_pipe->next_pipe;
    }
    dump_grid(false,true);
    for(vector<pipe> line : grid){
        for(pipe p : line){
            if(p.inside_loop){
                propogate_inside(&p);
            }
        }
    }
    int sum = 0;
    for(vector<pipe> line : grid){
        for(pipe p : line){
            if(p.inside_loop){
                sum++;
            }
        }
    }
    dump_grid(false,true);
    printf("SUM: %d\n", sum); 
    if (shoestirng < 0){
        shoestirng *= -1;
    }
    int area = shoestirng / 2;
    printf("SHOESTRING: %d\n", (area + 1 - ((dist+1)/2)));
}