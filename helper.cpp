#include<iostream>
#include<fstream>
#include"errors.hpp"
#include"helper.hpp"

const int AMIN = 0, ZMAX = 25;

using namespace std;

bool is_numeric(int test_digit){

  bool outcome;

  if(test_digit >47 && test_digit < 58 )
    outcome = true;
  else
    outcome = false;
  return(outcome);
}
	
int open_file(char* file_name, ifstream &instream){
  
  instream.open(file_name);
  if (instream.fail()){
    cout << "Sorry this file couldn't be opened";
    return 11;
  }
  return 0;
}
	
bool index_check(int number){

  return(number > ZMAX || number < AMIN);
}




