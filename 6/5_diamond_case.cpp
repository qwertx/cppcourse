#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct A
{
    int data;

    A(int theData)
        :data{ theData }
    {
    }
};

struct B : virtual A
{
    B() :A{ 1 }
    {
        cout << data << endl;
    }
};

struct C : A
{
    C() :A{ 2 }
    {
        cout << data << endl;
    }
};

// 1. B和C不共享A, 只有虚拟继承才共享, 其余的A是独立的
struct D : B, C
{   
    // 理论上是错误的, 因为编译器不知道用哪个A
    // 但是g++没有报错
    // 此处D的初始化只覆盖了虚拟继承, 真实继承没有影响
    D() :A{ 3 }
    {
    }
};

int main()
{
    D d; // 输出3 2
    cout << static_cast<B*>(&d)->data << endl; // 3
    cout << static_cast<C*>(&d)->data << endl; // 2
    // 错误, 不知道用哪个data
    cout << d.data << endl;
    return 0;
}