#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;
const string FILENAME = "puzzle1.input.txt";

int main () {
  string line;
  ifstream myfile (FILENAME);
  int sum = 0;
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      //cout << line << '\n';
      string digits = regex_replace(line, regex("(\\D)"), "");
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