#include <iostream>
#include <string>
#include <memory>

using namespace std;

// 重载<<通过给std::ostream定义一个operator<<(o, v)完成
// 因为无法修改ostream类, 因此只能定义为全局函数
// 如果是成员函数, 左侧对象将变成类的一个对象(this)(成员函数自动添加this)
struct Vector
{
    int x;
    int y;
};

// << 接受2个运算对象: ostream和打印值
ostream& operator<<(ostream& o, Vector v) {
    return o << "(" << v.x << ", " << v.y << ")";
}

int main()
{
    Vector u{ 1, 2 };
    Vector v{ 3, 4 };
    cout << u << ", " << v << endl;
    return 0;
}