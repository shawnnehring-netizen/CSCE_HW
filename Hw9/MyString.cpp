// TODO(student): Implement this source file
#include "MyString.h"
#include <iostream>
#include <stdexcept>


MyString::MyString() : str_arr{new char[1]}, size_{0}, capacity_{1}{}

MyString::MyString(const MyString& str) : str_arr{new char[str.capacity_]}, size_{str.size_}, capacity_{str.capacity_} {
    for (size_t i = 0; i < str.size_; i++){
        str_arr[i] = str.str_arr[i];
    }
}

MyString::MyString (const char* c){
    size_t i = 0;
    while(c[i] != '\0'){
        i++;
    }
    size_ = i;
    capacity_ = i+1;
    str_arr = new char[capacity_];
    for (size_t j = 0; j < size_;j++){
        str_arr[j] = c[j];
    }
    str_arr[size_] = '\0';
}

MyString& MyString::operator=(MyString const& new_str){
    if (this != &new_str){
        char* copy = new char[new_str.capacity_];
        for(size_t i = 0; i < new_str.capacity_; i++){
            copy[i] = new_str.str_arr[i];
        }
        delete[] str_arr;
        str_arr = copy;
        capacity_ = new_str.capacity_;
        size_ = new_str.size_;
    }
    return *this;

}

size_t MyString::size()const{
    return size_;
}

size_t MyString::length()const{
    return size_;
}

size_t MyString::capacity()const{
    return capacity_;
}

void MyString::clear(){
    size_ = 0;
}

void MyString::resize(size_t n){
    if(n > capacity_){
        capacity_ *= 2;
    }
    size_ = n;
}

bool MyString::empty(){
    if(size_ == 0){
        return true;
    }
    else{
        return false;
    }
}

MyString& MyString::operator+=(MyString new_str){
    if (size_ + new_str.size_ > capacity_){
        capacity_ *= 2;
    }
    for (size_t i = 0; i < new_str.size_; i++){
        str_arr[i+size_] = new_str.str_arr[i];
    }
    return *this;
}

const char& MyString::at(size_t pos)const {
    return str_arr[pos];
}

const char& MyString::front()const {
    return str_arr[0];
}


char* MyString::data() const{
    return str_arr;
}

bool MyString::find(MyString str){
    for (size_t i = 0;  i < size_; i++){
        if (str_arr[i] == *str.str_arr){
            return true;
        }
    }
    return npos;
}

MyString::~MyString(){
    delete[] str_arr;
}

std::ostream& operator<<(std::ostream& os, const MyString& new_str){
    os << new_str.data();
    return os;
}

MyString operator+(MyString old, MyString new_){
    if (old.size() + new_.size() > old.capacity()){
        old.resize(old.size() + new_.size());
    }
    for (size_t i = 0; i < new_.size(); i++){
        old.data()[i+old.size()] = new_.data()[i];
    }
    return old;
}

bool operator==(MyString old, MyString new_){
    if (old.size() == new_.size()){
        for (size_t i = 0; i < old.size(); i++){
            if (new_.data()[i] != old.data()[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}