// X内部能否看见Y y的成员member?
// (不涉及operator&重载)
class X
{
    public:
        void Method(Y& y)
        {
            &y.member; // &(y.member)而不是(&y).member!!!!!
            // 如果member是静态成员(属于类而非实例的成员)
            &Y::member;
        }
};

// 1. public都能访问

// 2. protected和private时, 若member定义在Y内, 只有X和Y相同才能访问
// 下例中, X<T>和X<U>相同则可以访问
template<typename T>
class X
{
private: 
    int member;

public:
    template<typename U>
    void Method(X<U>& y)
    {
        &y.member;
    }
};

int main()
{
    X<int> x;
    X<float> y;
    x.Method(x); // 可以
    x.Method(y); // 不可以
}

// 3.
// 若member定义在Y的某个基类Base中, 当X和Y相同时
// 若member是Base的protected成员, 可以访问
// 若member是Base的private成员, 不可以访问
class Base
{
private:
    int a;

protected:
    int b;
};

class Derived : public Base
{
public:
    void Method(Derived& y)
    {
        &y.a; // 不可以
        &y.b; // 可以
    }
};

// 4.
// 若member定义在Y的基类Base中, 且X Y不同(包括X继承自Y)
// class Y: public Base, 仅member是Base的public成员, 可以访问
// class Y: protected/private Base, 不能访问
// 而且X内部无法知道Base是Y的基类, 无法做指针或引用的类型转换
class Base1
{
private:
    int a1;

protected:
    int b1;

public:
    int c1;
};

class Base2
{
private:
    int a2;

protected:
    int b2;

public:
    int c2;
};

class Base3
{
private:
    int a3;

protected:
    int b3;

public:
    int c3;
};

class Y : public Base1, protected Base2, private Base3
{
};

class X
{
public:
    void Method(Y& y)
    {
        &y.a1; // 不可以
        &y.b1; // 不可以
        &y.c1; // 可以

        &y.a2; // 不可以
        &y.b2; // 不可以
        &y.c2; // 不可以

        &y.a3; // 不可以
        &y.b3; // 不可以
        &y.c3; // 不可以
    }
};


// 5.
// 若member定义在Y的基类Base中, 且X继承自Y, 但X访问Y成员时
// class Y: public/protected Base, 仅member是Base的public或protected成员, 可以访问
// class Y: private Base, 不能访问
// 而且X内部无法知道Base是Y的基类, 无法做指针或引用的类型转换
class Base1
{
private:
    int a1;

protected:
    int b1;

public:
    int c1;
};

class Base2
{
private:
    int a2;

protected:
    int b2;

public:
    int c2;
};

class Base3
{
private:
    int a3;

protected:
    int b3;

public:
    int c3;
};

class Y : public Base1, protected Base2, private Base3
{
};

class X : public Y
{
public:
    void Method(X& y) // 注意 y 的类型是 X
    {
        &y.a1; // 不可以
        &y.b1; // 可以
        &y.c1; // 可以

        &y.a2; // 不可以
        &y.b2; // 可以
        &y.c2; // 可以

        &y.a3; // 不可以
        &y.b3; // 不可以
        &y.c3; // 不可以
    }
};


// 6. X是Y的内部类, Y能看到什么, X就能看到什么, 不受上面规则约束
class Y
{
    class X // Y 是 public、protected 或 private都不重要
    {
    };
};

// 7. y换成this, 同样成立