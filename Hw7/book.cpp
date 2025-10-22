#include "book.h"

Book::Book(std::string,  // title
           std::string,  // author_first_name
           std::string,  // author_last_name
           std::string,  // isbn
           bool          // available
         ) : title{}, author{}, isbn{}, available{} {
   // TODO(student)
}

Book::Book(std::string,  // title
           AuthorName,   // author
           std::string,  // isbn
           bool          // available
         ) : title{}, author{}, isbn{}, available{} {
   // TODO(student)
}

std::string Book::get_title() const {
   // TODO(student)
   return "";
}

AuthorName Book::get_author() const {
   // TODO(student)
   return {};
}

std::string Book::get_isbn() const {
   // TODO(student)
   return "";
}

bool Book::is_available() const {
   // TODO(student)
   return false;
}

bool Book::borrow_book() {
   // TODO(student)
   return false;
}

bool Book::return_book() {
   // TODO(student)
   return false;
}

std::ostream& operator<<(std::ostream& os, const Book&) {
   // TODO(student)
   return os;
}
