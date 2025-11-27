#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include "Cities.h"
#include "LinkedList.h"

// TODO(student): implement the dispatch scheduler
int main() {
    std::string input = "";
    std::cin >> input;
    LinkedList list = LinkedList();
    while(input != "quit"){
        if(input == "push"){
            list.add(0,0);
        }
        else if(input == "pop"){

        }
        else if(input == "add"){
            
        }
        else if(input == "remove"){
            
        }
        else if(input == "print"){
            
        }
        else if(input == "clear"){
            
        }
        std::cin >> input;
    }
}
