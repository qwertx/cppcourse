#include <iostream>

using namespace std;

struct Point
{
    int x;
    int y;
};


// 输出1, 10
// a b为栈构造, c d为堆构造
// new的时候也可以用universal initialization
// new后一定要delete

int main()
{
    Point a{1, 2};
    Point b = a;

    Point* c = new Point{1, 2};
    Point* d = c;

    a.x = 10;
    c->x = 10;
    cout << b.x << ", " << d->x << endl;

    delete c;
}

// VS, 加上
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define NEW_WITH_MEMORY_LEAK_CHECKING new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new NEW_WITH_MEMORY_LEAK_CHECKING

// 如果有多个cpp, 放在公用的头文件或预编译头文件stdafx.h最上方
// 在主函数return 0;上方加入_CrtDumpMemoryLeaks();
// Linux可使用valgrind