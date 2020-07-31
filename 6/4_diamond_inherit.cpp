// 菱形继承
#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct A
{
    int data{ 0 };
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
    static_cast<B&>(d).data = 1;
    // 输出0, 具体解释见上一节
    cout << static_cast<C&>(d).data << endl;
    return 0;
}

// 共享A: 菱形继承
// 此时输出1
// 此时可以使用以下表达式
// A* pa = &d;
struct B : virtual A
{
};

struct C : virtual A
{
};



// B和C对A使用了不同的构造函数或不同的参数调用构造函数
// 但一个对象只能初始化一次?

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

struct C : virtual A
{
    C() :A{ 2 }
    {
        cout << data << endl;
    }
};

struct D : B, C
{
};

int main()
{
    D d;
    cout << d.data << endl;
    return 0;
}

// 以上代码无法通过编译, 有歧义
// 此时D必须自己决定如何初始化A
// 此时输出三个数字均为3
// 所以D对A的初始化覆盖了B和C的决定, 而且在B和C构造前就生效了
// 也就是先构造A, 此时data为3, 然后才是构造B和C, 但D的初始化起决定作用, data在BC构造过程中不变
struct D : B, C
{
    D() :A{ 3 }
    {
    }
};