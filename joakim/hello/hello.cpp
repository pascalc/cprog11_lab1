#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	// Base case, no arguments sent
	if(argc == 1) {
		cout << "Hello world!\n";
		return 0;
	}

	// Default values
	int repeat = 1;
	char* second_string = "world";

	repeat = atoi (argv[1]);
	if(repeat == 0) {
		second_string = argv[1];
		repeat = 1;
	}
	

	if(argc == 3) {
		second_string = argv[2];		
	}
	
	cout << "Hello";
	for(int i = 0; i < repeat; i++) {
		cout << " " << second_string;
	}
	cout << "!" << endl;

	return 0;
}
