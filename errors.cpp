#include<iostream>
#include"errors.hpp"

using namespace std;

void check_error(int error, char* file_name){

  switch(error){

  case 1:
    cerr<< "Usage enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    break;
  case 4:
    cerr <<"Non-numeric character in plugboard file " << file_name << endl;
    break;

  default:
    break;
  }
}
