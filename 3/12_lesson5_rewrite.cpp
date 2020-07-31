#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Cat;
class Dog;
class Mouse;

// 该接口类是为了方便扩展, 理论上可以不需要
// 接口类就是不能实例化的类(包含纯虚函数)
class IAnimalVisitor {
    public:
        virtual void Visit(Cat* animal) = 0;
        virtual void Visit(Dog* animal) = 0;
        virtual void Visit(Mouse* animal) = 0;
};

class Animal
{
private:
    string name;

public:
    
    Animal(const string& theName)
        :name{ theName }
    {
    }

    virtual ~Animal()
    {
    }

    const string& GetName()const
    {
        return name;
    }

    virtual string Introduce()const = 0;
    
    virtual void Accept(IAnimalVisitor* visitor) = 0;

};

class Cat : public Animal
{
public:
    Cat(const string& theName)
        :Animal{ theName }
    {
    }

    string Introduce()const override
    {
        return "我是一只猫，我的名字叫\"" + GetName() + "\"。";
    }
    
    virtual void Accept(IAnimalVisitor* visitor) {
        visitor->Visit(this);
    }

};

class Dog : public Animal
{
public:
    Dog(const string& theName)
        :Animal{ theName }
    {
    }

    string Introduce()const override
    {
        return "我是一只狗，我的名字叫\"" + GetName() + "\"。";
    }
    
    virtual void Accept(IAnimalVisitor* visitor) {
        visitor->Visit(this);
    }
};

class Mouse : public Animal
{
public:
    Mouse(const string& theName)
        :Animal{ theName }
    {
    }

    string Introduce()const override
    {
        return "我是一只老鼠，我的名字叫\"" + GetName() + "\"。";
    }
    
    virtual void Accept(IAnimalVisitor* visitor) {
        visitor->Visit(this);
    }
};

class IntroduceForCatVisitor : public IAnimalVisitor {
    public:
     virtual void Visit(Cat* animal) {
         cout << animal->Introduce() << endl;
     }
    virtual void Visit(Dog* animal) {     
     }
    virtual void Visit(Mouse* animal) {
     }
};

int main()
{
    auto tom = make_shared<Cat>("Tom");
    auto jerry = make_shared<Mouse>("Jerry");
    auto spike = make_shared<Dog>("Spike");
    auto butch = make_shared<Cat>("Butch");
    auto lightning = make_shared<Cat>("Lightning");
    vector<shared_ptr<Animal>> friends{ tom, jerry, spike, butch, lightning };
	IntroduceForCatVisitor visitor;
    for (auto animal : friends)
    {
        animal->Accept(&visitor);
    }
    return 0;
}