#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct X
{
    virtual void Print() const
    {
        cout << "X" << endl;
    }
};

struct Y : X
{
    void Print() const override
    {
        cout << "Y" << endl;
    }
};

int main()
{
    const X& x = Y{}; // 隐式转换到父类的引用
    x.X::Print(); // 直接调用X的Print

    // 下面两个调用是一样的, 只是后一个起了个名字print
    // x.*&X::Print, 指代的是虚函数X::Print被覆盖的结果
    (x.*&X::Print)();

    void (X::* print)()const = &X::Print;
    (x.*print)();

    // 就算不用指针也是一样的, 隐式转换的父类指针永远调用的是override的实际子类函数
    x.Print();
    return 0;
}