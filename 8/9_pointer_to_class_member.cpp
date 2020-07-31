// 指向类成员的指针分为成员变量指针和成员函数指针
// 但它们并不是指针, 而是成员的名字, 无法和void*相互转换(比如用reinterpret_cast)

// 如果用指针引用类的某个不是排在第一位的虚基类的一个虚函数的话, 尺寸可能超过sizeof(void*)
// 因为这不能简单地用指针解决, 还有如何从子类指针转成父类指针，这个虚函数被覆盖了怎么办等等一系列问题
// Visual C++下面有可能高达sizeof(void*)*4, 而且根据不同情况尺寸也不同

struct Vector
{
    int x;
    int y;
};

int main()
{
    Vector v{1, 2};
    // 成员变量指针指向Vector的某个int成员
    int Vector::* px = &Vector::x;
    int Vector::* py = &Vector::y;
    // v.*px和v.x相同
    // 要使用.*访问成员变量指针
    // 如果v自身也是指针, 那么要写v->*px
    cout << v.*px << endl;
    cout << v.*py << endl;
    return 0;
}


// 抽象成函数
int ReadVector(Vector v, int Vector::* p)
{
    return v.*p;
}

int main()
{
    Vector v{1, 2};
    cout << ReadVector(v, &Vector::x) << endl;
    cout << ReadVector(v, &Vector::y) << endl;
    return 0;
}


// 成员函数指针, 假设Vector有两个成员函数
struct Vector
{
private:
    int x;
    int y;

public:
    Vector(int theX, int theY)
        :x{ theX }
        , y{ theY }
    {
    }

    int GetX()const
    {
        return x;
    }

    int GetY()const
    {
        return y;
    }
};

//&Vector::GetX的类型是int (Vector::*)() const, p是指针名字
int ReadVector(Vector v, int (Vector::* p)() const)
{
    // 注意.*的优先级比()低, 不能写成v.*p()
    return (v.*p)();
}

int main()
{
    Vector v{ 1, 2 };
    cout << ReadVector(v, &Vector::GetX) << endl;
    cout << ReadVector(v, &Vector::GetY) << endl;
    return 0;
}