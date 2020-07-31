#include <iostream>
#include <string>

using namespace std;

// struct point{
//     int x; 
//     int y;
//     point(int z): x(z), y(z) {} // 构造函数
// };

// int main() {
//     auto p = new point[5]{1, 2, 3, 4, 5}; // 一个包含5个point的数组
//     cout << p[0].x << endl;
//     delete[] p;
//     return 0;
// }

struct point {
    int x;
    int y;
};

int main()
{
	point p[3]{{1,2}, {3,4}, {5,6}}; // 没有默认构造函数时, 通过universal initialization初始化类数组
    cout << p[1].x << endl;
    return 0;
}