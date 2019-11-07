/*#include<iostream>
#include<fstream>
#include"errors.h"
#include"enigma.hpp"

const int AMIN = 0, ZMAX = 25;

using namespace std;

int input_check(int number_of_files, char* file_name[]){

  if(number_of_files < 4)
    return 1;
  // cout << plugboard_check(file_name[1]);
  //cout << reflector_check(file_name[2]);
  //for (int i = 3; i <number_of_files-1; i++)
  //  cout << rotor_check(file_name[i]);
  cout << config_check(file_name[number_of_files-1],number_of_files);
  
  return 0;
  
}
int plugboard_check(char* file_name){

  int number, count=0, numbers[27];
  char peek; 
  fill(numbers, numbers +27, -11);
  ifstream in_stream;
 
  open_file(file_name,in_stream);

  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if (!is_numeric(static_cast<int>(peek)))
      return 4;
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(number > ZMAX || number < AMIN)
      return 3;
    for(int i =0; i <27; i++){
      if(number == numbers[i])
	return 5;
    }
    numbers[count] = number;
    count++;
    in_stream >> ws;
    peek = in_stream.peek();
      }
  if(count > 25 || count %2 != 0)
    return 6;

  in_stream.close();
  return 0;
  
}

int reflector_check(char* file_name){

  int number, count=0, numbers[27];
  char peek; 
  fill(numbers, numbers +27, -11);
  ifstream in_stream;
  
  open_file(file_name,in_stream);
  
  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if (!is_numeric(static_cast<int>(peek)))
      return 4;
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(number > ZMAX || number < AMIN)
      return 3;
    for(int i =0; i <27; i++){
      if(number == numbers[i])
	return 9;
    }
    numbers[count] = number;
    count++;
    in_stream >> ws;
    peek = in_stream.peek();
      }
  if(count != 26)
    return 10;
  in_stream.close();
  return 0;    
}

int rotor_check(char* file_name){

  int number, count=0, numbers[35], total =0;
  fill(numbers, numbers + 35, -11);
  char peek;
  ifstream in_stream;
  
  open_file(file_name,in_stream);
  
  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if (!is_numeric(static_cast<int>(peek)))
      return 4;
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(number > ZMAX || number < AMIN)
      return 3;
    if(count < 26){
      for(int i =0; i <26; i++){
	if(number == numbers[i])
	  return 7;
	if(i <25)
	  total += number;
      }
    }
    if(count >25){
      for(int i =26; i <35; i++){
	if(number == numbers[i])
	  return 7;
      }
    }
    numbers[count] = number;
    count ++;
    in_stream >> ws;
    peek = in_stream.peek();
  }
  in_stream.close();
  return 0;
}

int config_check(char* file_name, int number_of_files){

  int number, count=0, numbers[30];
  char peek; 
  fill(numbers, numbers +30, -11);
  ifstream in_stream;
  
  open_file(file_name,in_stream);

  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if (!is_numeric(static_cast<int>(peek)))
      return 4;
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(number > ZMAX || number < AMIN)
      return 3;
    count++;
    in_stream >>ws;
    peek = in_stream.peek();
  }
  if(count != number_of_files -4)
    return 8;
  
  in_stream.close();
  return 0;
}

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
*/
