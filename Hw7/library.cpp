#include <iostream>
#include <sstream>
#include "library.h"
#include "lms_utilities.h"

void Library::add_book(Book) {
   // TODO(student)
}

void Library::register_member(Member) {
   // TODO(student)
}

bool Library::borrow_book(const std::string& , int, std::string&) {
   // TODO(student)
   return false;
}

bool Library::return_book(const std::string&, std::string&) {
   // TODO(student)
   return false;
}

void Library::display_available_books(std::ostream&) {
   // TODO(student)
   // use the ostream parameter, NOT std::cout
}

void Library::display_library_members(std::ostream&) {
   // TODO(student)
   // use the ostream parameter, NOT std::cout
}

bool Library::is_book_available(const std::string&) {
   // TODO(student)
   return false;
}
