#include <iostream>
#include <vector>

using namespace std;

// 使用传统方法统计奇偶数
int Count(vector<int>& numbers, bool (*filter)(int)) { // 函数指针
    int counter = 0;
    for (int x: numbers) {
        if (filter(x)) {
            counter++;
        }
    }
    return counter;
}

bool Odd(int x) {
    return x % 2 == 1;
}

bool Even(int x) {
    return x % 2 == 0;
}

int CountOdds(vector<int>& numbers) {
    return Count(numbers, &Odd);
}

int CountEvens(vector<int>& numbers) {
    return Count(numbers, &Even);
}

// 使用lambda
// lambda类型没有名字,经常使用模板代替
template<typename U> // 声明模板参数, 表示暂时无法确定的类型
int CountLambda(vector<int>& numbers, U filter) {
    int counter = 0;
    for (int x: numbers) {
        if (filter(x)) {
            counter++;
        }
    }
    return counter;
}

int CountOddsLambda(vector<int>& numbers) {
    return CountLambda(numbers, [](int x) { return x % 2 == 1; });
}

int CountEvensLambda(vector<int>& numbers) {
    return CountLambda(numbers, [](int x) { return x % 2 == 0; });
}


// 增加需求, 求所有大于x的数
// 传统方法, 增加一个context参数
int CountGreater(vector<int>& numbers, bool (*filter)(int, void*), void* context) {
    int counter = 0;
    for (int x: numbers) {
        if (filter(x, context)) {
            counter++;
        }
    }
    return counter;
}

bool GreaterThan(int x, void* context) {
    return x > *reinterpret_cast<int*>(context);
}

int CountGreaterThan(vector<int>& numbers, int y) {
    return CountGreater(numbers, &GreaterThan, &y);
}

// 但此时其他代码就会很难看
bool OddGreater(int x, void*) {
    return x % 2 == 1;
}

bool EvenGreater(int x, void*) {
    return x % 2 == 0;
}

int CountOddsGreater(vector<int>& numbers) {
    return CountGreater(numbers, &OddGreater, nullptr);
}

int CountEvensGreater(vector<int>& numbers) {
    return CountGreater(numbers, &EvenGreater, nullptr);
}


// 使用lambda就会很简洁
// CountLambda无需修改
int CountGreaterThanLambda(vector<int>& numbers, int y) {
    // [=] 隐式值捕获, [&] 隐式引用捕获
    return CountLambda(numbers, [=](int x) { return x > y; });
}



// 大于x就复制到b
template<typename U>
void Traverse(vector<int>& xs, U process) {
    for (int x: xs) {
        process(x);
    }
}

void CopyGreaterThan(vector<int>& a, vector<int>& b, int y) {
    Traverse(a, [&, y](int x){ if (x > y) b.push_back(x); });
}


int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    vector<int> b;
    cout << CountGreaterThanLambda(nums, 3) << endl;
    CopyGreaterThan(nums, b, 3);
    for (auto x: b) {
        cout << x << ' ';
    }
    cout << endl;
    return 0;
}
