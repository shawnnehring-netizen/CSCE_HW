#include <iostream>
#include "functions.h"

// returns the boolean value true if and only if 1,000 <= a <= b < 1000000000000
bool is_valid_range(long long a, long long b) {
	// TODO(student): return true if and only if 1,000 <= a <= b < 1000000000000
	if (1000 <= a && a < 1000000000000  && 1000 <= b && b < 1000000000000){
		return true;     
	}
	else{
		return false;	
	}
	
}

// returns the 'p' if number is a plateau, 'b' if number is a basin, and 'n' if number is neither
char classify_geo_type(long long number) {
	// TODO(student): Initialize local variables
	int old_rem = number % 10;
	int step_plat = 0;
	int step_bas = 0;
	char value = 'n';
	// TODO(student): Determine whether number is a plateau: this is the key loop
	while (number != 0 && step_plat == 2){
		number = number / 10;
		if (number == 0){
			std::cout << 'p';
			value = 'p';
		}
		int rem = number % 10;
		//std::cout << old_rem << ' ' << rem << ' ';
		if (rem > old_rem && (step_plat == 0 || step_plat == 1)){
			step_plat = 1;
			old_rem = rem;
			//std::cout << "increase" << std::endl;
			continue;}
		else if (rem == old_rem && (step_plat == 1 || step_plat == 2)){
			step_plat = 2;
			old_rem = rem;
			//std::cout << "stay" << std::endl;
			continue;}
		else if (rem < old_rem && (step_plat == 2 || step_plat == 3)){
			step_plat = 3;
			old_rem = rem;
			//std::cout << "decrease" << std::endl;
			continue;}
		else{
			//std::cout << "done";
			break;}

	}

	// TODO(student): Determine whether number is a basin
	//                If you get the logic for plateau right, minor tweaks can create the code for basins.
	while (number != 0){
		number = number / 10;
		if (number == 0 && step_bas == 2){
			value = 'b';
		}
		int rem = number % 10;
		//std::cout << old_rem << ' ' << rem << ' ';
		if (rem < old_rem && (step_bas == 0 || step_bas == 1)){
			step_bas = 1;
			//std::cout << "decrease" << std::endl;
			old_rem = rem;
			continue;}
		else if (rem == old_rem && (step_bas == 1 || step_bas == 2)){
			step_bas = 2;
			//std::cout << "stay" << std::endl;
			old_rem = rem;
			continue;}
		else if (rem > old_rem && (step_bas == 2 || step_bas == 3)){
			step_bas = 3;
			//std::cout << "increase" << std::endl;
			old_rem = rem;
			continue;}
		else{
			//std::cout << "done";
			break;}

	}
	// TODO(student): return the appropriate char, p for plateau, b for basin, n for neither
	//std::cout << value;
	return value;
}

// returns how many numbers in the range [a, b] are plateaus and basins
plateaus_and_basins count_pb_numbers(long long a, long long b) {
	int number_of_plateaus = 0;
	int number_of_basins = 0;

	// TODO(student): count plateaus and basins in the range [a,b]
	long long i;
	char value;
	for (i=a;i<=b;i++){
		//std::cout << i;
		value = classify_geo_type(i);
		if (value == 'p'){
			number_of_plateaus += 1;
		}
		else if (value == 'b'){
			number_of_basins += 1;
		}
		break;
	}
	return {number_of_plateaus, number_of_basins};
}