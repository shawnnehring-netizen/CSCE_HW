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
   std::string line = "";
   std::string title = "";
   std::string first_name = "";
   std::string last_name = "";
   std::string isbn = "";
   int count = 0;
   int step = 0;
   std::ifstream word_file(file);
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (getline(word_file,line)){
      if (step == 0){
         title = line;
         step = 1;
      }
      else if (step == 1){
         int pos = line.find(' ');
         first_name = line.substr(0,pos);
         last_name = line.substr(pos+1,line.size());
         step = 2;
      }
      else if (step == 2){
         isbn = line;
         step = 3;
      }
      if (step == 3){
         step = 0;
         try{
            Book new_book = Book(title,first_name,last_name,isbn);
            lib.add_book(new_book);
            count +=1;
         }
         catch(...){
            continue;
         }
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
   std::string line = "";
   int id = 0;
   int count = 0;
   int step = 0;
   std::ifstream word_file(file);
   std::string msg = "";
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (getline(word_file,line)){
      if (step == 0){
         isbn = line;
         step = 1;
      }
      else if (step == 1){
         id = std::stoi(line);
         step = 0;
         if (lib.borrow_book(isbn,id,msg)){
            count+=1;
         }
      }
   }
   return count;
}

int read_list_of_returned_books(Library& lib, const std::string& file) {
   // TODO(student)
   std::string isbn = "";
   int count = 0;
   std::ifstream word_file(file);
   std::string msg = "";
   if (!(word_file.is_open())){
      throw std::runtime_error("Cannot open "+file);
   }
   while (word_file >> isbn){
      if (lib.return_book(isbn,msg)){
         count+=1;
      }
   }
   return count;
}
