#include <iostream>
#include "functions.h"

// returns the boolean value true if and only if 1,000 <= a <= b < 1,000,000,000,000
bool is_valid_range(long long a, long long b) {
	// TODO(student): return true if and only if 1,000 <= a <= b < 1,000,000,000,000
	return false;
}

// returns the 'p' if number is a plateau, 'b' if number is a basin, and 'n' if number is neither
char classify_geo_type(long long number) {
	// TODO(student): Initialize local variables

	// TODO(student): Determine whether number is a plateau: this is the key loop

	// TODO(student): Determine whether number is a basin
	//                If you get the logic for plateau right, minor tweaks can create the code for basins.

	// TODO(student): return the appropriate char, p for plateau, b for basin, n for neither
	return 'x';
}

// returns how many numbers in the range [a, b] are plateaus and basins
plateaus_and_basins count_pb_numbers(long long a, long long b) {
	int number_of_plateaus = 0;
	int number_of_basins = 0;

	// TODO(student): count plateaus and basins in the range [a,b]

	return {number_of_plateaus, number_of_basins};
}