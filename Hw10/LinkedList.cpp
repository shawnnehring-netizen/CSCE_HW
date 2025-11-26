#include <stdexcept>
#include "LinkedList.h"

// TODO(student): implement a linked list

LinkedList::LinkedList() : head{new Node(0)} {}

LinkedList::LinkedList(const LinkedList& other) {
    int value = other.head->value;
    Node* point = other.head->next;
    Node* head = new Node(value,point);
}

LinkedList::~LinkedList() {
    Node* here = head;
    while (here != nullptr){
        Node* next_one = here->next;
        delete here;
        here = next_one;
    }
}

LinkedList& LinkedList::operator=(const LinkedList list){
    if (list.head->next != head->next){
        Node* copy_me = list.head;
        Node* copy_here = head;
        while(copy_me != nullptr){
            copy_here->value = copy_me->value;
            copy_here->next = copy_me->next;
            copy_here = copy_here->next;
            copy_me = copy_me->next;
        }
    }
    return *this;

}

bool LinkedList::empty() const{
    if (head->next == nullptr){
        return true;
    }
    return false;
}

unsigned LinkedList::size() const{
    Node* point = head->next;
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
        for (unsigned int i = 0; i <= index; i++){
            if (i == index){
                return point->value;
            }
            point = head->next;
        }
    }
    catch(...){
        throw std::out_of_range("out of bounds");
    }
}

int LinkedList::front() const{
    if(head->next == nullptr){
        throw std::out_of_range("list is empty");
    }
    else{
        return head->value;
    }
}

void LinkedList::add(int value, unsigned index){
    
}

void LinkedList::remove(unsigned index){}

void LinkedList::clear(){}

Node*& LinkedList::get_head() { return head; }