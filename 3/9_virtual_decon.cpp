// 任何有子类的类都要有虚析构函数(因为面向对象程序设计要求)
// why?
#include <string>

using namespace std;

struct Base
{
};

struct Derived : Base
{
    // 长字符串使得std::string必须申请内存来保存
    string s {"This is a very long string that force std::string to allocate a buffer."};
};

int main()
{
    Derived* obj = new Derived;
    // Derived类的析构函数调用了std::string的析构函数
    delete obj;
    return 0;
}


// 但若改成
int main()
{
    Base* obj = new Derived; // 隐式转换为Base*
    // 调用Base的析构函数, 因此字符串没有释放
    // delete后也丢失了对该对象的引用
    delete obj;
    return 0;
}

// 改进: 给Base增加一个虚析构函数, 因为虚析构函数可以被子类覆盖
// 所以最终执行的是Derived的析构函数
struct Base()
{
    virtual ~Base() = default;
};

// 不要在g++或clang++中将子类指针的数组转成父类指针
int main()
{
    // 创建一个有10个Derived对象的数组, 并使用一个Base*指针指向该数组首地址
    Base* obj = new Derived[10];
    delete[] obj; // KABOOM!
    return 0;
}