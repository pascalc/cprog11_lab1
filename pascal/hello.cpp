#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	// Special, simple, case
	if (argc == 1) {
		cout << "Hello world!" << endl;
		return 0;
	}
	
	// Default values
	int reps = 1;
	char* second_string = "world";

	// The first argument is either the number of
	// repetitions or the string after 'hello'
	int first_arg_int = atoi(argv[1]);
	if (first_arg_int) {
		reps = first_arg_int;
	} else {
		second_string = argv[1];
	}
	
	// If we have a second argument, it is always
	// the string after 'hello'
	if (argc == 3) {
		second_string = argv[2];
	}
	
	// Print output
	cout << "Hello";
	for(int i = 0; i < reps; i++) {
		cout << " " << second_string;
	} 
	cout << "!" << endl;
	return 0;
}