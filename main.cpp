#include<iostream>
#include"errors.hpp"
#include"plugboard.hpp"
#include"reflector.hpp"
#include"rotors.hpp"

using namespace std;


int main(int argc, char* argv[]){
  
  int number_of_rotors = 0, rotor_num =0, error = 0;
  int starting_position[argc-4] = {};
  int input_int =0;
  char input_char;
  Plugboard plug;
  Reflector reflector;
  Rotor rotor[argc - 4];

  number_of_rotors = argc -4;

  plug.file_name = argv[1];

  error = plug.plugboard_check();
  if(error != 0){
    check_error(error,argv[1]);
    return error;
  }
  
  reflector.file_name = argv[2];
  error = reflector.reflector_check();
  if(error != 0){
    check_error(error,argv[2]);
    return error;
  }
 
  /* assign values to rotor */
  for(int i = argc - 4; i < argc -4 + number_of_rotors; i++){
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
    
  /*for(int i = 0; i < number_of_rotors; i++){
    cout << "Rotor " << i << " Starting Position" << rotor[i].starting_position << endl;
    }*/

  // Passing values through the engima machine // 
  while(cin >> ws >>input_char && input_char <= 'Z' && input_char >='A' ){
    input_int = static_cast<int>(input_char)-65;

    // Pass through plugboard //
    input_int = plug.plug_map(input_int);
    

    // Rotate rotors //

    //rotate rotor N //

    if(number_of_rotors > 0)
      rotor[number_of_rotors -1].rotate();

    //rotate other rotors //
    for(int k = 0; k < number_of_rotors -1; k++){
      if(notch_check(rotor[k+1],rotor[k+1].current_position))
	rotor[k].rotate();
    }

    // Pass through rotors right to left//
    for(int j =number_of_rotors-1; j >-1; j--){
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
  } 
  
  return 0;
}
