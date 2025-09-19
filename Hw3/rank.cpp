#include <iostream>
#include "rank_functions.h"

int main() {
    // TODO(student): create and load driver data into a vector of drivers using load_driver_data()
    std::vector<driver> driver_list;
    driver_list = load_driver_data();
    if (driver_list.size() == 0){
        std::cout<< "Bad input" << std::endl;
        return 1;

    }
    // TODO(student): if loading driver data failed,
    //                1) print "Bad input" to standard output
    //                2) exit the program by returning 1

    // TODO(student): set the rankings of the drivers using set_rankings()
    driver_list = set_rankings(driver_list);
    //for (auto i: driver_list){
        //std::cout << i.time << ' ' << i.country << ' ' << i.lastname << ' ' << i.number<< std::endl;}
    // TODO(student): print the results using print_results()
    print_results(driver_list);
    return 0;
}
