#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct X
{
    void A()
    {
    }

    int B(string u, double v)
    {
        return {};
    }

    string C(bool b)const
    {
        return{};
    }

    string D(bool b)&&
    {
        return{};
    }
};

int main()
{
    /*下面的四个填空都不能使用auto关键字*/

    // 练习定义成员函数指针
    void (X::* a)() = &X::A;
    int (X::* b)(string, double) = &X::B;
    string (X::* c)(bool) const = &X::C;
    string (X::* d)(bool) && = &X::D;
    return 0;
}

// 建议将
int (X::*b)(string, double) = &X::B;
// 以及
typedef int (X::*XB)(string, double);
XB b = &X::B;
// 改成, 这样定义的类型名字在最前面, 非常明显
using XB = int (X::*)(string, double);
XB b = &X::B;


// 合理使用using
using Member = int Vector::*; // Member是Vector中某个int成员变量的指针
using Filter = bool(*)(Member); // Filter是以Member为参数的函数指针
using MemberArray_10 = Member[10]; // Member数组

MemberArray_10* GetMembers(Filter filter)
{
    throw 0;
}

// 而不是下面这种完全看不明白的东西
// 注意函数返回数组指针格式是Type (*function(param_list)) [dimension]
// 维度在最后面
int Vector::* (*GetMembers(bool (*filter)(int Vector::*))) [10]
{
    throw 0;
}

// 用上面的例子写的测试, 可以正常编译
#include <string>
#include <iostream>

using namespace std;

struct Vector {
    int a;
    Vector(int s):a{s}{}
};
int Vector::* (*GetMembers(bool (*filter)(int Vector::*))) [10] {
        throw 0;
}
bool ff(int Vector::* vv){
    Vector v{1};
    if(v.*vv > 0) return true;
    else return false;
}
int main(){
    GetMembers(ff);
}