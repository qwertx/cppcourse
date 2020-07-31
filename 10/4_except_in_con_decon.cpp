// 在构造函数中抛出异常

// 老式做法: two phase construction
// 可以看出真正的构造函数几乎什么也没做
// 而是另外写了一个Construction函数进行成员变量初始化
// 为了避免在构造函数中抛异常
class someFubar{
public:
    someFubar();
    bool Construction(void);
    ~someFubar();
private:
    fooObject _fooObj;
};

someFubar::someFubar(): _fooObj(null){ }

bool someFubar::Construction(void){
    bool rv = false;
    this->_fooObj = new fooObject();
    if (this->_fooObj != null) rv = true;
    return rv;
}


// 正确做法
struct Exception
{
};

struct Throw
{
    int id;

    Throw(int theId, bool requireThrow)
        :id{ theId }
    {
        cout << "Throw(" << id << ")" << endl;
        if (requireThrow)
        {
            throw Exception{};
        }
    }

    ~Throw()
    {
        cout << "~Throw(" << id << ")" << endl;
    }
};

struct Bad
{
    Throw throw1;
    Throw throw2;
    Throw throw3;

    // 比如id为1时, 只有throw1真正抛出异常
    Bad(int id)
        :throw1{ 1,id == 1 }, throw2{ 2,id == 2 }, throw3{ 3,id == 3 }
    {
        cout << "Bad()" << endl;
        throw Exception{};
    }

    ~Bad()
    {
        cout << "~Bad()" << endl;
    }
};

// Bad{1} 输出: Throw(1), 程序中止(Throw构造函数抛出异常)
// Bad{2} 输出: Throw(1),Throw(2),~Throw(1), 程序中止(Throw构造函数抛出异常)