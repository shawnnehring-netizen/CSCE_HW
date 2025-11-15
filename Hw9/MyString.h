// TODO(student): Implement this header file
# ifndef _MYSTRING_H
# define _MYSTRING_H
#include <iostream>
#include <stdexcept>

class MyString{
    private:
        char* str_arr;
        size_t size_;
        size_t capacity_;
    public:
        static const size_t npos = -1;
        MyString();
        MyString(const MyString& str);
        MyString (const char* c);
        MyString& operator=(MyString const& new_str);
        size_t size()const;
        size_t length()const;
        size_t capacity()const;
        void clear();
        void resize(size_t n);
        bool empty();
        MyString& operator+=(MyString& new_str);
        const char& at (size_t pos)const;
        const char& front()const;
        char* data() const;
        size_t find (const MyString& new_str, size_t pos = 0) const;
        ~MyString();
};
MyString operator+(MyString old, const MyString new_);
bool operator==(MyString old, MyString new_);
std::ostream& operator<<(std::ostream& os, const MyString& new_str);
#endif

