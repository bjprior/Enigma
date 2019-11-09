#include<iostream>
#include"errors.hpp"

using namespace std;

void check_error(int error, char* file_name){

  switch(error){

  case 1:
    cerr<< "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    break;
    
  case 4:
    cerr <<"Non-numeric character in plugboard file " << file_name << endl;
    break;
    
  case 6:
    cerr <<"Incorrect number of parameters in plugboard file " << file_name << endl;
    break;
    
  case 10:
    cerr << "Insuffient number of mappings in reflector file " << file_name << endl;
      break;
  default:
    break;
  }
}
