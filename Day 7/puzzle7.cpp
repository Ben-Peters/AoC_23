#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <list>
using namespace std;
const string FILENAME = "puzzle7.input.txt";
const int NUM_HANDS = 1000;
#define PART_2 1

char card_opts[12] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};

enum hand_type {
    FIVE_OF_KIND = 7,
    FOUR_OF_KIND = 6,
    FULL_HOUSE = 5,
    THREE_OF_KIND = 4,
    TWO_PAIR = 3,
    ONE_PAIR = 2,
    HIGH_CARD = 1,
    NO_TYPE = 0
};

struct hand {
    string cards;
    int bid;
    hand_type h_type;
    hand(string c, int b, hand_type t){
        cards = c;
        bid = b;
        h_type = t;
    }
    hand(){
        cards="";
        bid=0;
        h_type=NO_TYPE;
    }
};

array<hand, NUM_HANDS> hands;

hand_type findType(string hand){
    int unq_chars = 1;
    string seen_chars = hand.substr(0,1);
    for (int i=1; i < 5; i++){
        if(seen_chars.find(hand.substr(i,1)) == string::npos){
            seen_chars.append(hand.substr(i,1));
            unq_chars++;
        }
    }
    int max_count = 0;
    for (int i=0; i<unq_chars; i++){
        char search_c = seen_chars[i];
        max_count = max(max_count, (int)count(hand.begin(), hand.end(), search_c));
    }
#if PART_2
    int num_jokers = count(hand.begin(),hand.end(), 'J');
    if(num_jokers){
        unq_chars --;
        max_count += num_jokers;
    }
#endif
    if(unq_chars <= 1){
        return FIVE_OF_KIND;
    }else if (unq_chars == 2){
        // four of kind or full house
        if(max_count == 4){
            return FOUR_OF_KIND;
        }else{
            return FULL_HOUSE;
        }
    }else if (unq_chars == 3){
        // 3 of kind or 2 pair
        if(max_count >= 3){
            return THREE_OF_KIND;
        }else{
            return TWO_PAIR;
        }
    }else if (unq_chars == 4){
        return ONE_PAIR;
    }else if (unq_chars == 5){
        return HIGH_CARD;
    }
    return NO_TYPE;
}

hand_type find_best_joker(string hand, int char_opt){
    hand_type best_hand = NO_TYPE;
    if(count(hand.begin(),hand.end(), 'J')){
        hand.replace(hand.find('J'),1,&card_opts[char_opt],1);
        return max(max(max(max(max(max(max(max(max(max(max(find_best_joker(hand,0),
                        find_best_joker(hand,1)),
                        find_best_joker(hand,2)),
                        find_best_joker(hand,3)),
                        find_best_joker(hand,4)),
                        find_best_joker(hand,5)),
                        find_best_joker(hand,6)),
                        find_best_joker(hand,7)),
                        find_best_joker(hand,8)),
                        find_best_joker(hand,9)),
                        find_best_joker(hand,10)),
                        find_best_joker(hand,11));
    }else {
        return findType(hand);
    }
}

int card_to_int(char c){
    switch (c) {
    case 'A':
        return 14;
        break;
    case 'K':
        return 13
        ;break;
    case 'Q':
        return 12;
        break;
    case 'J':
#ifdef PART_2
        return 1;
        break;
#else
        return 11;
        break;
#endif
    case 'T':
        return 10;
        break;
    case '9':
        return 9;
        break;
    case '8':
        return 8;
        break;
    case '7':
        return 7;
        break;
    case '6':
        return 6;
        break;
    case '5':
        return 5;
        break;
    case '4':
        return 4;
        break;
    case '3':
        return 3;
        break;
    case '2':
        return 2;
        break;
    case '1':
        return 1;
        break; 
    }
    return -1;
}

bool compare_hands (hand h1, hand h2){
    // should return whether h2 beats h1
    if(h1.h_type < h2.h_type){
        return true;
    }else if( h1.h_type == h2.h_type){
        for(int i=0; i<5; i++){
            if(card_to_int(h1.cards[i]) < card_to_int(h2.cards[i])){
                return true;
            } else if(card_to_int(h1.cards[i]) > card_to_int(h2.cards[i])){
                return false;
            }
        }
    }
    return false;
}

int main(){
  string line;
  ifstream myfile (FILENAME);
  if (myfile.is_open())
  {
    for(int i=0; i<NUM_HANDS; i++){
        getline (myfile,line);
//        hand_type best_type = NO_TYPE;
//        string cards = line.substr(0,5);
//        for(int j=0; j<12; j++){
//            if( count(cards.begin(),cards.end(), 'J')){
//                best_type = max(find_best_joker(line.substr(0,5),j), best_type);
//            }
//        }
        hands[i] = hand(
            line.substr(0,5),
            stoi(line.substr(6)),
            findType(line.substr(0,5)));
    }
  }
  sort(hands.begin(),hands.end(),compare_hands);
  long long sum = 0;
  for(int i=0; i<NUM_HANDS; i++){
    sum += hands[i].bid * (i+1);
    printf("%s\t%d\t%d\t%lld\n",hands[i].cards.c_str(), hands[i].bid, hands[i].h_type, sum);
  }
  printf("SUM: %lld", sum);
}