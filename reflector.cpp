#include<iostream>
#include<fstream>
#include"errors.hpp"
#include"helper.hpp"
#include"reflector.hpp"

using namespace std;

int Reflector::reflector_check(){

  int number, count=0, numbers[27];
  char peek; 
  fill(numbers, numbers +27, -11);
  ifstream in_stream;
  
  open_file(file_name,in_stream);
  
  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if(!is_numeric(static_cast<int>(peek))){
      cerr <<"Non-numeric character in reflector file " << file_name << endl;
      return 4;
    }
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(index_check(number)){
      cerr <<"integer entered into the reflector file "<< file_name;
      cerr  << " not in the 0-25 range" << endl;
      return 3;
    }
    for(int i =0; i <27; i++){
      if(number == numbers[i]){
	cerr << "incorrect reflector configuration " << number;
	cerr << " cannot be mapped to" << number << endl;
	return 9;
      }
    }
    numbers[count] = number;
    pairs[count/2][count%2] = number;
    count++;
    in_stream >> ws;
    peek = in_stream.peek();
  }
  if(count < 26 && count%2==0){
    cerr <<"Insufficient number of mappings in reflector file ";
    cerr << file_name << endl;
    return 10;
  }
  if(count%2!=0){
    cerr <<"Incorrect (odd) number of parameters in reflector file ";
    cerr << file_name << endl;
    return 10;
  }
  if(count >26){
    cerr <<"Too many mappings in reflector file " << file_name << endl;
  }
  in_stream.close();
  return 0;    
}

int Reflector::reflector_map(int target){

  int output;
  for(int i = 0; i < 13; i++){
    for(int j = 0; j < 2; j++){
      if(target == pairs[i][j]){
	if(j == 0)
	  output = pairs[i][1];
	else
	  output = pairs[i][0];
	return output;
      }
    }
  }
 return -1;
}
