// TODO(student): Implement this header file
# ifndef _MYSTRING_H
# define _MYSTRING_H

class MyString{
    private:
        char* str_arr;
    public:
        MyString();
        MyString(const MyString& str);
        MyString (const char* c);
        MyString operator=(MyString prev_str, MyString new_str);
        int size(MyString str);
        int length(MyString str);
        int capacity(MyString str);
        void clear(MyString str);
        void resize(size_t n);
        void empty();
        const char& at (size_t pos) const;
        const char& front() const;
        MyString operator+=(MyString pre_str, MyString new_str);
        char data(MyString str);
        bool find(MyString str);
        npos = ;
        MyString operator<<(MyString pre_str, MyString new_str);
        MyString operator+(MyString pre_str, MyString new_str);
        MyString operator==(MyString pre_str, MyString new_str);
        ~MyString();
};
# endif

