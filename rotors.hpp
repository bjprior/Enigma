
class Rotor{
public:
  int starting_position;
  int current_position;
  int mapping[26][2];
  int notch[26];
  int number_of_notches;
  char* file_name;
  int rotor_check();
  void rotate();
  //void rotor_set();
  int rotor_fwd_map(int target);
  int rotor_bwd_map(int target);
};

// check the congif of the starting positions of rotors //

int config_check(char* file_name, int number_of_files, int positions[]);

// check if a rotor should rotate returns true if that is the case//

bool notch_check(Rotor rotor, int position);
