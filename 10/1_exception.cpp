// assert用于判断自己的错误, 比如空指针, 错误数据等
// 异常一般用来判断用户输入错误, 出异常证明程序无法处理所有的输入情况
// assert命中证明程序本身有错误

// 抛出异常: throw <表达式>;
// 这个语句会运行异常表达式，然后把结果保存到某个地方，最后结束整个函数的执行
// 外层函数也会被挨个结束，直到落到了某一个try语句里面为止

// 处理异常
try
{
    // 这里放着一段可能会抛出异常的代码，并且你想要处理它。
    f();
}
catch(int e)
{
    // 异常可以是任何类型。只要f函数抛出了一个int类型的异常，譬如说throw 10;，那么就会落到这里
    // 然后你就可以做些事情，结束这个异常的传播
}
// bad_alloc异常可以在new时用nothrow阻止, 比如int *p = new (nothrow) int; 分配失败返回空指针
catch(std::bad_alloc e)
{
    // 如果异常是std::bad_alloc类型的，这通常意味着标准库里面需要new一段内存失败了
    // 你仍然可以做一些补救工作。但是你认为你无法处理这个异常，于是让异常继续传播出去
    // 也就是让更外层的try-catch语句去处理。
    // 这个时候就可以使用不带表达式的throw语句，这个语句专门在catch语句里面表示继续抛出这个异常
    throw;
}

// 举例
#include <string>
#include <iostream>

using namespace std;

// 异常可以是任何类型的
struct InvalidFormatException
{
};

int ReadInt(string s)
{
    auto begin = s.c_str(); // 转为char*
    char* end = nullptr;
    // long int strtol(const char* nptr, char** endptr, int base)
    // 将nptr指向的字符串根据base转为long int, base从2-36进制
    // 检测到非法字符时停止, 比如base=2, '2'是非法的
    // 结果返回long int, 非法字符串赋给*endptr(注意endptr是char*的指针, 要传入end的地址)
    int result = strtol(begin, &end, 10);
    if (*end != '\0') // 如果字符串中有非法字符(非数字)
    {
        // 异常用于处理输入错误, 这里用assert不好
        // 因为输入错误不应该让程序直接崩溃
        throw InvalidFormatException{};
    }
    return result;
}


int main()
{
    string s;
    getline(cin, s);
    try
    {
        int i = ReadInt(s);
        cout << "它的平方是" << i * i << "。" << endl;
    }
    // 此处只有类型没有异常的名字，这是因为我们不需要去检查异常对象的内容(因为没有内容)
    // 所以名字可以省略
    catch (InvalidFormatException)
    {
        cout << "格式错误。" << endl;
        // 无需继续用throw;抛出异常
    }
    return 0;
}

// 注意throw执行main函数里面的ReadInt(s)也就中断了
// 这个不存在的结果将不会赋值给i变量, 而是直接去执行catch语句的内容

// 如果没有对应的catch语句，会继续往外抛
// 直到调试器接住这个异常, 如果调试器不存在的话, 程序就会直接崩溃