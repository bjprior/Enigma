#include<iostream>
#include<fstream>
#include"errors.hpp"
#include"plugboard.hpp"
#include"helper.hpp"

using namespace std;

int Plugboard::plugboard_check(){

  int number, count=0, numbers[29];
  char peek; 
  fill(numbers, numbers +29, -11);
  ifstream in_stream;
 
  if(open_file(file_name,in_stream)!=0)
    return ERROR_OPENING_CONFIGURATION_FILE;
  
  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if(count > 25){
      cerr <<"Incorrect number of parameters in plugboard file ";
      cerr << file_name << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    if(!is_numeric(static_cast<int>(peek))){
      cerr <<"Non-numeric character in plugboard file " << file_name << endl;
      return NON_NUMERIC_CHARACTER;
    }
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(index_check(number)){
      cerr <<"integer entered into the plugboard file "<< file_name;
      cerr  << " not in the 0-25 range" << endl;
      return INVALID_INDEX;
    }
    for(int i =0; i <26; i++){
      if(number == numbers[i]){
	cerr << "incorrect plugboard configuration " << number;
	cerr << " cannot be mapped to" << number << endl;
	return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }
    numbers[count] = number;
    pair[count/2][count%2] = number;
    count++;
    in_stream >> ws;
    peek = in_stream.peek();
  }
  if(count %2 != 0){
    cerr <<"Incorrect number of parameters in plugboard file ";
    cerr << file_name << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  number_of_pairs = count/2;
  in_stream.close();
  return NO_ERROR;
}

int Plugboard::plug_map(int target){

  int output;
  for(int i = 0; i < number_of_pairs; i++){
    for(int j = 0; j < 2; j++){
      if(target == pair[i][j]){
	if(j == 0)
	  output = pair[i][1];
	else
	  output = pair[i][0];
	return output;
      }
    }
  }
  
  return target;
}
