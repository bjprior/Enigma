enigma: main.o helper.o plugboard.o reflector.o rotors.o
	g++ main.o helper.o plugboard.o reflector.o rotors.o -o enigma

main.o: main.cpp helper.hpp plugboard.hpp
	g++ -g -c -Wall main.cpp

plugboard.o: plugboard.cpp helper.hpp plugboard.hpp
	g++ -g -c -Wall plugboard.cpp

reflector.o: reflector.cpp helper.hpp reflector.hpp
	g++ -g -c -Wall reflector.cpp

rotors.o: rotors.cpp helper.hpp rotors.hpp
	g++ -g -c -Wall rotors.cpp

helper.o:
	g++ -g -c -Wall helper.cpp

clean:
	rm -f *.o enigma
