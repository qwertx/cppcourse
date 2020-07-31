// 静态成员相当于全局变量, 使用时要写 类名::
// 也相当于全局函数, 只不过可以查看自己所在类的private或protected成员

// static和virtual互斥
// 构造/析构, 某些运算符重载, 无法声明成static



// 对于静态变量, 如果不是const整数(或整数兼容类型, 比如enum和char等)
// 那么写在类里只是声明, 还额外需要定义

// 类似于全局变量定义要写在cpp里面, 头文件只能放extern的全局变量声明
// 此处类里面相当于extern
struct MyClass
{
    static const int A = 0;
    static string B; // 声明
};

string MyClass::B = "我是一个静态字符串变量";



// 静态函数
class MyClass
{
private:
    int data;

public:
    MyClass(int theData)
        :data{theData}
    {
    }

    int A()
    {
        return data;
    }

    static int B(const MyClass& myClass)
    {
        return myClass.data;
    }
};

int main() {
    MyClass a(10);
    MyClass* pa = &a;

    // 均为true
    a.A() == MyClass::B(a);
    pa->A() == MyClass::B(*pa); // 解引用得到引用
    return 0;
}

// 静态函数属于类本身, 无法访问this
// 所以virtual, override, const, &, &&等都无法使用