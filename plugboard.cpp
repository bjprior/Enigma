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
 
  open_file(file_name,in_stream);

  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if(count > 26){
      cerr <<"Incorrect number of parameters in plugboard file ";
      cerr << file_name;
      return 6;
    }
    if(!is_numeric(static_cast<int>(peek))){
      cerr <<"Non-numeric character in plugboard file " << file_name << endl;
      return 4;
    }
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(index_check(number)){
      cerr <<"integer entered into the plugboard file "<< file_name;
      cerr  << " not in the 0-25 range" << endl;
      return 3;
    }
    for(int i =0; i <26; i++){
      if(number == numbers[i]){
	cerr << "incorrect plugboard configuration " << number;
	cerr << " cannot be mapped to" << number << endl;
	return 5;
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
    cerr << file_name;
    return 6;
  }
  number_of_pairs = count/2;
  in_stream.close();
  return 0;
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
