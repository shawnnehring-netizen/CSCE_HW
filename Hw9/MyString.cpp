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

MyString::MyString (const char* c) : str_arr{}, size_{}, capacity_{}{
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
    str_arr[0] = '\0';
}

void MyString::resize(size_t n){
    while(n >= capacity_){
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

MyString& MyString::operator+=(const MyString new_str){
    size_t old = size_;
    this->resize(new_str.size_ + size_);
    for (size_t i = 0; i < new_str.size_; i++){
        str_arr[i+old] = new_str.str_arr[i];
    }
    str_arr[size_-1] = '\0';
    return *this;
}

const char& MyString::at(size_t pos)const {
    if (pos >= size_){
        throw std::out_of_range("out of range");
    }
    return str_arr[pos];
}

const char& MyString::front()const {
    return str_arr[0];
}


char* MyString::data() const{
    return str_arr;
}

size_t MyString::find(const MyString& new_str, size_t pos) const{
    size_t j = 0;
    for (size_t i = pos; i < size_; i++){
        if (str_arr[i] == new_str.str_arr[j]){
            size_t first = i;
            j += 1;
            if (j == new_str.size_){
                return first;
            }
        else{
            j=0;
        }
        }
    }
    return npos;
}


MyString::~MyString(){
    delete[] str_arr;
}

std::ostream& operator<<(std::ostream& os, const MyString& new_str){
    for (size_t i = 0; i < new_str.size(); i++){
        os << (new_str.data()[i]);
    }
    return os;
}

MyString operator+(MyString old, const MyString new_){
    old.resize(old.size() + new_.size());
    for (size_t i = 0; i < old.size(); i++){
        old.data()[i + old.size() - new_.size()] = new_.data()[i];
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