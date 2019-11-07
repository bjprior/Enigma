#include<iostream>
#include"rotors.hpp"
#include"helper.hpp"

using namespace std;

int Rotor::rotor_check(){

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
    if(index_check(number))
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
  in_stream.close();
  return 0;
}

void Rotor::rotate(){

    current_position += 1;

}

void Rotor::rotor_set(){

  int temp[1][2];

  temp[0][0] = mapping[0][0];
  temp[0][1] = mapping[0][1];

  for(int i = 0; i <25; i++){
    mapping[i][0] = mapping[i+1][0];
    mapping[i][1] = mapping[i+1][1];
  }

  mapping[25][0] = temp[0][0];
  mapping[25][1] = temp[0][1];
}
    

int Rotor::rotor_fwd_map(int target){

  //// cout << endl << "current "<<current_position << " start " << starting_position << endl;
  int output,rel_pos; //rel_pos is current position - starting position 
  int ent_pos; //the position the char enters the rotor
  ////cout << "current " << current_position << " start  " << starting_position << endl;
  ent_pos = (current_position+target)%26;
    
  ////cout <<" ent " << ent_pos;
  rel_pos = (current_position)%26;
  ////cout << " rel " << rel_pos << endl;
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
    if (!is_numeric(static_cast<int>(peek)))
      return 4;
    else{
      in_stream >> ws;
      in_stream >> number;
    }
    if(index_check(number))
      return 3;
    positions[count] = number;
    count++;
    in_stream >>ws;
    peek = in_stream.peek();
  }
  if(count != number_of_files -4)
    return 8;
  
  in_stream.close();
  return 0;
}

bool notch_check(Rotor rotor, int position){

  for(int i = 0; i < rotor.number_of_notches; i++){
    if(rotor.notch[i]==position)
      return true;
  }
  return false;

}
  
