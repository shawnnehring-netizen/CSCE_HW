#include "member.h"

Member::Member(std::string,  // firstName
               std::string,  // last_name
               int           // id
            ) : name{}, id{} {
    // TODO(student)
    std::string full_name = name.first_name + name.last_name;
    if (full_name.size() == 0){
        throw std::invalid_argument("Invalid name");
    }
    for (long unsigned int i = 0; i < full_name.size(); i++){
        if (!(std::isalpha(full_name[i]))){
            throw std::invalid_argument("Invalid name");
        }
    }
    if (id < 1000){
        throw std::invalid_argument("Invalid id");
    }
}

Member::Member(MemberName,  // name
               int          // id
               ) : name{}, id{} {
    // TODO(student)
    std::string full_name = name.first_name + name.last_name;
    if (full_name.size() == 0){
        throw std::invalid_argument("Invalid name");
    }
    for (long unsigned int i = 0; i < full_name.size(); i++){
        if (!(std::isalpha(full_name[i]))){
            throw std::invalid_argument("Invalid name");
        }
    }
    if (id < 1000){
        throw std::invalid_argument("Invalid id");
    }
}

MemberName Member::get_name() const {
    // TODO(student)
    return name;
}

int Member::get_id() const {
    // TODO(student)
    return id;
}

std::ostream& operator<<(std::ostream& os, const Member& mem) {
   // TODO(student)
   MemberName name = mem.get_name();
   int id = mem.get_id();
   std::string full_name = name.first_name + ' ' + name.last_name;
   std::cout << "Member: " << full_name << ", id: " << id;
   return os;
}
