// A
// 正确
struct Vector
{
};

Vector operator*(int a, Vector b)
{
    return {};
}



// B
// operator不能被定义为静态函数, 与C#相反
struct Vector
{
    static Vector operator*(int a, Vector b)
    {
        return {};
    }
};



// C
struct Vector
{
    // operator*不能有三个参数
    // 因为operator为成员函数时, 左侧运算对象必须是自己类的一个对象
    Vector operator*(int a, Vector b)
    {
        return {};
    }
};



int main()
{
    int a = 0;
    Vector b;
    a * b;
    return 0;
}