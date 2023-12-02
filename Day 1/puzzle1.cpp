#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
const string FILENAME = "puzzle1.input.txt";

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int main () {
  string line;
  ifstream myfile (FILENAME);
  int sum = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
      string short_line;
        for (int i = 1; i <= line.length(); i++){
            short_line += line.substr(i-1,1);
            replace(short_line, "one", "o1e");
            replace(short_line, "two", "t2o");
            replace(short_line, "three", "t3e");
            replace(short_line, "four", "f4r");
            replace(short_line, "five", "f5e");
            replace(short_line, "six", "s6x");
            replace(short_line, "seven", "s7n");
            replace(short_line, "eight", "e8t");
            replace(short_line, "nine", "n9e");
            //replace(short_line, "zero", "0");

        }
      cout << short_line << endl;
      string digits = regex_replace(short_line, regex("(\\D)"), "");
      string first_digit = digits.substr(0,1);
      //cout << first_digit;
      string last_digit = digits.substr(digits.length()-1, 1);
      //cout << last_digit << endl;
      cout << stoi(first_digit + last_digit) << endl;
      sum += stoi(first_digit + last_digit);
      cout << "SUM: " << sum << endl;
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  return 0;
}