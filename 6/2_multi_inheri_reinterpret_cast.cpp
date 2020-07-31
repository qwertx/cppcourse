#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct A
{
    int a;

    virtual ~A() = default;

    void Print()
    {
        cout << a << endl;
    }
};

struct B
{
    int b;

    virtual ~B() = default;

    void Print()
    {
        cout << b << endl;
    }
};

struct C : A, B
{
};

int main()
{
    C c;
    c.a = 1;
    c.b = 2;

    B* pb = reinterpret_cast<B*>(&c);
    // 流行的编译器中输出1
    // 可以将C在内存中理解为AB连续存放(因为C首先继承A)
    // 其中A和B的长度都是2*sizeof(void*), 第一个指针保存虚函数表, 第二个保存a或b
    // 想象成四格: A虚-a-B虚-b
    // 由于reinterpret_cast解释为B*, 那么执行this->b时
    // pb就会把C当作B去解释, 也就是误以为A::a所在的第二格是b, 因此输出1
    pb->Print();

    // 子类转父类请用static_cast
    B* pc = static_cast<B*>(&c);
    pc->Print(); // 输出2
    return 0;
}

