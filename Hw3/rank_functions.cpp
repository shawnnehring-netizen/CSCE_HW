#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "rank_functions.h"

// load data from standard input into a vector
//   input format := <time> <country> <number> <name>
//   examples:
//     32.7 AUS 81 Piastri
//     36.5 NED 1  Verstappen
//   rank should be initialized to 0 for each driver
// returns a vector of drivers, or an empty vector if any input is invalid
std::vector<driver> load_driver_data(std::string&line) {
    std::vector<driver> data;
    std::string word = "";
    for (char c : line){
            if (c == ' ' || c == '\n'){
                data.insert(data.begin(),word);
                word.clear();
            }
            else {
                word += c;
            }
    }

    // TODO(student)
    return driver;
}

// returns a copy of the input vector with ranks set based on the time for each driver.
//   the fastest/minimum time is ranked 1
// the order of the elements in the vector should not be changed
std::vector<driver> set_rankings(std::vector<driver>) {
    // TODO(student)
    int wins = 0;
    for (int i; i < driver.length(); i++){
        for (int j; j < driver.length(); j++){
            if (driver[i][3] > driver[j][3]){
                wins += 1;
            }
        }
        int rank = driver.length() - wins;
        driver[i].push_back(rank);
    }
    return {};
}

// returns a copy of the input string with whitespace removed from the front and back
std::string trim(std::string&line) {
    // TODO(student)
    line.erase(0,line.size(),' ')
    return line;
}

// print the results of the race
void print_results(const std::vector<driver>& drivers) {
    // get the fastest time
    double best_time;
    for (const driver& driver : drivers) {
        if (driver.rank == 1) {
            best_time = driver.time;
            break;
        }
    }

    std::cout << "Final results!";
    std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
    for (unsigned rank = 1; rank <= drivers.size(); rank++) {
        for (const driver& driver : drivers) {
            if (driver.rank == rank) {
                std::string rank_str = "["+std::to_string(rank)+"]";
                std::cout << std::setw(4) << std::left << rank_str << " " << driver.time << " " << std::setw(15) << std::left << driver.lastname << " (" << driver.country << ") +" << (driver.time - best_time) << std::endl;
            }
        }
    }
}
