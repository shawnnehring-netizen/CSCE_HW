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
        const unsigned npos = -1;
    public:
        MyString();
        MyString(const MyString& str);
        MyString (const char* c);
        MyString& operator=(MyString const& new_str);
        unsigned size()const;
        unsigned length()const;
        unsigned capacity()const;
        void clear();
        void resize(unsigned n);
        bool empty();
        MyString& operator+=(MyString new_str);
        const char& at (unsigned pos)const;
        const char& front()const;
        char* data() const;
        bool find(MyString str);
        ~MyString();
};
MyString operator+(MyString old, MyString new_);
bool operator==(MyString old, MyString new_);
std::ostream& operator<<(std::ostream& os, const MyString& new_str);
#endif

