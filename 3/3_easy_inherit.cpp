#include <string>
#include <iostream>

using namespace std;

// class是集合论的术语
// 如果要用new创建继承关系的实例, 每一个类的析构函数都要声明为virtual
// 如果父类的析构函数为virtual, 那么自己的就自动成为virtual
class Animal{
    public:
        string name;
        // 虚函数是用于派生类定义适合自身的版本
        // 使用指针或引用调用虚函数, 将进行动态绑定
        // 根据传入对象的不同确定执行哪个版本的函数
        virtual ~Animal(){} 
};

class Cat: public Animal { };


// 子类的引用和指针都可以隐式转换为父类的引用和指针
// 下面四个都指向一个对象
int main()
{

    Cat cat;
    Cat* pCat = &cat;

    Animal& animal = cat;
    Animal* pAnimal = pCat;
}


// 父类向子类转换
// 使用dynamic_cast进行转换, 前提:被转换的类至少包含一个虚函数
// 会进行类型检查, 不匹配就会返回nullptr, 也可以在几个子类/基类中转换
// static_cast不会检查类型, 类型错误会拿到野指针
int main()
{
    Animal* pAnimal = GetAnAnimalFromSomewhere();
    Cat* cat = dynamic_cast<Cat*>(pAnimal);
    if (cat == nullptr)
    {
        cout << "这不是一只猫。" << endl;
    }
    else
    {
        cout << "这是一只猫。" << endl;
    }
}


// 为什么要继承? 为了覆盖父类的虚函数
// 虚函数: 可以被子类修改的父类函数
class Animal
{
public:
    string name;

    virtual ~Animal(){}

    /*
        千万不要把IO跟逻辑混在一起。
        Introduce函数只负责生成字符串，别人要怎么调用它，在另一个地方解决。
    */
    virtual string Introduce()
    {
        return "我不知道自己是什么动物。";
    }
};

// override表示自己正在覆盖父类的一个函数
// name这里可以写出this->name, 类型是Cat* const, 也就是常量指针指向可写的Cat
class Cat : public Animal
{
public:
    string Introduce()override
    {
        return "我是一只猫，我的名字是\"" + name +"\"。";
    }
};

class Dog : public Animal
{
public:
    string Introduce()override
    {
        return "我是一只狗，我的名字是\"" + name +"\"。";
    }
};


void IntroduceAnAnimal(Animal& animal)
{
    cout << animal.Introduce() << endl;
}

int main()
{   
    Cat cat;
    cat.name = "Tom";

    Dog dog;
    dog.name = "Spike";

    Animal animal;
    animal.name = "nothing";

    IntroduceAnAnimal(cat);  // 我是一只猫
    IntroduceAnAnimal(dog);  // 我是一只狗
    IntroduceAnDnimal(animal); // 我不知道自己是什么动物
}


// 如果animal没有默认构造函数
// 需要在子类初始化列表中写上父类名字, 并调用父类的某个构造函数
// 如果不写会调用默认构造函数, 若不存在的话会出现错误
// 同时, 若父类没有默认构造函数, 子类也不会有, =default也没用
class Animal
{
public:
    string name;

    Animal(const string& theName)
        : name{theName}
    {
    }

    virtual ~Animal()
    {
    }
};

class Cat : public Animal
{
public:
    Cat()
        :Animal{"Tom"}
    {
    }

    Cat(const string& theName)
        :Animal{theName}
    {
    }
};

class Dog : public Animal
{
public:
    Dog()
        :Animal{"Spike"}
    {
    }

    Dog(const string& theName)
        :Animal{theName}
    {
    }
};