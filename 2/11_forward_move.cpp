// forward按原样传递引用, 注意不要忽略模板参数
// 比如声明的参数为X&&, 写成forward<X>
// 若X为非引用类型, 处理为右值, 否则为左值
// forward一般配合模板使用, 若明确知道类型, 那么只有右值引用需要forward
#include <iostream>
#include <vector>

using namespace std;


void Print(int& x)
{
    cout << "x is int&" << endl;
}

void Print(int&& x)
{
    cout << "x is int&&" << endl;
}

template<typename T>
void CallPrint(T&& x)
{
    Print(std::forward<T>(x));
}

int main()
{
    int x = 0;
    CallPrint(x); // x为左值, T为int&(是整数的引用/别名), forward int&返回int&
    // 0是constexpr int, 可以是int/const int/const int&/int&&/const int&&
    // 推导得知T为int(整数自身), 因此是右值, 调用int&&
    CallPrint(0); 
    // constexpr: 常量表达式, 表示在编译期间可以算出来
    return 0;
}


// move声称左值对象再也不需要了, 返回该对象的右值引用
class ClassRoom
{
private:
    vector<string> students;

public:
    ClassRoom()
    {
    }

    ClassRoom(const ClassRoom& classRoom)
        :students{classRoom.students}
    {
    }

    ClassRoom(ClassRoom&& classRoom)
    // 使用move获得classRoom.students的右值引用
    // 因为此处使用了classRoom.students,因此是左值引用,需要move进行转换
    // 如果使用的是声明的classRoom, 那么可以forward
        :students{std::move(classRoom.students)} 
    {
    }
};

// 比如, 此处Do两次均调用的是左值引用的Print, 因为x y都在函数体内获得了名字, 没有阻止接下来的使用
// 需要加入forward即可变为右值引用
void Print(int& x)
{
    cout << "x is int&" << endl;
}

void Print(int&& x)
{
    cout << "x is int&&" << endl;
}

void Do(int&& x)
{
    Print(x);

    int&& y = 0;
    Print(y);
}

// 总结:
// move和forward之后的参数不要再使用
// forward将形式上声明为右值引用的参数传递出去
// move在传递左值引用对象的时候, 声称其已经不再需要使用了

// 测试
// 此处应该用forward, 因为以及被标记为&&, 就不再需要声称其用完后不需要了
class ClassRoom2
{
private:
    vector<string> students;

public:
    ClassRoom2(vector<string>&& theStudents) // 右值引用构造函数
        :students{std::forward<vector<string>>(theStudents)}
    {
    }
};