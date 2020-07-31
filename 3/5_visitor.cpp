#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// 目标: 不使用dynamic_cast识别出具体是哪个子类
// 而是让目标自己汇报
// 需要一个接口接受汇报(也就是类)

// 如果使用智能指针, 需要用dynamic_pointer_cast

// 前置声明, 因为Animal中用到了后面提到的类
class Cat;
class Dog;
class Mouse;

class Animal
{
private:
    string name;

public:
    // 接口类
    // 重载函数只会重载字面类型, 比如此处给一个Animal*, 即使类型是Cat, 也会编译错误
    class IVisitor {
        public:
        	virtual ~IVisitor() {}
            virtual void Visit(Cat* animal) = 0;
            virtual void Visit(Dog* animal) = 0;
            virtual void Visit(Mouse* animal) = 0;
    };

    Animal(const string& theName)
        :name{theName}
    {
    }

    virtual ~Animal()
    {
    }

    const string& GetName() const
    {
        return name;
    }

    virtual string Introduce() const = 0; // 纯虚函数, 子类必须override

    // 参数类型是Animal::IVisitor*
    virtual void Accept(IVisitor* visitor) = 0;
};

class Cat : public Animal
{
public:
    Cat(const string& theName)
        :Animal{theName}
    {
    }

    string Introduce()const override
    {
        return "我是一只猫，我的名字叫\"" + GetName() + "\"。";
    }

    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};

class Dog : public Animal
{
public:
    Dog(const string& theName)
        :Animal{theName}
    {
    }

    string Introduce()const override
    {
        return "我是一只狗，我的名字叫\"" + GetName() + "\"。";
    }

    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};

class Mouse : public Animal
{
public:
    Mouse(const string& theName)
        :Animal{theName}
    {
    }

    string Introduce()const override
    {
        return "我是一只老鼠，我的名字叫\"" + GetName() + "\"。";
    }

    void Accept(IVisitor* visitor) override {
        visitor->Visit(this);
    }
};

class OnlyPrintCatVisitor: public Animal::IVisitor {
    public:
        void Visit(Cat* animal) override {
            cout << animal->Introduce() << endl;
        }
        void Visit(Dog* animal) override {
        }

        void Visit(Mouse* animal) override {
        }

};

int main()
{
    // make_shared创建一个指向Cat的智能指针, 类型是shared_ptr<Cat> 
    auto tom = make_shared<Cat>("Tom"); 
    auto jerry = make_shared<Mouse>("Jerry");
    auto spike = make_shared<Dog>("Spike");
    auto butch = make_shared<Cat>("Butch");
    auto lightning = make_shared<Cat>("Lightning");
    vector<shared_ptr<Animal>> friends{ tom, jerry, spike, butch, lightning };

    OnlyPrintCatVisitor visitor;
    for (auto animal : friends)
    {
        animal -> Accept(&visitor);
    }
    return 0;
}


// visitor总结:
// 基类中写一个基类接口类定义虚访问函数visit
// 在外部写一个子接口类继承该基接口类, 对visit函数进行override
// 子接口类中的visit函数是真正的访问函数, 参数为子类指针, 实现了访问行为

// 基类中加入Accept纯虚函数, 参数为接口类的实例, 并在所有子类中override
// 子类中的Accept函数调用接口类的实例, 通过子接口类中的visit函数访问自身(this)

// 真正访问时, 通过调用子类对象的Accept函数, 间接调用子接口类visitor
// 通过子接口类的visit函数访问自身

// 正常: Cat*->Introduce
// Dog*->Introduce(不希望)

// visitor: 
// Cat*->Accept(Visitor*)
// Visitor*->Visit(Cat*)
// Cat*->Introduce
// 若Dog*->Accept(Visitor*), Visitor*->Visit(Dog*), 无行为定义

// 通过Visitor这个中介, 在Visit函数中定义访问行为
// 这样不破坏类的内部, 实现了类似if的功能

// dynamic_cast
// good: 直接/添加类容易(只需判断是否nullptr)
// bad: 添加逻辑困难, 或者需要不同类做不同事情

// visitor
// good: 性能好o(1)/添加逻辑很容易, 修改接口即可
// bad: 曲折/添加子类相对困难