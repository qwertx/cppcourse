#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct Animal
{
    virtual ~Animal() = default;
    virtual void PrintIntroduction() = 0;
};

struct Bear : virtual Animal
{
    void PrintIntroduction()override
    {
        cout << "我是一头熊。" << endl;
    }
};

struct Cat : virtual Animal
{
    void PrintIntroduction()override
    {
        cout << "我是一只猫。" << endl;
    }
};

struct BearCat: Bear, Cat {
    void PrintIntroduction()override
    {
        cout << "我才不是什么熊猫（逃" << endl;
    }
};

int main()
{
    BearCat bearCat;
    // 当BearCat为空时, 产生歧义
    // 因为Bear和Cat共享一个Animal, 虚函数也是共享的
    // 需要再覆盖一次虚函数
    bearCat.PrintIntroduction();
    return 0;
}