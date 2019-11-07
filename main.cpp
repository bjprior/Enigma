#include<iostream>
#include"errors.h"
#include"enigma.hpp"
#include"plugboard.hpp"
#include"reflector.hpp"
#include"rotors.hpp"

using namespace std;


int main(int argc, char* argv[]){
  
  int number_of_rotors = 0, rotor_num =0;
  int starting_position[argc-4] = {};
  int input_int =0;
  char input_char;
  Plugboard plug;
  Reflector reflector;
  Rotor rotor[argc - 4];

  number_of_rotors = argc -4;
  
  plug.file_name = argv[1];
  plug.plugboard_check();
  
  reflector.file_name = argv[2];
  reflector.reflector_check();

  /* assign values to rotor */
  
  for(int i = argc - 4; i < argc -1; i++){
    rotor[rotor_num].file_name=argv[i];
    rotor[rotor_num].rotor_check();
    rotor_num++;
  }

  /*Assign the starting position to rotor*/
  config_check(argv[argc-1],argc,starting_position);
  for (int i =0; i < number_of_rotors; i++){
    rotor[i].starting_position = starting_position[i];
    rotor[i].current_position = rotor[i].starting_position;
  }

  cin >> ws >> input_char;
  while(!cin.eof()){
    input_int = static_cast<int>(input_char)-65;
    // Pass through plugboard //
    input_int = plug.plug_map(input_int);
    
    // Pass through rotors right to left//
    for(int j =number_of_rotors-1; j >-1; j--){
      //rotate rotor 1 //
      if(j == number_of_rotors-1)
	rotor[j].rotate();
      //rotate other rotors //
      for(int k = number_of_rotors -2; k > -1; k--){
	if(notch_check(rotor[k+1],rotor[k+1].current_position))
	  rotor[k].rotate();
      }
      input_int = rotor[j].rotor_fwd_map(input_int);
    }
    
    // Pass through reflector //
    input_int = reflector.reflector_map(input_int);


      // Pass back through rotors //
    for(int j = 0; j < number_of_rotors; j++){
      input_int = rotor[j].rotor_bwd_map(input_int);
    }
    
    // Pass through plugboard //
    input_int = plug.plug_map(input_int);
    input_char = static_cast<char>(input_int+65);
    cout << input_char;
	    cin >> ws >> input_char;	      
  } 
  
  return 0;
}
