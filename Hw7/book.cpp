#include "book.h"
//cd Hw7
//ls book.cpp book.h library.cpp library.h lms_utilities.cpp lms_utilities.h main.cpp member.cpp member.h
//g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g *.cpp
Book::Book(std::string,  // title
           std::string,  // author_first_name
           std::string,  // author_last_name
           std::string,  // isbn
           bool          // available
         ) : title{}, author{}, isbn{}, available{} {
   std::string author_name = author.first_name + author.last_name;
   if (author_name.size() == 0){
      throw std::invalid_argument("Invalid title");
   }
   for (long unsigned int i = 0; i < author_name.size(); i++){
      if (!(std::isalpha(author_name[i]) && !(author_name[i] = '-') && !(author_name[i] = ' ') && !(author_name[i] = ':'))){
         throw std::invalid_argument("Invalid author");
      }
   }
   for (long unsigned int i = 0; i < author.last_name.size(); i++){
      if (!(std::isalpha(author.last_name[i]) && !(author.last_name[i] = '-') && !(author.last_name[i] = ' ') && !(author.last_name[i] = ':'))){
         throw std::invalid_argument("Invalid author");
      }
   }
   if (title.size() == 0){
      throw std::invalid_argument("Invalid title");
   }
   for (long unsigned int i = 0; i < title.size(); i++){
      if (!(std::isalpha(title[i]))){
         throw std::invalid_argument("Invalid title");
      }
   }
   if (!(isbn.size() == 10 || isbn.size() == 13) && !(typeid(isbn).name() == typeid("").name())){
      throw std::invalid_argument("Invaldi ISBN");
   }

   // TODO(student)
}

Book::Book(std::string,  // title
           AuthorName,   // author
           std::string,  // isbn
           bool          // available
         ) : title{}, author{}, isbn{}, available{} {
   // TODO(student)
   std::string author_name = author.first_name + author.last_name;
   if (author_name.size() == 0){
      throw std::invalid_argument("Invalid title");
   }
   for (long unsigned int i = 0; i < author_name.size(); i++){
      if (!(std::isalpha(author_name[i]) && !(author_name[i] = '-') && !(author_name[i] = ' ') && !(author_name[i] = ':'))){
         throw std::invalid_argument("Invalid author");
      }
   }
   for (long unsigned int i = 0; i < author.last_name.size(); i++){
      if (!(std::isalpha(author.last_name[i]) && !(author.last_name[i] = '-') && !(author.last_name[i] = ' ') && !(author.last_name[i] = ':'))){
         throw std::invalid_argument("Invalid author");
      }
   }
   if (title.size() == 0){
      throw std::invalid_argument("Invalid title");
   }
   for (long unsigned int i = 0; i < title.size(); i++){
      if (!(std::isalpha(title[i]))){
         throw std::invalid_argument("Invalid title");
      }
   }
   if (!(isbn.size() == 10 || isbn.size() == 13) && !(typeid(isbn).name() == typeid("").name())){
      throw std::invalid_argument("Invaldi ISBN");
   }
}

std::string Book::get_title() const {
   // TODO(student)
   return title;
}

AuthorName Book::get_author() const {
   // TODO(student)
   return author;
}

std::string Book::get_isbn() const {
   // TODO(student)
   return isbn;
}

bool Book::is_available() const {
   // TODO(student)
   return available;
}

bool Book::borrow_book() {
   // TODO(student)
   if (available){
      available = false;
      return true;
   }
   return false;
}

bool Book::return_book() {
   // TODO(student)
   if (!available){
      available = true;
      return true;
   }
   return false;
}

std::ostream& operator<<(std::ostream& os, const Book& blah) {
   // TODO(student)
   std::string title  = blah.get_title();
   std::string isbn = blah.get_isbn();
   AuthorName author = blah.get_author();
   std::string author_name = author.first_name + ' ' + author.last_name;
   std::cout << "title: \"" << title << "\" by " << author_name << ", isbn: " << isbn;

   return os;
}
