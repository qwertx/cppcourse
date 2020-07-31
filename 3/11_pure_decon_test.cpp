class A
{
public:
    virtual ~A() = default;
    virtual void F() = 0;
};

class B : public A
{
public:
    // 因为基类中的F()是虚函数, 所以这里一定是虚函数
    // 写=0并没有问题
    // 除非返回值或参数不同, 那么F()就不是virtual
    void F() = 0;
};

int main()
{
    // 只要有一个纯虚函数存在, 该类就是抽象类, 只能作为接口使用
    // 不能用于实例化, 除非实现每个虚函数
    // 因此此处编译错误
    B b;
    return 0;
}