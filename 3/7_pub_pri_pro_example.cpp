class Y
{
protected:
    int member;
};

class X : public Y
{
public:
    void Method(X& y)
    {
        // protected和private时, 若member定义在Y内, 只有X和Y相同才能访问
        // 而static_cast<Y&>(y)类型是Y&, X和Y不同, 无法访问
        &(static_cast<Y&>(y).member);
    }
};