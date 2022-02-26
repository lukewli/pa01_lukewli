#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"


using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }


  //Read each file
  CardBST A;
  while (getline (cardFile1, line) && (line.length() > 0)){
    string suit = line.substr(0,1);
    string rank = line.substr(2,2);
    A.insert(suit, rank);


  }
  cardFile1.close();

  CardBST B;
  while (getline (cardFile2, line) && (line.length() > 0)){
    string suit = line.substr(0,1);
    string rank = line.substr(2,2);
    B.insert(suit, rank);
  }
  cardFile2.close();

  A.playgame(B);
  
  return 0;
}
