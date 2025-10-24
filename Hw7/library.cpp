#include <iostream>
#include <sstream>
#include "library.h"
#include "lms_utilities.h"

void Library::add_book(Book boo) {
   // TODO(student)
   books.push_back(boo);
}

void Library::register_member(Member mem) {
   // TODO(student)
   members.push_back(mem);
}

bool Library::borrow_book(const std::string& isbn, int id, std::string& msg) {
   // TODO(student)
   bool isbn_check = false;
   bool id_check = false;
   Book this_book = books[0];
   for (long unsigned int i = 0 ; i < books.size();i++){
      if (isbn == books[i].get_isbn()){
         if (books[i].is_available()){
            isbn_check = true;
            this_book = books[i];
         }
         break;
      }
   }
   if (!isbn_check){
      std::cout << "Book ISBN: " << isbn << " not available"<< std::endl;
      return false;
   }
   for (long unsigned int i = 0 ; i < members.size();i++){
      if (id == members[i].get_id()){
         id_check = true;
      }
   }
   if (!id_check){
      std::cout << "Member " << id << " not found"<< std::endl;
      return false;
   }
   std::cout << msg;
   this_book.borrow_book();
   return true;
}

bool Library::return_book(const std::string& isbn, std::string& msg) {
   // TODO(student)
   bool isbn_check = false;
   bool return_check = false;
   Book this_book = books[0];
   for (long unsigned int i = 0 ; i < books.size();i++){
      if (isbn == books[i].get_isbn()){
         isbn_check = true;
         this_book = books[i];
         if (!(books[i].is_available())){
            return_check = true;
         }
         break;
      }
   }
   if (!(isbn_check || return_check)){
      std::cout << msg;
      return false;
   }
   std::cout << "Book \"" << this_book.get_title() << "\" returned" << std::endl;
   this_book.return_book();
   return true;
}

void Library::display_available_books(std::ostream& os) {
   // TODO(student)
   // use the ostream parameter, NOT std::cout
   for (long unsigned int i = 0 ; i < books.size();i++){
      os << books[i] << "\n";
   }

}

void Library::display_library_members(std::ostream& os) {
   // TODO(student)
   // use the ostream parameter, NOT std::cout
   for (long unsigned int i = 0 ; i < members.size();i++){
      os << members[i] << "\n";
   }
}

bool Library::is_book_available(const std::string& isbn) {
   // TODO(student)
   bool isbn_check = false;
   bool return_check = false;
   for (long unsigned int i = 0 ; i < books.size();i++){
      if (isbn == books[i].get_isbn()){
         isbn_check = true;
         Book this_book = books[i];
         if (!(books[i].is_available())){
            return_check = true;
         }
         break;
      }
   }
   if (!(isbn_check && return_check)){
      return false;
   }
   return true;
}
