#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
using namespace std;
const string FILENAME = "puzzle5.input.txt";
const int NUM_SEEDS = 20;
const int NUM_MAPS = 7;
struct map{
    long long dst_start;
    long long src_start;
    long long rng_len;
    map(long long d_start, long long s_start, long long r_len){
        dst_start = d_start;
        src_start = s_start;
        rng_len = r_len;
    }
};
//#define PART_1 1

long long try_transform(long long input, long long dst_start, long long src_start, long long rng_len){
    if(src_start <= input && input <= (src_start+rng_len-1)){
        long long offset = dst_start - src_start;
        return input + offset;
    } else {
        return -1;
    }
}

long long try_transform(long long input, list<map>* maps){
    for(int i=0; i < NUM_MAPS; i++){
        for( list<map>::iterator it = maps[i].begin(); it != maps[i].end(); ++it){
            long long res = try_transform(input, it->dst_start, it->src_start, it->rng_len);
            if(res != -1){
                input = res;
                break;
            }
        }
    }
    return input;
}

int main(){
  string line;
  ifstream myfile (FILENAME);
  long long seeds[NUM_SEEDS];
  bool trans_flags[NUM_SEEDS];
  int map_num = -1;
  list<map> maps[NUM_MAPS];
  if (myfile.is_open())
  {
    getline (myfile,line);
    line = line.substr(7);
    for(int i = 0; i < NUM_SEEDS; i++){
        seeds [i] = stoll(line.substr(0, line.find(" ")));
        line = line.substr(line.find(" ")+1);
    }
    while (getline(myfile,line)){
        printf("%s\n", line.c_str());
        if(line.find("map") != string::npos){
            // do something before each map
            map_num++;
            for(int i=0; i<NUM_SEEDS; i++){
                trans_flags[i]=false;
            }
        } else if(line != "\0"){
            long long dst_start = stoll(line.substr(0,line.find(" ")));
            line = line.substr(line.find(" ")+1);
            long long src_start = stoll(line.substr(0,line.find(" ")));
            line = line.substr(line.find(" ")+1);
            long long rng_len = stoll(line);
#ifdef PART_1
            for(int i=0; i < NUM_SEEDS; i++){
                if(trans_flags[i]){
                    continue;
                }
                long result = try_transform(seeds[i], dst_start, src_start, rng_len);
                if(result >= 0){
                    trans_flags[i] = true;
                    seeds[i] = result;
                }
            }
#else
            map m = map(dst_start, src_start, rng_len);
            maps[map_num].push_back(m);

#endif
        } else {
            for(int i=0; i<NUM_SEEDS; i++){
                printf("%lld ", seeds[i]);
            }
            printf("\n");
        }
    }
  }
#ifdef PART_1
  long long min_loc = seeds[0];
  for(int i=0; i<NUM_SEEDS; i++){
    printf("%lld ", seeds[i]);
    if (seeds[i] < min_loc){
        min_loc = seeds[i];
    }
  }
#else
  long long min_loc = seeds[0];
  for (int i=0; i < NUM_SEEDS; i+=2){
    long long seed_start = seeds[i];
    long long seed_rng = seeds[i+1];
    for(long long j = seed_start; j < seed_start+seed_rng; j++){
        long long loc = try_transform(j, maps);
        if(loc < min_loc){
            min_loc = loc;
        }
    }
  }
#endif
    printf("\n");
    printf("Min_Location: %lld", min_loc);
}