// TODO(student): Implement this header file
# ifndef _MYSTRING_H
# define _MYSTRING_H
#include <iostream>
#include <stdexcept>

class MyString{
    private:
        char* str_arr;
        unsigned size_;
        unsigned capacity_;
        //int npos;
    public:
        MyString();
        MyString(const MyString& str);
        MyString (const char* c);
        int size();
        int length(MyString str);
        int capacity();
        MyString& operator=(MyString const& new_str);
        void clear();
        void resize(unsigned n);
        bool empty();
        MyString& MyString::operator+=(MyString new_str);
        const char& at (unsigned pos);
        const char& front();
        char* data();
        bool find(MyString str);
        ~MyString();
};
# endif

