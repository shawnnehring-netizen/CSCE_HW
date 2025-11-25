#include <iostream>
using namespace std;

class Foo{
 public:
    int* data;
    Foo() : data(new int(5)) {}
    Foo(const Foo& other){
        data = new int(*other.data);
        cout << "X";
    }
    ~Foo(){
        delete data;
        cout << "Y";
    }
};
int main(){
    Foo a, b;
    Foo c = a;
    *a.data = 7;
    cout << *c.data;
    b = a;
}


