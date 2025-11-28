#include <stdexcept>
#include "LinkedList.h"

// TODO(student): implement a linked list

LinkedList::LinkedList() : head{nullptr} {}

LinkedList::LinkedList(const LinkedList& other) : head{new Node(0)} {
    head->value = other.head->value;
    Node* copy_me = other.head->next;
    Node* copy_here = head;
    while(copy_me != nullptr){
        copy_here->next = new Node(copy_me->value);
        copy_here = copy_here->next;
        copy_me = copy_me->next;
    }

}

LinkedList::~LinkedList() {
    Node* here = head;
    while (here != nullptr){
        Node* next_one = here->next;
        delete here;
        here = next_one;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other){
    head = new Node(other.head->value);
    Node* copy_me = other.head->next;
    Node* copy_here = head;
    while(copy_me != nullptr){
        copy_here->next = new Node(copy_me->value);
        copy_here = copy_here->next;
        copy_me = copy_me->next;
    }
    return *this;

}

bool LinkedList::empty() const{
    return head == nullptr;
}

unsigned LinkedList::size() const{
    Node* point = head;
    int size = 0;
    while(point != nullptr){
        size ++;
        point = point->next;
    }
    return size;
}

int LinkedList::at(unsigned index) const{
    try{
        Node* point = head;
        for (unsigned int i = 0; i < index; i++){
            point = head->next;
        }
        return point->value;
    }
    catch(...){
        throw std::out_of_range("out of bounds");
    }
}

int LinkedList::front() const{
    if(head == nullptr){
        throw std::out_of_range("list is empty");
    }
    else{
        return head->value;
    }
}

void LinkedList::add(int value, unsigned index){
    try{
        Node* point = head;
        for (unsigned int i = 0; i < index-1; i++){
            point = head->next;
        }
        Node* other = new Node(value);
        other->next =  point->next;
        point->next = other;
    }
    catch(...){
        throw std::out_of_range("inedx ot of bounds");
    }
}

void LinkedList::remove(unsigned index){
    try{
        Node* point = head;
        for (unsigned int i = 0; i < index-1; i++){
            point = head->next;
        }
        Node* deleted_node = point->next;
        point->next = deleted_node->next;
        delete deleted_node;
    }
    catch(...){
        throw std::out_of_range("inedx ot of bounds");
    }
}

void LinkedList::clear(){
    Node* point = head;
    while(point != nullptr){
        Node* new_point = point->next;
        delete point;
        point = new_point;
    }
}