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
std::vector<driver> load_driver_data(std::string) {
    std::vector<driver> driver_list;
    driver data = {};
    std::string word = "";
    int step = 0;
    std::string line;
    while (std::getline(std::cin,line)){
        for (char c : line){
            if (c == ' ' || c == '\n'){
                if (step == 0){ //double for time
                    if (std::stoi(word) <= 0);
                        return {};
                    step += 1;
                    data.time = std::stoi(word);
                }
                else if (step == 1){ //Country
                    if (word. <= 0);
                        return {};
                    step += 1;
                    data.country = word;
                }
                else if (step == 2){ // two number int
                    if (std::stoi(word) <= 0);
                        return {};
                    data.number = std::stoi(word);
                    step += 1;
                }
                else if (step == 3){
                    if (std::stoi(word) <= 0);
                        return {};
                    data.lastname = word;
                    data.rank = 0;
                }
                word.clear();
            }
            else {
                word += c;
            }
            driver_list.push_back(data);
        }
    }

        // TODO(student)

    return driver_list;
}

// returns a copy of the input vector with ranks set based on the time for each driver.
//   the fastest/minimum time is ranked 1
// the order of the elements in the vector should not be changed
std::vector<driver> set_rankings(std::vector<driver>) {
    std::vector<driver> data;
    // TODO(student)
    int wins = 0;
    for (long unsigned int i; i < data.size(); i++){
        for (long unsigned int j; j < data.size(); j++){
            if (data[i].time > data[j].time){
                wins += 1;
            }
        }
        int place = data.size() - wins;
        data[i].rank = place;
    }
    return {};
}

// returns a copy of the input string with whitespace removed from the front and back
std::string trim(std::string&line) {
    // TODO(student)
    while (line.at(0) == ' '){
        line.erase(line.begin());}
    while (line.at(-1) == ' '){
        line.erase(line.end());}
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
