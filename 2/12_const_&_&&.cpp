#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Student {
    public:
        string name;
};


// 1. const
// 按下面注释掉的代码, const ClassRoom&是无法调用HasStudent的
// 因为this默认是Type *const, 即常量指针, 也就是只能指向本对象(顶层const, 指针内的地址不变)
// 但this指向的是非常量, 无法绑定到常量对象, 因此常量对象无法调用普通的成员函数
// 反之可以,指向常量的指针可以指向非常量对象, 但无法通过指针修改非常量对象的值


// 因此可以将const放在成员函数后表示this指向常量, 称为常量成员函数
// 相当于把this声明成const Type* const this
// 此时也无法通过this修改对象内部成员
class ClassRoom
{
private:
    vector<Student> students;

public:
    void AddStudent(Student student)
    {
        students.push_back(std::move(student));
    }

    // bool HasStudent(const string& name)
    // 所有不需要修改成员的成员函数都应加上const
    bool HasStudent(const string& name) const
    {
        return find_if(begin(students), end(students), [&](const Student& student)
        {
            return student.name == name;
        }) != end(students);
    }
};


// &和&&
// 如果修饰一个函数为&, 那么对象是右值引用时, 将无法调用, &&同理
// 错误: GetX返回值是X&&, 无法调用Print
class X
{
public:
    void Print()&
    {
        cout << "X&" << endl;
    }
};

X GetX()
{
    return {};
}

int main()
{
    GetX().Print();
    return 0;
}

// 无法通过编译, 因为只要有一个被&或&&修饰的函数, 所有的重载都要指定&或&&
// const要改成const&或const&&
class X2
{
public:
    void Print()const
    {
        cout << "const X" << endl;
    }

    void Print()&
    {
        cout << "X&" << endl;
    }

    void Print()&&
    {
        cout << "X&&" << endl;
    }
};



// WHY?
// 思考以下调用,
auto classRoom = MakeClassRoom()
    .WithStudent(a)
    .WithStudent(b)
    .WithStudent(c)
    ;

// 如果写成这样, 由于return *this会返回当前对象的拷贝, (若返回值为ClassRoom&则返回自身)
// 因此在多次调用中, 会多次重复创建该对象, 造成浪费
class ClassRoom
{
private:
    vector<Student> students;

public:
    ClassRoom WithStudent(Student student)
    {
        students.push_back(std::move(student));
        return *this;
    }
};

ClassRoom MakeClassRoom()
{
    return {};
}


// 此时, 使用return move(*this), 在返回时调用的是右值引用的拷贝构造函数
// 因此要加上右值引用的拷贝构造函数(左值拷贝构造函数会自动生成)
// 写了右值引用的拷贝构造函数后, 另外两个也要写, 不然不会自动生成
// 避免了复制的大量内存消耗
class ClassRoom
{
private:
    vector<Student> students;

public:
    ClassRoom()
    {
    }

    ClassRoom(const ClassRoom& classRoom)
        :students{ classRoom.students }
    {
    }

    ClassRoom(ClassRoom&& classRoom)
        :students{ std::move(classRoom.students) }
    {
    }

    ClassRoom WithStudent(Student student)&&
    {
        students.push_back(std::move(student));
        return std::move(*this);
    }
};

ClassRoom MakeClassRoom()
{
    return {};
}

// 也可以阻止错误调用, classRoomA为左值, 无法调用&&修饰的WithStudent函数
ClassRoom classRoomA = MakeClassRoom();
classRoomA.WithStudent(a);