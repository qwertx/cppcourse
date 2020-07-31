#include <string>

using namespace std;

class Animal
{
public:
    string name;

    virtual ~Animal() = default;

    virtual string Introduce()
    {
        return "我的名字叫" + name + "。";
    }
};

class Cat : public Animal
{
public:
    string Introduce()override
    {
        // return "我是一只猫，我的名字叫" + name + "。";

        // 不重复写"我的名字叫", 直接调用
        return "我是一只猫，" + Animal::Introduce();
    }
};

// 以下代码可以
Cat cat;
cat.name = "Tom";
cout << cat.Animal::Introduce() << endl;


// 如果Animal::Introduce根本无需实现
// 使用纯虚函数

// 但是无法直接创建Animal, 该类只能被继承
// 也无法使用Animal::Introduce, 会产生链接错误
class Animal
{
    virtual string Introduce() = 0;
};

 
// 如果析构函数为纯虚的, 那么Base和其子类均无法被析构
// 如果把析构函数写成private或=delete, 那么这个类将无法被继承
// 因为子类析构函数无法调用父类的析构函数
class Base
{
public:
    virtual ~Base() = 0;
};

// 一个不能被析构的类没有什么意义
// 但有时需要无法被构造的类, 用于存放静态函数, 强迫使用者写出namespace