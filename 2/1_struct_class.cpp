// struct默认public, class默认private
// c可以写struct foo foo; c++不行
// 比如下例, 因为B是struct, 所以B的基类A是public继承


#include <iostream>
using namespace std;

class A {
    public:
        int a;
};

struct B: A {
};

int main() {
    B b;
    b.a = 0;
    cout << b.a << endl;
    return 0;
}