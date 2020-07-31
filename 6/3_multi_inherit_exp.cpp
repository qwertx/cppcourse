#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct A
{
    int a;
};

struct B : A
{
};

struct C : A
{
};

struct D : B, C
{
};

int main()
{
    D d;
    // B继承自A, C继承自A, D继承B和C, 因此D实际包含了两份A的内容
    // 那么从D*到A*就无法隐式转换, 因为不知道要转成B中的A还是C中的A
    // 所以必须告诉编译器选择哪个A
    // A* pa = &d;

    // 选择B中的A, 包含了两次转换, 一次显式一次隐式
    A* pa = static_cast<B*>(&d);

    // 验证的确有2个A
    static_cast<C*>(&d)->a = 1;
    static_cast<B*>(&d)->a = 0;
    cout << static_cast<C*>(&d)->a << endl; // 1
    return 0;
}

// 使用虚拟继承, 可以让D只包含一份A的内容