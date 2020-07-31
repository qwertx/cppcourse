// 析构函数何时执行? 离开作用域(语句块结束时)


int main()
{
    A a;
    if (B b = GetB()) // 只要类型B可以被隐式转换成bool，都可以这么写，譬如说shared_ptr<T>等
    {
        C c;
    } // 第一个右括号析构C
    // 出if语句析构B, 如果有else, 也可以访问B
    return 0;
}
// main结束析构A

// 如果抛出异常, 该执行的析构函数也会正常执行
// const T&类型的变量，只要是从右值引用构造出来的，
// 那么也跟普通的值类型变量一样，会在相同的地方调用析构函数

// 为什么不直接写T t;
// 由于const T&可以是父类, 有时必须这样写
String GetMyString()
{
    return "This is a string!";
}

int main()
{
    {   
        const String& s = GetMyString(); // 无法用String&初始化右值(或字面值), 必须加const
    } // 出右括号s被析构
    return 0;
}


// 上例中, String的构造函数/析构函数只调用了1次
// C++标准里面有return value optimization
// 即如果用一个变量接返回值, 或返回值是另一次调用的参数
// 那么会在函数内部(return语句中)把对象直接构造在那个变量或参数上

// 相当于遇到return时直接执行const string& s = "This is a string!";