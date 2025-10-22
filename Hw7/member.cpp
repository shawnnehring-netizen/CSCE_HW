#include "member.h"

Member::Member(std::string,  // firstName
               std::string,  // last_name
               int           // id
            ) : name{}, id{} {
    // TODO(student)
}

Member::Member(MemberName,  // name
               int          // id
               ) : name{}, id{} {
    // TODO(student)
}

MemberName Member::get_name() const {
    // TODO(student)
    return {};
}

int Member::get_id() const {
    // TODO(student)
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Member&) {
   // TODO(student)
   return os;
}
