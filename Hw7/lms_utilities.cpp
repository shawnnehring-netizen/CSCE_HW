#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "book.h"
#include "member.h"
#include "library.h"
#include "lms_utilities.h"

int read_list_of_books(Library& lib, const std::string& file) {
   // TODO(student)
   std::string title = "";
   std::string first_name = "";
   std::string last_name = "";
   std::string isbn = "";
   int count = 0;
   std::ifstream word_file(file);
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (word_file >> title >> first_name >> last_name >> isbn){
      AuthorName author = {};
      author.first_name = first_name;
      author.last_name = last_name;
      try{
         Book new_book = Book(title,author,isbn,true);
         lib.add_book(new_book);
         count +=1;
      }
      catch(...){
         continue;
      }
   }
   return count;
}

int read_list_of_members(Library& lib, const std::string& file) {
   // TODO(student)
   std::string first_name = "";
   std::string last_name = "";
   int count = 0;
   int id = 1000;
   std::ifstream word_file(file);
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (word_file >> first_name >> last_name){
      try{
         Member mem = Member(first_name, last_name, id);
         lib.register_member(mem);
         id += 1;
         count += 1;
      }
      catch(...){
         continue;
      }
   }
   return count;
}

int read_list_of_borrowed_books(Library& lib, const std::string& file) {
  // TODO(student)
   std::string isbn = "";
   int id = 0;
   int count = 0;
   //bool isbn_check = false;
   //bool return_check = false;
   bool check = false;
   std::ifstream word_file(file);
   std::string msg = "";
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (word_file >> isbn >> id){
   //   if (){
   //      msg = "Book ISBN: " + isbn + " not available";
   //   }
   //   else if (){
   //      msg = "Member " + id + " not found";
   //   }
   //   else{
   //      msg = member + " borrowed " + book;
   //   }
      check = lib.borrow_book(isbn,id,msg);
      if (check){
         count+=1;
      }
   }
   return count;
}

int read_list_of_returned_books(Library& lib, const std::string& file) {
   // TODO(student)
   std::string isbn = "";
   int count = 0;
   //bool isbn_check = false;
   //bool return_check = false;
   bool check = false;
   std::ifstream word_file(file);
   std::string msg = "";
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (word_file >> isbn){
   //   if (){
   //      msg = "Book ISBN: " + isbn + " not available";
   //   }
   //   else if (){
   //      msg = "Member " + id + " not found";
   //   }
   //   else{
   //      msg = member + " borrowed " + book;
   //   }
      check = lib.return_book(isbn,msg);
      if (check){
         count+=1;
      }
   }
   return count;
}
