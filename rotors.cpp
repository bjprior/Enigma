#include<iostream>
#include"rotors.hpp"
#include"helper.hpp"
#include"errors.hpp"

using namespace std;

int Rotor::rotor_check(){

  int number, count=0, numbers[35], total =0;
  fill(numbers, numbers + 35, -11);
  char peek;
  ifstream in_stream;

  if(open_file(file_name,in_stream)!=0)
    return ERROR_OPENING_CONFIGURATION_FILE;
  
  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if (!is_numeric(static_cast<int>(peek))){
      cerr <<"Non-numeric character for mapping in rotor file " << file_name << endl;
      return NON_NUMERIC_CHARACTER;
    }
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(index_check(number)){
      cerr <<"integer entered into the rotor file "<< file_name;
      cerr  << " not in the 0-25 range" << endl;
      return INVALID_INDEX;
    }
    if(count < 26){
      for(int i =0; i <26; i++){
	if(number == numbers[i]){
	  cerr <<" Invalid mapping of input " << count << " to output " << number;
	  cerr <<" (output " << number << " is already mapped to from input ";
	  cerr << i << ") in rotor file "<< file_name << endl;
	  return INVALID_ROTOR_MAPPING;
	}
	if(i <25)
	  total += number;
      }
    }
    if(count >25){
      for(int i =26; i <35; i++){
	if(number == numbers[i])
	  return INVALID_ROTOR_MAPPING;
      }
    }
    numbers[count] = number;
    if(count < 26){
    mapping[count][0] = number;
    mapping[count][1] = count;
    }
    if(count >25)
      notch[count- 26] = number;
    number_of_notches = count -25;
    count ++;
    in_stream >> ws;
    peek = in_stream.peek();
  }
  if(count < 25){
    cerr << "Not all inputs mapped in rotor file: " << file_name <<endl;
    return INVALID_ROTOR_MAPPING;
  }
  in_stream.close();
  return NO_ERROR;
}

void Rotor::rotate(){

    current_position += 1;

}
  
int Rotor::rotor_fwd_map(int target){


  int output,rel_pos; //rel_pos is current position - starting position 
  int ent_pos; //the position the char enters the rotor

  ent_pos = (current_position+target)%26;
  rel_pos = (current_position)%26;

  output = mapping[ent_pos][0]-rel_pos;
  if(output < 0)
    output+=26;
  
  return output;
}

int Rotor::rotor_bwd_map(int target){

  int output=0, rel_pos = 0;

  for(int i = 0; i < 26; i++){
    rel_pos = current_position%26;
    if((target+rel_pos)%26 == mapping[i][0]){
      output = i - rel_pos;
      if(output < 0)
	output +=26;
      return output;
    }
  }
      return 0;
}

int config_check(char* file_name, int number_of_files, int positions[]){

  int number, count=0, numbers[30]; 
  char peek; 
  fill(numbers, numbers +30, -11);
  ifstream in_stream;
  
  open_file(file_name,in_stream);

  in_stream >>ws;
  peek = in_stream.peek();
  while(!in_stream.eof()){
    if(!is_numeric(static_cast<int>(peek))){
      cerr <<"Non-numeric character in rotor positions file " << file_name << endl;
      return NON_NUMERIC_CHARACTER;
    }
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(index_check(number)){
      cerr <<"integer entered into the rotor position file "<< file_name;
      cerr  << " not in the 0-25 range" << endl;
      return INVALID_INDEX;
    }
    positions[count] = number;
    count++;
    in_stream >>ws;
    peek = in_stream.peek();
  }
  if(count < number_of_files -4){
    cerr << "No starting position for rotor " << count;
    cerr << " in rotor position file: "<<file_name << endl;
    return NO_ROTOR_STARTING_POSITION;
  }
  in_stream.close();
  return NO_ERROR;
}

bool notch_check(Rotor rotor, int position){
  
  for(int i = 0; i < rotor.number_of_notches; i++){
    if(rotor.notch[i]==(position%26))
      return true;
  }
  return false;

}
  
