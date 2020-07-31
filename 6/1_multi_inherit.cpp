// 多重继承就是一个类有多个基类


#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct A
{
    virtual ~A() = default;

    virtual void PrintA()
    {
        cout << "A::PrintA" << endl;
    }
};

struct B
{
    virtual ~B() = default;

    virtual void PrintB()
    {
        cout << "B::PrintB" << endl;
    }
};

struct C : A, B
{
    void PrintA()override
    {
        cout << "C::PrintA" << endl;
    }

    void PrintB()override
    {
        cout << "C::PrintB" << endl;
    }
};

int main()
{
    C c;
    // 将c的地址传给基类的指针, 但是调用仍然是c的函数
    A* pa = &c;
    B* pb = &c;

    pa->PrintA(); // C::PrintA
    pa->A::PrintA(); // A::PrintA
    pb->PrintB(); // C::PrintB
    pb->B::PrintB(); // B::PrintB

    // 同理
    // 这里是A向B转换
    // A, B类都有虚函数, 而且pa指向C, C继承自B, 因此有效
    // 也就是基类间相互转换可以用dynamic_cast
    pb == dynamic_cast<B*>(pa);
    return 0;
}