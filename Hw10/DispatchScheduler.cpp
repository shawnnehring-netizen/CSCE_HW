#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include "Cities.h"
#include "LinkedList.h"

// TODO(student): implement the dispatch scheduler
int main() {
    std::string input = "";
    std::string city = "";
    std::cin >> input >> city;
    LinkedList list = LinkedList();
    while(input != "quit"){
        if(input == "push"){
            list.add(0,get_city_by_name(city));
        }
        else if(input == "pop"){
            list.remove(0);
        }
        else if(input == "add"){
            Node* head = list.get_head();
            if(head->value > get_city_by_name(city)){
                list.add(0,get_city_by_name(city));
            }
            for(unsigned int i = 1; i < list.size();i++){
                if(head->value < get_city_by_name(city) && get_city_by_name(city) < head->next->value){
                    list.add(i,get_city_by_name(city));
                }
                head = head->next;
            }
            if(head->value < get_city_by_name(city)){
                list.add(list.size(),get_city_by_name(city));
            }

        }
        else if(input == "remove"){
            
        }
        else if(input == "print"){
            
        }
        else if(input == "clear"){
            list.clear();
        }
        std::cin >> input;
    }
}
