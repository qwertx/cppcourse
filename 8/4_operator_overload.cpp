// 若一个表达式是-x
// 会被翻译成x.operator-()或operator-(x)
// 取决于哪一个有定义, 如果都有, 就会选择成员函数的那个
// 比如
struct X
{
    X operator -() // x.operator-()
    {
        return{};
    }
};

X operator-(const X&) // operator-(x)
{
    return{};
}

// ++/--
// ++x, 一般为x.operator++()或operator++(x)
// x++, 一般为x.operator++(int{})或operator++(x, int{})
// int{}参数没有用, 仅仅用来区分是前置++还是后置++


// 二元操作符, 比如a+b
// a.operator+(b)或operator+(a, b)

// 但是operator=或operator+=等必须是成员函数

// 此外, operator=会被自动生成, 和构造/析构函数一样
// 如果类的某个成员的operator=声明为delete的话, 类的operator=也是delete

// 赋值操作符原则上应返回自己引用(不是强制的)
// operator+和operator=都被定义时, operator+=仍不会自动存在

// 声明在类外的operator函数, 可以被定义在任意的namespace里
// 仅当你可以直接访问到该namespace内容时(比如using namespace xxx), 这个运算符才起作用
// 也可以使用全名, 比如::A::B::operator-(x)
// ::x可以访问全局x(当x被成员变量x隐藏时)

// ::表示顶层命名空间, 比如::std::string, 可以这样写