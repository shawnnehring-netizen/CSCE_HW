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
    Node* point = head;
    for (unsigned int i = 0; i < index; i++){
        if (point == nullptr){
            throw std::out_of_range("out of bounds");
        }
        point = point->next;
    }
    if (point == nullptr){
        throw std::out_of_range("out of bounds");
    }
    return point->value;
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
    if (index == 0){
        Node* other = new Node(value);
        other->next = head;
        head = other;
    }
    else{
        Node* point = head;
        for (unsigned int i = 1; i < index; i++){
            if (point == nullptr){
                throw std::out_of_range("out of bounds");
            }
            point = point->next;
        }
        if (point == nullptr){
            throw std::out_of_range("out of bounds");
        }
        Node* other = new Node(value);
        other->next = point->next;
        point->next = other;
    }
}

void LinkedList::remove(unsigned index){
    if (index == 0){
        if(head == nullptr){
           throw std::out_of_range("out of bounds"); 
        }
        Node* deleted_node = head;
        head = nullptr;
        delete deleted_node;
    }
    else{
        Node* point = head;
        for (unsigned int i = 1; i < index; i++){
            if (point == nullptr){
                throw std::out_of_range("out of bounds");
            }
            point = point->next;
        }
        if (point == nullptr){
            throw std::out_of_range("out of bounds");
        }
        Node* deleted_node = point->next;
        point->next = deleted_node->next;
        delete deleted_node;
    }
}

void LinkedList::clear(){
    Node* point = head;
    while(point != nullptr){
        Node* new_point = point->next;
        delete point;
        point = new_point;
    }
    head = nullptr;
}