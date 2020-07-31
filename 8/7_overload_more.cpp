// 类型转换也是通过运算符重载实现的

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

struct Vector
{
    int x;
    int y;
    
    // 让Vector能隐式转换到string
    // 如果加上explicit关键字, 就只能显式转换
    // string s = static_cast<string>(v);

    // explicit更常用于构造函数, 表示只能显式构造, 不能通过隐式转换构造
    operator string()const
    {
        stringstream ss;
        // istringstream通常用来读取一行中的各个单词
        // 而ostringstream可以将多个内容写入内存
        // 然后用.str()返回保存的string
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }
};

// 要注意二元运算符的结合性
// a+b+c+d
// a.operator+(b).operator+(c).operator+(d)
// 或
// operator+(operator+(operator+(a, b), c), d)

// 但operator=是右结合的, a=b=c=d
// a.operator=(b.operator=(c.operator=(d)))
// 注意operator=必须是成员函数


// operator->和operator->*可以重载,
// 但operator.和operator.*不行
// ->*和.*是指向成员选择的指针(先解引用再获取成员)

// 因为可以对非指针调用->, 比如shared_ptr<T>可以使用
// p->x(实际是p.get()->x)
// 因此shared_ptr<T>::operator->()返回T*

// 如果operator->返回不是指针, 那么编译器会一直调用该operator->
// 直至遇到指针为止

// 定义重载要想好返回值类型
// 注意参数类型是const T&, T&还是T, 要不要对左值右值分别重载
// 要不要加const等等

// ?:这个三元操作符无法重载