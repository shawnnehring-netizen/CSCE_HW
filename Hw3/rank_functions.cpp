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
std::vector<driver> load_driver_data() {
    // TODO(student)
    std::vector<driver> driver_list;
    driver data = {};
    std::string word = "";
    int step = 0;
    std::string line;
    int dub_spa = 0;
    while (std::getline(std::cin,line)){
        //std::cout << line << std::endl;
        for (char c : line){
            if (c == ' ' && c != '.' && dub_spa == 0){
                if (step == 3) break;
                if (step == 0){ //double for time
                    if (std::stod(word) <= 0){
                        return {};}
                    step += 1;
                    data.time = std::stod(word);
                    //std::cout << std::stod(word) << std::endl;
                }
                else if (step == 1){ //Country
                    if (word.length() != 3){
                        return {};}
                    for (char j : word){
                        if (std::isupper(j) == 0) {
                            return {};
                        }
                    }
                    step += 1;
                    data.country = word;
                    //std::cout << word << std::endl;
                }
                else if (step == 2){ // two number int
                    if (std::stoi(word) < 0 || std::stoi(word) > 99){
                        return {};}
                    data.number = std::stoi(word);
                    //std::cout << std::stoi(word) << std::endl;
                    step += 1;
                }
                word.clear();
                dub_spa = 1;
            }
            else if (c != ' '){
                word += c;
                dub_spa = 0;
            }
        }
        data.lastname = word;
        if (word.length() < 2){
            return {};
        }
        for (char j : word){
            if (std::isalpha(j) == 0) {
                return {};
            }
        }
        //std::cout << word << std::endl;
        data.rank = 0;
        word.clear();
        step = 0;
        driver_list.push_back(data);
        //std::cout << data.time << ' ' << data.country << ' ' << data.lastname << ' ' << data.number<< std::endl;
    }

        // TODO(student)

    return driver_list;
}



// returns a copy of the input vector with ranks set based on the time for each driver.
//   the fastest/minimum time is ranked 1
// the order of the elements in the vector should not be changed
std::vector<driver> set_rankings(std::vector<driver>data) {
    // TODO(student)
    //std::cout << data[1].time;
    // TODO(student)
    int wins = 0;
    for (long unsigned int i=0; i < data.size(); i++){
        //std::cout << i << std::endl;
        for (long unsigned int j=0; j < data.size(); j++){
            if (data[i].time < data[j].time){
                wins += 1;
            }
            //std::cout << j << std::endl;
        }
        int place = data.size() - wins;
        data[i].rank = place;
        //std::cout << data[i].time << ' ' << data[i].country << ' ' << data[i].lastname << ' ' << data[i].number << ' ' << data[i].rank << std::endl;
        wins = 0;
    }
    return data;
}

// returns a copy of the input string with whitespace removed from the front and back
std::string trim(std::string line) {
    if (line.length() == 0) return "";
    while (line.at(0) == ' '){
        //std::cout << line.at(0) << "here" << std::endl;
        line.erase(line.begin()+0);
        if (line.length() == 0) return "";}
    while (line.at(line.length()-1) == ' '){
        //std::cout << line.at(line.length()-1) << "here" << std::endl;
        line.erase(line.length()-1);}
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
